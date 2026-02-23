#include "NiagaraSpecExecutor.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "NiagaraCommon.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"   
#include "NiagaraLightRendererProperties.h"
#include "NiagaraMeshRendererProperties.h"
#include "AssetToolsModule.h"
#include "UObject/UnrealType.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "NiagaraEditorModule.h"
#include "NiagaraConstants.h"
#include "NiagaraDataInterfaceCurve.h"
#include "UObject/SavePackage.h"
#include "Factories/Factory.h"
#include "Modules/ModuleManager.h"
#include "UObject/UObjectGlobals.h"
#include "NiagaraScriptSourceBase.h"
#include "NiagaraSystemEditorData.h"
#include "NiagaraEditorUtilities.h"
#include "Subsystems/AssetEditorSubsystem.h"
#include "Editor.h"
#include "NiagaraParameterStore.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceConstant.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "Internationalization/Regex.h"
#include "VFXTemplateSelector.h"
#include "VFXMotionModuleLibrary.h"
#include "VFXModuleStripper.h"
#include "VFXModuleInserter.h"
#include "VFXRendererValidationFixer.h"
#include "PipelineLog.h"

static FString NormalizeTemplateObjectPath(const FString& InPath);
static void SetEmitterRequiresPersistentIDs(UNiagaraEmitter* Emitter, bool bEnabled);
static void ApplyIntentModuleRules(UNiagaraSystem* System, const FString& EmitterName, const FVFXIntent& Intent, const FTemplateSelectionResult& Selection);
static void AddMinimalModuleChain(UNiagaraSystem* System, const FString& EmitterName, EVFXRendererType RendererType);
static bool ResolveEmitterArrayProperty(UNiagaraEmitter* Emitter, const FName& ArrayPropName, void*& OutContainer, FArrayProperty*& OutArrayProp);

static FString SanitizeNiagaraIdentifier(const FString& SourceString, const FString& Fallback)
{
    FString Sanitized = SourceString;
    Sanitized = Sanitized.Replace(TEXT(" "), TEXT("_"));

    FString Clean;
    Clean.Reserve(Sanitized.Len());
    for (const TCHAR Ch : Sanitized)
    {
        if (FChar::IsAlnum(Ch) || Ch == TEXT('_'))
        {
            Clean.AppendChar(Ch);
        }
        else
        {
            Clean.AppendChar(TEXT('_'));
        }
    }

    while (Clean.Contains(TEXT("__")))
    {
        Clean = Clean.Replace(TEXT("__"), TEXT("_"));
    }

    Clean.TrimStartAndEndInline();
    return Clean.IsEmpty() ? Fallback : Clean;
}

static void MarkSystemDirtyAndFullRecompile(UNiagaraSystem* System, const TCHAR* Context)
{
    if (!System)
    {
        return;
    }

    System->MarkPackageDirty();
    if (UPackage* Pkg = System->GetOutermost())
    {
        Pkg->MarkPackageDirty();
    }

#if WITH_EDITOR
    System->RequestCompile(true);
    System->WaitForCompilationComplete(true, true);
#endif

    UE_LOG(LogVFXAgent, Verbose, TEXT("[%s] MarkPackageDirty + FullRecompile completed for '%s'"), Context, *System->GetName());
}

static FString GetVFXAgentSetting(const TCHAR* Key, const FString& DefaultValue)
{
    FString Value;
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetString(Section, Key, Value, File) && !Value.IsEmpty())
        {
            return Value;
        }
    }
    return DefaultValue;
}

static TArray<FString> GetVFXAgentSettingArray(const TCHAR* Key)
{
    TArray<FString> Values;
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetArray(Section, Key, Values, File) && Values.Num() > 0)
        {
            return Values;
        }
    }
    return Values;
}

static bool GetVFXAgentSettingBool(const TCHAR* Key, bool bDefault)
{
    bool bValue = bDefault;
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetBool(Section, Key, bValue, File))
        {
            return bValue;
        }
    }
    return bDefault;
}

static UNiagaraScript* LoadNiagaraScriptFromPath(const FString& Path)
{
    if (Path.IsEmpty()) return nullptr;
    const FString Normalized = NormalizeTemplateObjectPath(Path);
    return LoadObject<UNiagaraScript>(nullptr, *Normalized);
}

static void AddMinimalModuleChain(UNiagaraSystem* System, const FString& EmitterName, EVFXRendererType RendererType)
{
    if (!System) return;
	(void)RendererType;

    FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara,
        FString::Printf(TEXT("Building minimal module chain for '%s'"), *EmitterName));

    struct FModuleEntry
    {
        const TCHAR* Path;
        const TCHAR* Stack;
    };

    const FModuleEntry Entries[] = {
        { TEXT("/Niagara/Modules/Spawn/Spawn Rate.Spawn Rate"), TEXT("Particle Spawn") },
        { TEXT("/Niagara/Modules/Spawn/Spawn Burst Instantaneous.Spawn Burst Instantaneous"), TEXT("Particle Spawn") },
        { TEXT("/Niagara/Modules/Particle/Initialize Particle.Initialize Particle"), TEXT("Particle Spawn") },
        { TEXT("/Niagara/Modules/Spawn/Velocity/Add Velocity.Add Velocity"), TEXT("Particle Spawn") },
        { TEXT("/Niagara/Modules/Update/Drag.Drag"), TEXT("Particle Update") },
        { TEXT("/Niagara/Modules/Update/Color/Scale Color.Scale Color"), TEXT("Particle Update") },
        { TEXT("/Niagara/Modules/Update/Scale Sprite Size.Scale Sprite Size"), TEXT("Particle Update") }
    };

    for (const FModuleEntry& Entry : Entries)
    {
        const bool bOk = FNiagaraSpecExecutor::AddModuleToEmitter(System, EmitterName, Entry.Path, Entry.Stack);
        if (!bOk)
        {
            FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Niagara,
                FString::Printf(TEXT("Failed to add module: %s"), Entry.Path));
        }
    }
}

static bool HasAnyModules(UNiagaraEmitter* Emitter, const FName& ArrayPropName)
{
    if (!Emitter) return false;

    void* TargetContainer = nullptr;
    FArrayProperty* ArrayProp = nullptr;
    if (!ResolveEmitterArrayProperty(Emitter, ArrayPropName, TargetContainer, ArrayProp) || !TargetContainer || !ArrayProp)
    {
        return false;
    }

    FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));
    return Helper.Num() > 0;
}

// Helper for finding assets
static void EnsureAssetRegistryReady()
{
    static bool bSearchedAll = false;
    if (bSearchedAll)
    {
        return;
    }
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    AssetRegistryModule.Get().SearchAllAssets(true);
    bSearchedAll = true;
}

static FString FindTemplatePath(const FString& TemplateId)
{
    FString Id = TemplateId;
    Id.TrimStartAndEndInline();
    if (Id.IsEmpty())
    {
        return FString();
    }

    // If a path was provided, trust it (but normalize if missing object name).
    if (Id.Contains(TEXT("/")))
    {
        if (!Id.Contains(TEXT(".")))
        {
            const FString AssetName = FPaths::GetCleanFilename(Id);
            if (!AssetName.IsEmpty())
            {
                return FString::Printf(TEXT("%s.%s"), *Id, *AssetName);
            }
        }
        return Id;
    }

    // UE5.5 template paths - located in /Niagara/DefaultAssets/Templates/Emitters/
    // These are EMITTER templates (not system templates) and should be loaded directly as UNiagaraEmitter
    if (Id.Equals(TEXT("Fountain"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain");
    if (Id.Equals(TEXT("UpwardMeshBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/UpwardMeshBurst.UpwardMeshBurst");
    if (Id.Equals(TEXT("DirectionalBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/DirectionalBurst.DirectionalBurst");
    if (Id.Equals(TEXT("OmnidirectionalBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/OmnidirectionalBurst.OmnidirectionalBurst");
    if (Id.Equals(TEXT("SimpleSpriteBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/SimpleSpriteBurst.SimpleSpriteBurst");
    if (Id.Equals(TEXT("BlowingParticles"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/BlowingParticles.BlowingParticles");
    if (Id.Equals(TEXT("ConfettiBurst"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/ConfettiBurst.ConfettiBurst");
    if (Id.Equals(TEXT("DynamicBeam"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/DynamicBeam.DynamicBeam");
    if (Id.Equals(TEXT("StaticBeam"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/StaticBeam.StaticBeam");
    if (Id.Equals(TEXT("HangingParticulates"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/HangingParticulates.HangingParticulates");
    if (Id.Equals(TEXT("LocationBasedRibbon"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/LocationBasedRibbon.LocationBasedRibbon");
    if (Id.Equals(TEXT("Minimal"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal");
    if (Id.Equals(TEXT("SingleLoopingParticle"), ESearchCase::IgnoreCase)) return TEXT("/Niagara/DefaultAssets/Templates/Emitters/SingleLoopingParticle.SingleLoopingParticle");

    // AssetRegistry fallback: try to resolve by asset name under /Niagara or /Game
    EnsureAssetRegistryReady();
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter Filter;
    Filter.ClassPaths.Add(UNiagaraSystem::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UNiagaraEmitter::StaticClass()->GetClassPathName());
    Filter.PackagePaths.Add(TEXT("/Niagara"));
    Filter.PackagePaths.Add(TEXT("/Engine"));
    Filter.PackagePaths.Add(TEXT("/Game"));
    Filter.bRecursivePaths = true;

    TArray<FAssetData> Assets;
    AssetRegistryModule.Get().GetAssets(Filter, Assets);

    const FString Candidates[] =
    {
        Id,
        Id + TEXT("System"),
        Id + TEXT("Emitter"),
        Id + TEXT("Template")
    };

    for (const FAssetData& Asset : Assets)
    {
        const FString AssetName = Asset.AssetName.ToString();
        for (const FString& Candidate : Candidates)
        {
            if (AssetName.Equals(Candidate, ESearchCase::IgnoreCase))
            {
                return Asset.GetObjectPathString();
            }
        }
    }

    // Final fallback - use Fountain emitter template for UE5.5
    return TEXT("/Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain");
}

static FString NormalizeTemplateObjectPath(const FString& InPath)
{
    if (InPath.IsEmpty())
    {
        return InPath;
    }
    if (InPath.Contains(TEXT(".")))
    {
        return InPath;
    }
    const FString AssetName = FPaths::GetCleanFilename(InPath);
    if (AssetName.IsEmpty())
    {
        return InPath;
    }
    return FString::Printf(TEXT("%s.%s"), *InPath, *AssetName);
}

static void SetEmitterRequiresPersistentIDs(UNiagaraEmitter* Emitter, bool bEnabled)
{
    if (!Emitter) return;
    FBoolProperty* BoolProp = FindFProperty<FBoolProperty>(Emitter->GetClass(), TEXT("bRequiresPersistentIDs"));
    if (BoolProp)
    {
        BoolProp->SetPropertyValue_InContainer(Emitter, bEnabled);
    }
}

static bool SetStructObjectField(void* StructPtr, UStruct* StructType, const FName& FieldName, UObject* Value)
{
    if (!StructPtr || !StructType) return false;
    FProperty* Prop = StructType->FindPropertyByName(FieldName);
    if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Prop))
    {
        ObjProp->SetObjectPropertyValue_InContainer(StructPtr, Value);
        return true;
    }
    return false;
}

static bool ResolveEmitterArrayProperty(UNiagaraEmitter* Emitter, const FName& ArrayPropName, void*& OutContainer, FArrayProperty*& OutArrayProp)
{
    OutContainer = Emitter;
    OutArrayProp = nullptr;

    if (!Emitter)
    {
        return false;
    }

    OutArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), ArrayPropName);
    if (OutArrayProp)
    {
        return true;
    }

#if ENGINE_MAJOR_VERSION == 5 && ENGINE_MINOR_VERSION >= 5
    if (FVersionedNiagaraEmitterData* EmitterData = Emitter->GetLatestEmitterData())
    {
        OutContainer = EmitterData;
        OutArrayProp = FindFProperty<FArrayProperty>(FVersionedNiagaraEmitterData::StaticStruct(), ArrayPropName);
        if (OutArrayProp)
        {
            return true;
        }
    }
#endif

    OutContainer = nullptr;
    return false;
}

struct FModuleInsertOptions
{
    FString Mode;      // First | Last | Phase | Anchor
    FString Phase;     // Phase name
    FString Anchor;    // Virtual anchor
    FString Relative;  // Before | After
    int32 Priority = 0;
};

static EModulePhase ParsePhase(const FString& Value)
{
    const FString Lower = Value.ToLower();
    if (Lower.Contains(TEXT("presim"))) return EModulePhase::PreSim;
    if (Lower.Contains(TEXT("force"))) return EModulePhase::Forces;
    if (Lower.Contains(TEXT("damp"))) return EModulePhase::Damping;
    if (Lower.Contains(TEXT("clamp"))) return EModulePhase::Clamp;
    if (Lower.Contains(TEXT("integrate"))) return EModulePhase::Integrate;
    if (Lower.Contains(TEXT("collision"))) return EModulePhase::CollisionDetect;
    if (Lower.Contains(TEXT("event"))) return EModulePhase::EventWrite;
    if (Lower.Contains(TEXT("postcollision"))) return EModulePhase::PostCollisionResponse;
    if (Lower.Contains(TEXT("curve"))) return EModulePhase::Curves;
    if (Lower.Contains(TEXT("render"))) return EModulePhase::RenderPrep;
    if (Lower.Contains(TEXT("kill")) || Lower.Contains(TEXT("cull"))) return EModulePhase::KillCull;
    return EModulePhase::Unknown;
}

static UNiagaraScript* GetScriptFromEntry(void* ElemPtr, UStruct* StructType)
{
    if (!ElemPtr || !StructType) return nullptr;
    const FName Fields[] = { TEXT("Script"), TEXT("ScriptObject"), TEXT("GeneratorScript"), TEXT("EventScript") };
    for (const FName& Field : Fields)
    {
        FProperty* Prop = StructType->FindPropertyByName(Field);
        if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(Prop))
        {
            if (UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(ElemPtr))
            {
                return Cast<UNiagaraScript>(Obj);
            }
        }
    }
    return nullptr;
}

static bool IsRelativeBefore(const FString& Value)
{
    const FString Lower = Value.ToLower();
    return Lower.Contains(TEXT("before"));
}

static int32 FindPhaseBoundaryIndex(UNiagaraEmitter* Emitter, const FName& ArrayPropName, EModulePhase Phase, bool bBefore)
{
    void* TargetContainer = nullptr;
    FArrayProperty* ArrayProp = nullptr;
    if (!ResolveEmitterArrayProperty(Emitter, ArrayPropName, TargetContainer, ArrayProp) || !TargetContainer || !ArrayProp)
    {
        return INDEX_NONE;
    }

    FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));

    int32 FirstIndex = INDEX_NONE;
    int32 LastIndex = INDEX_NONE;
    if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
    {
        UStruct* StructType = StructProp->Struct;
        for (int32 i = 0; i < Helper.Num(); ++i)
        {
            void* ElemPtr = Helper.GetRawPtr(i);
            UNiagaraScript* Script = GetScriptFromEntry(ElemPtr, StructType);
            if (ClassifyScriptPhase(Script) == Phase)
            {
                if (FirstIndex == INDEX_NONE) FirstIndex = i;
                LastIndex = i;
            }
        }
    }

    if (FirstIndex == INDEX_NONE) return INDEX_NONE;
    return bBefore ? FirstIndex : (LastIndex + 1);
}

static int32 FindAnchorIndex(UNiagaraEmitter* Emitter, const FName& ArrayPropName, const FString& Anchor, bool bBefore)
{
    const FString Lower = Anchor.ToLower();
    if (Lower == TEXT("@forcesend")) return FindPhaseBoundaryIndex(Emitter, ArrayPropName, EModulePhase::Forces, false);
    if (Lower == TEXT("@collisionbegin")) return FindPhaseBoundaryIndex(Emitter, ArrayPropName, EModulePhase::CollisionDetect, true);
    if (Lower == TEXT("@collisionend")) return FindPhaseBoundaryIndex(Emitter, ArrayPropName, EModulePhase::CollisionDetect, false);
    if (Lower == TEXT("@eventwriteend")) return FindPhaseBoundaryIndex(Emitter, ArrayPropName, EModulePhase::EventWrite, false);
    if (Lower == TEXT("@curvesbegin")) return FindPhaseBoundaryIndex(Emitter, ArrayPropName, EModulePhase::Curves, true);
    // If anchor matches a phase name, use it
    const EModulePhase AnchorPhase = ParsePhase(Anchor);
    if (AnchorPhase != EModulePhase::Unknown)
    {
        return FindPhaseBoundaryIndex(Emitter, ArrayPropName, AnchorPhase, bBefore);
    }
    return INDEX_NONE;
}

static int32 FindInsertIndexForPhase(UNiagaraEmitter* Emitter, const FName& ArrayPropName, EModulePhase Phase, bool bBefore, int32 Priority)
{
    int32 Index = FindPhaseBoundaryIndex(Emitter, ArrayPropName, Phase, bBefore);
    if (Index != INDEX_NONE) return Index;

    // If no matching phase exists, insert before the first module with a higher phase index
    void* TargetContainer = nullptr;
    FArrayProperty* ArrayProp = nullptr;
    if (!ResolveEmitterArrayProperty(Emitter, ArrayPropName, TargetContainer, ArrayProp) || !TargetContainer || !ArrayProp)
    {
        return INDEX_NONE;
    }

    FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));
    if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
    {
        UStruct* StructType = StructProp->Struct;
        for (int32 i = 0; i < Helper.Num(); ++i)
        {
            void* ElemPtr = Helper.GetRawPtr(i);
            UNiagaraScript* Script = GetScriptFromEntry(ElemPtr, StructType);
            EModulePhase Other = ClassifyScriptPhase(Script);
            if ((int32)Other > (int32)Phase)
            {
                return i;
            }
        }
    }

    return Helper.Num();
}

static bool InsertScriptWithOrdering(UNiagaraEmitter* Emitter, const FName& ArrayPropName, UNiagaraScript* Script, const FModuleInsertOptions& Options)
{
    if (!Emitter || !Script) return false;

    void* TargetContainer = nullptr;
    FArrayProperty* ArrayProp = nullptr;
    if (!ResolveEmitterArrayProperty(Emitter, ArrayPropName, TargetContainer, ArrayProp) || !TargetContainer || !ArrayProp)
    {
        return false;
    }

    FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));

    // Avoid duplicates
    if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
    {
        UStruct* StructType = StructProp->Struct;
        for (int32 i = 0; i < Helper.Num(); ++i)
        {
            void* ElemPtr = Helper.GetRawPtr(i);
            UNiagaraScript* Existing = GetScriptFromEntry(ElemPtr, StructType);
            if (Existing == Script)
            {
                return true;
            }
        }
    }

    const FString ModeLower = Options.Mode.ToLower();
    const bool bBefore = IsRelativeBefore(Options.Relative);
    int32 InsertIndex = Helper.Num();

    if (ModeLower.Contains(TEXT("first")))
    {
        InsertIndex = 0;
    }
    else if (ModeLower.Contains(TEXT("last")))
    {
        InsertIndex = Helper.Num();
    }
    else if (ModeLower.Contains(TEXT("anchor")))
    {
        InsertIndex = FindAnchorIndex(Emitter, ArrayPropName, Options.Anchor, bBefore);
        if (InsertIndex == INDEX_NONE) InsertIndex = Helper.Num();
    }
    else // Phase (default)
    {
        const EModulePhase Phase = ParsePhase(Options.Phase);
        InsertIndex = FindInsertIndexForPhase(Emitter, ArrayPropName, Phase, bBefore, Options.Priority);
    }

    Helper.InsertValues(InsertIndex, 1);
    void* ElemPtr = Helper.GetRawPtr(InsertIndex);
    if (FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner))
    {
        UStruct* StructType = StructProp->Struct;
        if (!SetStructObjectField(ElemPtr, StructType, TEXT("Script"), Script))
        {
            SetStructObjectField(ElemPtr, StructType, TEXT("ScriptObject"), Script);
            SetStructObjectField(ElemPtr, StructType, TEXT("GeneratorScript"), Script);
            SetStructObjectField(ElemPtr, StructType, TEXT("EventScript"), Script);
        }
    }

    return true;
}

struct FModuleNode
{
    FString Id;
    EModulePhase Phase = EModulePhase::Unknown;
    int32 Priority = 0;
    bool bIsAnchor = false;
};

enum class ERuleMatchMode : uint8
{
    Contains,
    Exact,
    Regex
};

struct FModuleSortRule
{
    FString Match;
    ERuleMatchMode Mode = ERuleMatchMode::Contains;
    EModulePhase Phase = EModulePhase::Unknown;
    int32 Priority = 0;
    FString Before;
    FString After;
};

static ERuleMatchMode ParseMatchMode(const FString& Value)
{
    const FString Lower = Value.ToLower();
    if (Lower.Contains(TEXT("exact"))) return ERuleMatchMode::Exact;
    if (Lower.Contains(TEXT("regex"))) return ERuleMatchMode::Regex;
    return ERuleMatchMode::Contains;
}

static bool RuleMatches(const FModuleSortRule& Rule, const FString& Name)
{
    if (Rule.Match.IsEmpty()) return false;
    const FString Target = Name;
    if (Rule.Mode == ERuleMatchMode::Exact)
    {
        return Target.Equals(Rule.Match, ESearchCase::IgnoreCase);
    }
    if (Rule.Mode == ERuleMatchMode::Regex)
    {
        FRegexPattern Pattern(Rule.Match);
        FRegexMatcher Matcher(Pattern, Target);
        return Matcher.FindNext();
    }
    return Target.Contains(Rule.Match, ESearchCase::IgnoreCase);
}

static FModuleSortRule ParseRuleString(const FString& RuleStr)
{
    FModuleSortRule Rule;
    TArray<FString> Parts;
    RuleStr.ParseIntoArray(Parts, TEXT(";"), true);
    for (const FString& Part : Parts)
    {
        FString Key, Value;
        if (!Part.Split(TEXT("="), &Key, &Value)) continue;
        Key = Key.TrimStartAndEnd();
        Value = Value.TrimStartAndEnd();
        if (Key.Equals(TEXT("match"), ESearchCase::IgnoreCase)) Rule.Match = Value;
        else if (Key.Equals(TEXT("mode"), ESearchCase::IgnoreCase)) Rule.Mode = ParseMatchMode(Value);
        else if (Key.Equals(TEXT("phase"), ESearchCase::IgnoreCase)) Rule.Phase = ParsePhase(Value);
        else if (Key.Equals(TEXT("priority"), ESearchCase::IgnoreCase)) Rule.Priority = FCString::Atoi(*Value);
        else if (Key.Equals(TEXT("before"), ESearchCase::IgnoreCase)) Rule.Before = Value;
        else if (Key.Equals(TEXT("after"), ESearchCase::IgnoreCase)) Rule.After = Value;
    }
    return Rule;
}

static TArray<FModuleSortRule> GetGlobalModuleSortRules()
{
    TArray<FModuleSortRule> Rules;
    const TArray<FString> RuleStrings = GetVFXAgentSettingArray(TEXT("ModuleSortRules"));
    for (const FString& Str : RuleStrings)
    {
        const FModuleSortRule Rule = ParseRuleString(Str);
        if (!Rule.Match.IsEmpty()) Rules.Add(Rule);
    }
    return Rules;
}

static FString PhaseAnchorBeginId(EModulePhase Phase)
{
    return FString::Printf(TEXT("@PhaseBegin.%d"), (int32)Phase);
}

static FString PhaseAnchorEndId(EModulePhase Phase)
{
    return FString::Printf(TEXT("@PhaseEnd.%d"), (int32)Phase);
}

static FString MapVirtualAnchorToNodeId(const FString& Anchor)
{
    const FString Lower = Anchor.ToLower();
    if (Lower == TEXT("@forcesend")) return PhaseAnchorEndId(EModulePhase::Forces);
    if (Lower == TEXT("@collisionbegin")) return PhaseAnchorBeginId(EModulePhase::CollisionDetect);
    if (Lower == TEXT("@collisionend")) return PhaseAnchorEndId(EModulePhase::CollisionDetect);
    if (Lower == TEXT("@eventwriteend")) return PhaseAnchorEndId(EModulePhase::EventWrite);
    if (Lower == TEXT("@curvesbegin")) return PhaseAnchorBeginId(EModulePhase::Curves);
    const EModulePhase AsPhase = ParsePhase(Anchor);
    if (AsPhase != EModulePhase::Unknown)
    {
        return PhaseAnchorBeginId(AsPhase);
    }
    return Anchor; // allow direct id reference
}

static void AddEdge(TMap<FString, TSet<FString>>& Edges, const FString& From, const FString& To)
{
    if (From.IsEmpty() || To.IsEmpty() || From == To) return;
    Edges.FindOrAdd(From).Add(To);
}

static bool TopoSortModules(const TArray<FModuleNode>& Nodes, const TMap<FString, TSet<FString>>& Edges, TArray<FString>& OutOrder)
{
    TMap<FString, int32> InDegree;
    TMap<FString, TArray<FString>> Adj;
    for (const FModuleNode& Node : Nodes)
    {
        InDegree.Add(Node.Id, 0);
        Adj.Add(Node.Id, TArray<FString>());
    }

    for (const TPair<FString, TSet<FString>>& Pair : Edges)
    {
        const FString& From = Pair.Key;
        for (const FString& To : Pair.Value)
        {
            if (!Adj.Contains(From) || !InDegree.Contains(To)) continue;
            Adj[From].Add(To);
            InDegree[To]++;
        }
    }

    auto NodeKey = [&Nodes](const FString& Id)
    {
        const FModuleNode* Found = Nodes.FindByPredicate([&](const FModuleNode& N) { return N.Id == Id; });
        const int32 PhaseIdx = Found ? (int32)Found->Phase : 999;
        const int32 Priority = Found ? Found->Priority : 0;
        return TTuple<int32, int32, FString>(PhaseIdx, Priority, Id);
    };

    TArray<FString> Zero;
    for (const TPair<FString, int32>& Pair : InDegree)
    {
        if (Pair.Value == 0) Zero.Add(Pair.Key);
    }

    Zero.Sort([&](const FString& A, const FString& B)
    {
        return NodeKey(A) < NodeKey(B);
    });

    while (Zero.Num() > 0)
    {
        const FString Current = Zero[0];
        Zero.RemoveAt(0);
        OutOrder.Add(Current);
        for (const FString& Next : Adj[Current])
        {
            int32& Deg = InDegree[Next];
            Deg--;
            if (Deg == 0)
            {
                Zero.Add(Next);
            }
        }
        Zero.Sort([&](const FString& A, const FString& B)
        {
            return NodeKey(A) < NodeKey(B);
        });
    }

    return OutOrder.Num() == Nodes.Num();
}

static void SortEmitterModuleStack(UNiagaraEmitter* Emitter, const FName& ArrayPropName)
{
    if (!Emitter) return;
    void* TargetContainer = nullptr;
    FArrayProperty* ArrayProp = nullptr;
    if (!ResolveEmitterArrayProperty(Emitter, ArrayPropName, TargetContainer, ArrayProp) || !TargetContainer || !ArrayProp) return;

    FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(TargetContainer));
    if (Helper.Num() <= 1) return;

    FStructProperty* StructProp = CastField<FStructProperty>(ArrayProp->Inner);
    if (!StructProp) return;
    UStruct* StructType = StructProp->Struct;

    struct FEntry
    {
        FString Id;
        EModulePhase Phase = EModulePhase::Unknown;
        TArray<uint8> Data;
        UNiagaraScript* Script = nullptr;
    };

    TArray<FEntry> Entries;
    Entries.Reserve(Helper.Num());
    for (int32 i = 0; i < Helper.Num(); ++i)
    {
        void* ElemPtr = Helper.GetRawPtr(i);
        UNiagaraScript* Script = GetScriptFromEntry(ElemPtr, StructType);
        FEntry Entry;
        Entry.Script = Script;
        Entry.Phase = ClassifyScriptPhase(Script);
        Entry.Id = Script ? Script->GetName() : FString::Printf(TEXT("Unknown_%d"), i);
        Entry.Data.SetNumZeroed(StructProp->GetSize());
        StructProp->CopyCompleteValue(Entry.Data.GetData(), ElemPtr);
        Entries.Add(MoveTemp(Entry));
    }

    // Build nodes + anchors
    TArray<FModuleNode> Nodes;
    TMap<FString, int32> NodeIndex;

    auto AddNode = [&](const FString& Id, EModulePhase Phase, bool bAnchor)
    {
        if (NodeIndex.Contains(Id)) return;
        FModuleNode Node;
        Node.Id = Id;
        Node.Phase = Phase;
        Node.Priority = 0;
        Node.bIsAnchor = bAnchor;
        NodeIndex.Add(Id, Nodes.Num());
        Nodes.Add(Node);
    };

    const EModulePhase PhaseOrder[] = {
        EModulePhase::PreSim, EModulePhase::Forces, EModulePhase::Damping, EModulePhase::Clamp,
        EModulePhase::Integrate, EModulePhase::CollisionDetect, EModulePhase::EventWrite,
        EModulePhase::PostCollisionResponse, EModulePhase::Curves, EModulePhase::RenderPrep, EModulePhase::KillCull
    };

    for (const EModulePhase Phase : PhaseOrder)
    {
        AddNode(FString::Printf(TEXT("@PhaseBegin.%d"), (int32)Phase), Phase, true);
        AddNode(FString::Printf(TEXT("@PhaseEnd.%d"), (int32)Phase), Phase, true);
    }

    for (const FEntry& Entry : Entries)
    {
        AddNode(Entry.Id, Entry.Phase, false);
    }

    // Apply global rules to set phase/priority and constraints
    const TArray<FModuleSortRule> GlobalRules = GetGlobalModuleSortRules();
    for (FModuleNode& Node : Nodes)
    {
        if (Node.bIsAnchor) continue;
        for (const FModuleSortRule& Rule : GlobalRules)
        {
            if (RuleMatches(Rule, Node.Id))
            {
                if (Rule.Phase != EModulePhase::Unknown) Node.Phase = Rule.Phase;
                Node.Priority = FMath::Max(Node.Priority, Rule.Priority);
            }
        }
    }

    // Propagate updated phase to entries
    for (FEntry& Entry : Entries)
    {
        const FModuleNode* Node = Nodes.FindByPredicate([&](const FModuleNode& N) { return N.Id == Entry.Id; });
        if (Node)
        {
            Entry.Phase = Node->Phase;
        }
    }

    TMap<FString, TSet<FString>> Edges;
    // Phase ordering
    for (int32 i = 0; i < UE_ARRAY_COUNT(PhaseOrder) - 1; ++i)
    {
        const FString EndA = FString::Printf(TEXT("@PhaseEnd.%d"), (int32)PhaseOrder[i]);
        const FString BeginB = FString::Printf(TEXT("@PhaseBegin.%d"), (int32)PhaseOrder[i + 1]);
        AddEdge(Edges, EndA, BeginB);
    }

    // Attach modules to their phase anchors
    for (const FEntry& Entry : Entries)
    {
        const FString Begin = FString::Printf(TEXT("@PhaseBegin.%d"), (int32)Entry.Phase);
        const FString End = FString::Printf(TEXT("@PhaseEnd.%d"), (int32)Entry.Phase);
        AddEdge(Edges, Begin, Entry.Id);
        AddEdge(Edges, Entry.Id, End);
    }

    // Apply rule-based before/after constraints
    for (const FModuleSortRule& Rule : GlobalRules)
    {
        for (const FEntry& Entry : Entries)
        {
            if (!RuleMatches(Rule, Entry.Id)) continue;
            if (!Rule.Before.IsEmpty())
            {
                const FString AnchorId = MapVirtualAnchorToNodeId(Rule.Before);
                AddEdge(Edges, Entry.Id, AnchorId);
            }
            if (!Rule.After.IsEmpty())
            {
                const FString AnchorId = MapVirtualAnchorToNodeId(Rule.After);
                AddEdge(Edges, AnchorId, Entry.Id);
            }
        }
    }

    // Hard constraints for collision events
    const FString ForcesEnd = FString::Printf(TEXT("@PhaseEnd.%d"), (int32)EModulePhase::Forces);
    const FString ClampEnd = FString::Printf(TEXT("@PhaseEnd.%d"), (int32)EModulePhase::Clamp);
    const FString CollisionBegin = FString::Printf(TEXT("@PhaseBegin.%d"), (int32)EModulePhase::CollisionDetect);
    const FString CollisionEnd = FString::Printf(TEXT("@PhaseEnd.%d"), (int32)EModulePhase::CollisionDetect);
    const FString EventBegin = FString::Printf(TEXT("@PhaseBegin.%d"), (int32)EModulePhase::EventWrite);
    const FString EventEnd = FString::Printf(TEXT("@PhaseEnd.%d"), (int32)EModulePhase::EventWrite);
    const FString CurvesBegin = FString::Printf(TEXT("@PhaseBegin.%d"), (int32)EModulePhase::Curves);
    AddEdge(Edges, ForcesEnd, CollisionBegin);
    AddEdge(Edges, ClampEnd, CollisionBegin);
    AddEdge(Edges, CollisionEnd, EventBegin);
    AddEdge(Edges, EventEnd, CurvesBegin);

    TArray<FString> Order;
    const bool bOk = TopoSortModules(Nodes, Edges, Order);
    if (!bOk)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Module order constraints cycle detected. Falling back to phase+stable ordering."));
        Order.Reset();
        Entries.Sort([](const FEntry& A, const FEntry& B)
        {
            if (A.Phase != B.Phase) return (int32)A.Phase < (int32)B.Phase;
            return A.Id < B.Id;
        });
        for (const FEntry& E : Entries) Order.Add(E.Id);
    }

    TMap<FString, const FEntry*> EntryMap;
    for (const FEntry& E : Entries) EntryMap.Add(E.Id, &E);

    TArray<const FEntry*> SortedEntries;
    for (const FString& Id : Order)
    {
        if (Id.StartsWith(TEXT("@"))) continue;
        if (const FEntry* Found = EntryMap.FindRef(Id))
        {
            SortedEntries.Add(Found);
        }
    }

    if (SortedEntries.Num() != Entries.Num())
    {
        for (const FEntry& E : Entries)
        {
            if (!SortedEntries.Contains(&E)) SortedEntries.Add(&E);
        }
    }

    Helper.Resize(SortedEntries.Num());
    for (int32 i = 0; i < SortedEntries.Num(); ++i)
    {
        void* ElemPtr = Helper.GetRawPtr(i);
        StructProp->CopyCompleteValue(ElemPtr, SortedEntries[i]->Data.GetData());
    }
}

static void SetStructGuidField(void* StructPtr, UStruct* StructType, const FName& FieldName, const FGuid& Value)
{
    if (!StructPtr || !StructType) return;
    FProperty* Prop = StructType->FindPropertyByName(FieldName);
    if (FStructProperty* StructProp = CastField<FStructProperty>(Prop))
    {
        if (StructProp->Struct == TBaseStructure<FGuid>::Get())
        {
            StructProp->CopyCompleteValue(StructProp->ContainerPtrToValuePtr<void>(StructPtr), &Value);
        }
    }
}

static void SetStructNameField(void* StructPtr, UStruct* StructType, const FName& FieldName, const FName& Value)
{
    if (!StructPtr || !StructType) return;
    FProperty* Prop = StructType->FindPropertyByName(FieldName);
    if (FNameProperty* NameProp = CastField<FNameProperty>(Prop))
    {
        NameProp->SetPropertyValue_InContainer(StructPtr, Value);
    }
}

static void SetStructFloatField(void* StructPtr, UStruct* StructType, const FName& FieldName, float Value)
{
    if (!StructPtr || !StructType) return;
    FProperty* Prop = StructType->FindPropertyByName(FieldName);
    if (FFloatProperty* FloatProp = CastField<FFloatProperty>(Prop))
    {
        FloatProp->SetPropertyValue_InContainer(StructPtr, Value);
    }
    else if (FIntProperty* IntProp = CastField<FIntProperty>(Prop))
    {
        IntProp->SetPropertyValue_InContainer(StructPtr, FMath::RoundToInt(Value));
    }
}

bool FNiagaraSpecExecutor::AddBasicEmitterToSystem(UNiagaraSystem* System, const FString& EmitterName)
{
    if (!System)
    {
        return false;
    }

    const bool bDisallowTemplates = GetVFXAgentSettingBool(TEXT("bDisallowTemplates"), false);
    if (bDisallowTemplates)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Template usage blocked"));
        FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Template usage blocked"));

        // Use the engine's Minimal emitter as a safe initializer even when templates are disallowed.
        // This avoids crashes from uninitialized emitters while still producing a standalone emitter.
        UNiagaraEmitter* EmptyTemplate = LoadObject<UNiagaraEmitter>(nullptr,
            TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal"));
        if (!EmptyTemplate)
        {
            EmptyTemplate = LoadObject<UNiagaraEmitter>(nullptr,
                TEXT("/Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain"));
        }
        if (!EmptyTemplate)
        {
            UE_LOG(LogVFXAgent, Error, TEXT("Failed to load Empty or Minimal emitter template. Cannot create scratch emitter."));
            return false;
        }

        const bool bOriginalInheritable = EmptyTemplate->bIsInheritable;
        EmptyTemplate->bIsInheritable = false;
        const FGuid VersionGuid = EmptyTemplate->GetExposedVersion().VersionGuid;

#if WITH_EDITOR
        const FGuid HandleId = FNiagaraEditorUtilities::AddEmitterToSystem(*System, *EmptyTemplate, VersionGuid, true);
        for (FNiagaraEmitterHandle& EmitterHandle : System->GetEmitterHandles())
        {
            if (EmitterHandle.GetId() == HandleId)
            {
                EmitterHandle.SetName(FName(*EmitterName), *System);
                EmitterHandle.SetIsEnabled(true, *System, true);
                break;
            }
        }
#else
        System->AddEmitterHandle(*EmptyTemplate, FName(*EmitterName), VersionGuid);
#endif

        EmptyTemplate->bIsInheritable = bOriginalInheritable;

        System->MarkPackageDirty();
        if (UPackage* Pkg = System->GetOutermost())
        {
            Pkg->MarkPackageDirty();
        }

        UE_LOG(LogVFXAgent, Log, TEXT("Created scratch emitter '%s' (engine empty initializer)"), *EmitterName);
        AddMinimalModuleChain(System, EmitterName, EVFXRendererType::Sprite);
        return System->GetEmitterHandles().Num() > 0;
    }

#if WITH_EDITOR
    // In UE5.5, we cannot directly create a blank UNiagaraEmitter with NewObject because
    // it doesn't properly initialize the internal structures (scripts, version data, etc.)
    // Instead, we load the "Empty" emitter template which is a truly blank emitter
    // provided by the engine, then add it as a standalone (non-inheriting) copy.
    
    // Try to load the Minimal emitter template - this is a clean emitter with basic modules
    UNiagaraEmitter* EmptyTemplate = LoadObject<UNiagaraEmitter>(nullptr, 
        TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal"));
    
    if (!EmptyTemplate)
    {
        // Fallback: try Fountain template
        EmptyTemplate = LoadObject<UNiagaraEmitter>(nullptr, 
            TEXT("/Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain"));
    }
    
    if (!EmptyTemplate)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to load Empty or Minimal emitter template. Cannot create blank emitter."));
        return false;
    }
    
    UE_LOG(LogVFXAgent, Log, TEXT("Using template '%s' to create blank emitter '%s'"), *EmptyTemplate->GetPathName(), *EmitterName);
    
    // CRITICAL: Set bIsInheritable to false BEFORE calling AddEmitterHandle.
    // This tells the engine to create a fully standalone emitter with no template/parent references.
    const bool bOriginalInheritable = EmptyTemplate->bIsInheritable;
    EmptyTemplate->bIsInheritable = false;
    
    const FGuid VersionGuid = EmptyTemplate->GetExposedVersion().VersionGuid;
    const FGuid HandleId = FNiagaraEditorUtilities::AddEmitterToSystem(*System, *EmptyTemplate, VersionGuid, true);
    for (FNiagaraEmitterHandle& EmitterHandle : System->GetEmitterHandles())
    {
        if (EmitterHandle.GetId() == HandleId)
        {
            EmitterHandle.SetName(FName(*EmitterName), *System);
            EmitterHandle.SetIsEnabled(true, *System, true);
            break;
        }
    }
    
    // Restore original value on template
    EmptyTemplate->bIsInheritable = bOriginalInheritable;
    
    System->MarkPackageDirty();
    if (UPackage* Pkg = System->GetOutermost())
    {
        Pkg->MarkPackageDirty();
    }

    UE_LOG(LogVFXAgent, Log, TEXT("Created blank emitter '%s' from Empty template - no locked modules"), *EmitterName);

    return System->GetEmitterHandles().Num() > 0;
#else
    return false;
#endif
}

bool FNiagaraSpecExecutor::ValidateSpec(const FVFXEffectSpec& Spec, FString& OutError)
{
    if (Spec.Name.IsEmpty())
    {
        OutError = TEXT("Name is empty");
        return false;
    }
    if (Spec.OutputPath.IsEmpty())
    {
        OutError = TEXT("OutputPath is empty");
        return false;
    }
    if (Spec.Emitters.Num() == 0)
    {
        OutError = TEXT("No Emitters defined");
        return false;
    }
    return true;
}

UNiagaraSystem* FNiagaraSpecExecutor::CreateSystemFromSpec(const FVFXEffectSpec& Spec)
{
    UNiagaraSystem* System = CreateNiagaraSystemAsset(Spec.OutputPath, Spec.Name);
    if (!System) return nullptr;

    // Clear any default emitters created by the factory so we only keep generated emitters.
    {
        TArray<FNiagaraEmitterHandle> HandlesCopy = System->GetEmitterHandles();
        for (const FNiagaraEmitterHandle& Handle : HandlesCopy)
        {
            System->RemoveEmitterHandle(Handle);
        }
    }

    for (const FVFXEmitterSpec& EmitterSpec : Spec.Emitters)
    {
        const FString TemplateIdLower = EmitterSpec.TemplateId.ToLower();
        const bool bExplicitNoTemplate =
            TemplateIdLower == TEXT("none") ||
            TemplateIdLower == TEXT("notemplate") ||
            TemplateIdLower == TEXT("auto") ||
            TemplateIdLower == TEXT("generated");

        const bool bUseIntentStrategy = Spec.bHasIntent;
        FTemplateSelectionResult Selection;
        if (bUseIntentStrategy)
        {
            Selection = FVFXTemplateSelector::SelectStrategy(Spec.Intent, EmitterSpec);
        }

        bool bHasTemplate = !EmitterSpec.TemplatePath.IsEmpty() || (!EmitterSpec.TemplateId.IsEmpty() && !bExplicitNoTemplate);
        FString Template;
        if (bUseIntentStrategy)
        {
            const bool bExplicitTemplate = !EmitterSpec.TemplatePath.IsEmpty() || (!EmitterSpec.TemplateId.IsEmpty() && !bExplicitNoTemplate);
            if (bExplicitTemplate)
            {
                Template = EmitterSpec.TemplatePath;
                if (Template.IsEmpty()) Template = FindTemplatePath(EmitterSpec.TemplateId);
            }
            else
            {
                if (Selection.Strategy == EConstructionStrategy::BuildFromScratch)
                {
                    bHasTemplate = false;
                }
                else
                {
                    Template = Selection.TemplatePath;
                    bHasTemplate = !Template.IsEmpty();
                }
            }

            UE_LOG(LogVFXAgent, Log, TEXT("Emitter '%s' strategy: %s | Template: %s | Reason: %s"),
                *EmitterSpec.Name,
                StrategyToString(Selection.Strategy),
                *Template,
                *Selection.StrategyReason);
        }

        const bool bDisallowTemplates = GetVFXAgentSettingBool(TEXT("bDisallowTemplates"), false);
        if (bDisallowTemplates)
        {
            bHasTemplate = false;
            Template.Empty();
            UE_LOG(LogVFXAgent, Error, TEXT("Template usage blocked"));
            FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Template usage blocked"));
        }

        bool bAdded = false;
        if (bHasTemplate)
        {
            if (Template.IsEmpty())
            {
                Template = EmitterSpec.TemplatePath;
                if (Template.IsEmpty()) Template = FindTemplatePath(EmitterSpec.TemplateId);
            }

            bAdded = AddEmitterFromTemplate(System, Template, EmitterSpec.Name);
            if (!bAdded)
            {
                UE_LOG(LogVFXAgent, Warning, TEXT("Failed to add emitter from template '%s'. Falling back to Minimal."), *Template);
                bAdded = AddEmitterFromTemplate(System, FindTemplatePath(TEXT("Minimal")), EmitterSpec.Name);
            }
        }
        else
        {
            bAdded = FNiagaraSpecExecutor::AddBasicEmitterToSystem(System, EmitterSpec.Name);
        }

        if (!bAdded)
        {
            UE_LOG(LogVFXAgent, Error, TEXT("Failed to add emitter '%s'."), *EmitterSpec.Name);
            continue;
        }

        ConfigureEmitter(System, EmitterSpec.Name, EmitterSpec);

        if (bUseIntentStrategy)
        {
            ApplyIntentModuleRules(System, EmitterSpec.Name, Spec.Intent, Selection);
        }
    }

    if (System->GetEmitterHandles().Num() == 0)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("No emitters were added to system '%s'."), *Spec.Name);
        return nullptr;
    }

    // CRITICAL FIX: Properly initialize the Niagara System for preview display
    // This sequence ensures the system is fully ready for the Niagara Editor
    
#if WITH_EDITOR
    // Step 1: Enable all emitters and ensure they are not isolated
    for (int32 i = 0; i < System->GetNumEmitters(); ++i)
    {
        FNiagaraEmitterHandle& EmitterHandle = System->GetEmitterHandle(i);
        EmitterHandle.SetIsEnabled(true, *System, true);
        
        // Ensure the emitter is not isolated (which would hide it in System Overview)
        // In UE5, isolation state is controlled via the editor data
    }

    // Step 2: Ensure the System Overview graph is synchronized with the current emitters
    UNiagaraSystemEditorData* SystemEditorData = Cast<UNiagaraSystemEditorData>(System->GetEditorData());
    if (SystemEditorData)
    {
        SystemEditorData->SynchronizeOverviewGraphWithSystem(*System);
    }
    else
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Editor data missing, system overview may not display correctly"));
    }

    // Step 3: Mark packages dirty to ensure changes are persisted
    System->MarkPackageDirty();
    if (UPackage* Pkg = System->GetOutermost())
    {
        Pkg->MarkPackageDirty();
    }
    
    // Step 4: Force a full recompile of the system
    // Use bForce=true to ensure complete recompilation
    System->RequestCompile(true);
    
    // Step 5: Wait for compilation to complete (blocking)
    // This ensures the system is fully compiled before display
    System->WaitForCompilationComplete(true, true);
    
    // Step 6: Invalidate cached data to force refresh on next access
    System->InvalidateCachedData();
    
    // Step 7: Broadcast PostEditChange to notify any open Niagara Editors
    // This triggers the editor to refresh its preview and system overview
    // (Deferred to the final save/compile step to avoid duplicate validation runs)
    // System->PostEditChange();
    
    UE_LOG(LogVFXAgent, Log, TEXT("System '%s' fully initialized with %d emitters for preview"), 
           *Spec.Name, System->GetNumEmitters());
#endif

    return System;
}

// Helper to retrieve renderer properties from a UNiagaraEmitter using reflection.
static TArray<UNiagaraRendererProperties*> GetEmitterRenderers(UNiagaraEmitter* Emitter)
{
    TArray<UNiagaraRendererProperties*> Result;
    if (!Emitter) return Result;

    // Try common property names that engines have used.
    const FName PossibleNames[] = { TEXT("RendererProperties"), TEXT("Renderers") };

    for (const FName& Name : PossibleNames)
    {
        FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), Name);
        if (!ArrayProp) continue;

        FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
        FObjectPropertyBase* InnerObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner);
        if (!InnerObjProp) break;

        for (int32 i = 0; i < Helper.Num(); ++i)
        {
            void* ElemPtr = Helper.GetRawPtr(i);
            UObject* Obj = InnerObjProp->GetObjectPropertyValue(ElemPtr);
            if (UNiagaraRendererProperties* RP = Cast<UNiagaraRendererProperties>(Obj))
            {
                Result.Add(RP);
            }
        }

        break; // stop after first successful property
    }

    return Result;
}

static void RemoveMismatchedRenderers(UNiagaraEmitter* Emitter, EVFXRendererType DesiredType)
{
    if (!Emitter) return;
    const FName PossibleNames[] = { TEXT("RendererProperties"), TEXT("Renderers") };
    for (const FName& Name : PossibleNames)
    {
        FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), Name);
        if (!ArrayProp) continue;
        FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
        FObjectPropertyBase* InnerObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner);
        if (!InnerObjProp) break;

        for (int32 i = Helper.Num() - 1; i >= 0; --i)
        {
            void* ElemPtr = Helper.GetRawPtr(i);
            UObject* Obj = InnerObjProp->GetObjectPropertyValue(ElemPtr);
            UNiagaraRendererProperties* RP = Cast<UNiagaraRendererProperties>(Obj);
            if (!RP)
            {
                Helper.RemoveValues(i, 1);
                continue;
            }

            const bool bMatch =
                (DesiredType == EVFXRendererType::Sprite && RP->IsA<UNiagaraSpriteRendererProperties>()) ||
                (DesiredType == EVFXRendererType::Ribbon && RP->IsA<UNiagaraRibbonRendererProperties>()) ||
                (DesiredType == EVFXRendererType::Mesh && RP->IsA<UNiagaraMeshRendererProperties>()) ||
                (DesiredType == EVFXRendererType::Light && RP->IsA<UNiagaraLightRendererProperties>());
            if (!bMatch)
            {
                Helper.RemoveValues(i, 1);
            }
        }

        break;
    }

    Emitter->Modify();
    Emitter->PostEditChange();
}

static bool IsRendererOfType(UNiagaraRendererProperties* Renderer, EVFXRendererType DesiredType)
{
    if (!Renderer) return false;
    switch (DesiredType)
    {
        case EVFXRendererType::Sprite:
            return Renderer->IsA<UNiagaraSpriteRendererProperties>();
        case EVFXRendererType::Ribbon:
            return Renderer->IsA<UNiagaraRibbonRendererProperties>();
        case EVFXRendererType::Mesh:
            return Renderer->IsA<UNiagaraMeshRendererProperties>();
        case EVFXRendererType::Light:
            return Renderer->IsA<UNiagaraLightRendererProperties>();
        default:
            return false;
    }
}

static UMaterialInterface* GetMaterialFromStruct(void* StructPtr, UStruct* Struct)
{
    if (!StructPtr || !Struct)
    {
        return nullptr;
    }

    for (TFieldIterator<FObjectPropertyBase> It(Struct); It; ++It)
    {
        FObjectPropertyBase* Prop = *It;
        if (!Prop)
        {
            continue;
        }
        if (Prop->PropertyClass->IsChildOf(UMaterialInterface::StaticClass()) && Prop->GetName().Contains(TEXT("Material")))
        {
            return Cast<UMaterialInterface>(Prop->GetObjectPropertyValue_InContainer(StructPtr));
        }
    }

    return nullptr;
}

static bool SetMaterialOnStruct(void* StructPtr, UStruct* Struct, UMaterialInterface* Material)
{
    if (!StructPtr || !Struct || !Material)
    {
        return false;
    }

    for (TFieldIterator<FObjectPropertyBase> It(Struct); It; ++It)
    {
        FObjectPropertyBase* Prop = *It;
        if (!Prop)
        {
            continue;
        }
        if (Prop->PropertyClass->IsChildOf(UMaterialInterface::StaticClass()) && Prop->GetName().Contains(TEXT("Material")))
        {
            Prop->SetObjectPropertyValue_InContainer(StructPtr, Material);
            return true;
        }
    }

    return false;
}

static UMaterialInterface* GetRendererMaterialAny(UNiagaraRendererProperties* Renderer)
{
    if (!Renderer)
    {
        return nullptr;
    }

    if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Renderer))
    {
        return Sprite->Material;
    }
    if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Renderer))
    {
        return Ribbon->Material;
    }

    const FName PossibleNames[] = { TEXT("OverrideMaterials"), TEXT("Materials") };
    for (const FName& Name : PossibleNames)
    {
        FArrayProperty* MaterialsProp = FindFProperty<FArrayProperty>(Renderer->GetClass(), Name);
        if (!MaterialsProp)
        {
            continue;
        }
        FScriptArrayHelper Helper(MaterialsProp, MaterialsProp->ContainerPtrToValuePtr<void>(Renderer));
        if (Helper.Num() > 0)
        {
            void* ElemPtr = Helper.GetRawPtr(0);
            if (FStructProperty* StructProp = CastField<FStructProperty>(MaterialsProp->Inner))
            {
                if (UMaterialInterface* Mat = GetMaterialFromStruct(ElemPtr, StructProp->Struct))
                {
                    return Mat;
                }
            }
            else if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(MaterialsProp->Inner))
            {
                return Cast<UMaterialInterface>(ObjProp->GetObjectPropertyValue(ElemPtr));
            }
        }
    }

    return nullptr;
}

static bool SetRendererMaterialAny(UNiagaraRendererProperties* Renderer, UMaterialInterface* Material)
{
    if (!Renderer || !Material)
    {
        return false;
    }

    if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Renderer))
    {
        Sprite->Material = Material;
        return true;
    }
    if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Renderer))
    {
        Ribbon->Material = Material;
        return true;
    }

    const FName PossibleNames[] = { TEXT("OverrideMaterials"), TEXT("Materials") };
    for (const FName& Name : PossibleNames)
    {
        FArrayProperty* MaterialsProp = FindFProperty<FArrayProperty>(Renderer->GetClass(), Name);
        if (!MaterialsProp)
        {
            continue;
        }
        FScriptArrayHelper Helper(MaterialsProp, MaterialsProp->ContainerPtrToValuePtr<void>(Renderer));
        if (Helper.Num() == 0)
        {
            Helper.AddValue();
        }
        void* ElemPtr = Helper.GetRawPtr(0);
        if (FStructProperty* StructProp = CastField<FStructProperty>(MaterialsProp->Inner))
        {
            if (SetMaterialOnStruct(ElemPtr, StructProp->Struct, Material))
            {
                return true;
            }
        }
        else if (FObjectPropertyBase* ObjProp = CastField<FObjectPropertyBase>(MaterialsProp->Inner))
        {
            ObjProp->SetObjectPropertyValue(ElemPtr, Material);
            return true;
        }
    }

    return false;
}

static bool RendererHasMaterial(UNiagaraRendererProperties* Renderer)
{
    if (!Renderer)
    {
        return false;
    }
    if (Renderer->IsA<UNiagaraLightRendererProperties>())
    {
        return true;
    }
    return GetRendererMaterialAny(Renderer) != nullptr;
}

static UMaterialInterface* GetDefaultParticleMaterial()
{
    static TWeakObjectPtr<UMaterialInterface> Cached;
    if (!Cached.IsValid())
    {
        Cached = LoadObject<UMaterialInterface>(nullptr, TEXT("/Niagara/DefaultAssets/DefaultSpriteMaterial.DefaultSpriteMaterial"));
    }
    if (!Cached.IsValid())
    {
        Cached = LoadObject<UMaterialInterface>(nullptr, TEXT("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"));
    }
    return Cached.Get();
}

static bool IsDefaultEngineMaterial(UMaterialInterface* Material)
{
    if (!Material) return true;
    const FString Path = Material->GetPathName().ToLower();
    return Path.Contains(TEXT("/niagara/defaultassets/defaultspritematerial")) ||
           Path.Contains(TEXT("/engine/enginematerials/defaultmaterial")) ||
           Path.Contains(TEXT("/engine/enginematerials/particlespritematerial"));
}

static TArray<FAssetData> GatherMaterialLibraryAssets()
{
    static bool bInitialized = false;
    static TArray<FAssetData> CachedAssets;
    if (bInitialized)
    {
        return CachedAssets;
    }

    TArray<FString> Paths = GetVFXAgentSettingArray(TEXT("MaterialLibraryPaths"));
    if (Paths.Num() == 0)
    {
        Paths = {
            TEXT("/Game/VFX/Materials"),
            TEXT("/Game/VFX/MaterialLibrary"),
            TEXT("/Game/VFXAgent/Materials"),
            TEXT("/Game/FX/Materials")
        };
    }

    EnsureAssetRegistryReady();
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter Filter;
    Filter.ClassPaths.Add(UMaterial::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UMaterialInstance::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UMaterialInstanceConstant::StaticClass()->GetClassPathName());
    Filter.bRecursivePaths = true;

    for (const FString& Path : Paths)
    {
        if (!Path.IsEmpty())
        {
            Filter.PackagePaths.Add(*Path);
        }
    }

    AssetRegistryModule.Get().GetAssets(Filter, CachedAssets);
    bInitialized = true;
    return CachedAssets;
}

static int32 ScoreMaterialCandidate(const FString& LowerName, const FString& LowerPath, const TArray<FString>& Keywords)
{
    int32 Score = 0;
    for (const FString& K : Keywords)
    {
        if (LowerName.Contains(K) || LowerPath.Contains(K))
        {
            Score += 5;
        }
    }

    if (LowerPath.StartsWith(TEXT("/game/")))
    {
        Score += 3;
    }
    if (LowerPath.Contains(TEXT("default")) || LowerPath.Contains(TEXT("placeholder")) || LowerPath.Contains(TEXT("debug")))
    {
        Score -= 4;
    }
    if (LowerPath.StartsWith(TEXT("/engine/")) || LowerPath.StartsWith(TEXT("/niagara/")))
    {
        Score -= 10;
    }

    return Score;
}

static void BuildMaterialKeywords(const FVFXIntent& Intent, const FString& EmitterName, TArray<FString>& OutKeywords)
{
    const FString Archetype = UEnum::GetValueAsString(Intent.Archetype).ToLower();
    if (Archetype.Contains(TEXT("tornado"))) { OutKeywords.Add(TEXT("tornado")); OutKeywords.Add(TEXT("vortex")); OutKeywords.Add(TEXT("swirl")); }
    if (Archetype.Contains(TEXT("explosion"))) { OutKeywords.Add(TEXT("explosion")); OutKeywords.Add(TEXT("burst")); OutKeywords.Add(TEXT("shock")); }
    if (Archetype.Contains(TEXT("fire"))) { OutKeywords.Add(TEXT("fire")); OutKeywords.Add(TEXT("flame")); OutKeywords.Add(TEXT("ember")); }
    if (Archetype.Contains(TEXT("smoke"))) { OutKeywords.Add(TEXT("smoke")); OutKeywords.Add(TEXT("fog")); OutKeywords.Add(TEXT("cloud")); }
    if (Archetype.Contains(TEXT("aura"))) { OutKeywords.Add(TEXT("aura")); OutKeywords.Add(TEXT("magic")); OutKeywords.Add(TEXT("glow")); }
    if (Archetype.Contains(TEXT("trail"))) { OutKeywords.Add(TEXT("trail")); OutKeywords.Add(TEXT("ribbon")); }
    if (Archetype.Contains(TEXT("beam"))) { OutKeywords.Add(TEXT("beam")); OutKeywords.Add(TEXT("laser")); }
    if (Archetype.Contains(TEXT("dust"))) { OutKeywords.Add(TEXT("dust")); OutKeywords.Add(TEXT("sand")); }
    if (Archetype.Contains(TEXT("sparks"))) { OutKeywords.Add(TEXT("spark")); OutKeywords.Add(TEXT("sparkle")); }
    if (Archetype.Contains(TEXT("impact"))) { OutKeywords.Add(TEXT("impact")); OutKeywords.Add(TEXT("hit")); }

    const FString NameLower = EmitterName.ToLower();
    if (NameLower.Contains(TEXT("core"))) OutKeywords.Add(TEXT("core"));
    if (NameLower.Contains(TEXT("smoke"))) OutKeywords.Add(TEXT("smoke"));
    if (NameLower.Contains(TEXT("dust"))) OutKeywords.Add(TEXT("dust"));
    if (NameLower.Contains(TEXT("debris"))) OutKeywords.Add(TEXT("debris"));
    if (NameLower.Contains(TEXT("trail"))) OutKeywords.Add(TEXT("trail"));
    if (NameLower.Contains(TEXT("ribbon"))) OutKeywords.Add(TEXT("ribbon"));
    if (NameLower.Contains(TEXT("beam"))) OutKeywords.Add(TEXT("beam"));
    if (NameLower.Contains(TEXT("spark"))) OutKeywords.Add(TEXT("spark"));
}

static UMaterialInterface* SelectPreferredMaterialFromLibrary(const FVFXIntent& Intent, const FString& EmitterName)
{
    const TArray<FAssetData> Assets = GatherMaterialLibraryAssets();
    if (Assets.Num() == 0)
    {
        return nullptr;
    }

    TArray<FString> Keywords;
    BuildMaterialKeywords(Intent, EmitterName, Keywords);

    int32 BestScore = MIN_int32;
    const FAssetData* BestAsset = nullptr;

    for (const FAssetData& Asset : Assets)
    {
        const FString NameLower = Asset.AssetName.ToString().ToLower();
        const FString PathLower = Asset.GetObjectPathString().ToLower();
        const int32 Score = ScoreMaterialCandidate(NameLower, PathLower, Keywords);
        if (Score > BestScore)
        {
            BestScore = Score;
            BestAsset = &Asset;
        }
    }

    if (!BestAsset)
    {
        return nullptr;
    }

    return Cast<UMaterialInterface>(BestAsset->GetAsset());
}

static void ApplyPreferredMaterialToEmitter(UNiagaraEmitter* Emitter, UMaterialInterface* PreferredMaterial)
{
    if (!Emitter || !PreferredMaterial) return;

    TArray<UNiagaraRendererProperties*> Renderers = GetEmitterRenderers(Emitter);
    for (UNiagaraRendererProperties* Renderer : Renderers)
    {
        if (!Renderer) continue;

        UMaterialInterface* Current = FVFXRendererValidationFixer::GetRendererMaterial(Renderer);
        if (!Current || IsDefaultEngineMaterial(Current))
        {
            FVFXRendererValidationFixer::SetRendererMaterial(Renderer, PreferredMaterial);
        }
    }

    Emitter->Modify();
    Emitter->PostEditChange();
}

static void EnsureRendererMaterial(UNiagaraRendererProperties* Renderer)
{
    if (!Renderer) return;
    UMaterialInterface* DefaultMat = GetDefaultParticleMaterial();
    if (!DefaultMat) return;

    if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Renderer))
    {
        if (!Sprite->Material)
        {
            Sprite->Material = DefaultMat;
        }
    }
    else if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Renderer))
    {
        if (!Ribbon->Material)
        {
            Ribbon->Material = DefaultMat;
        }
    }
    else
    {
        SetRendererMaterialAny(Renderer, DefaultMat);
    }
}

static UNiagaraEmitter* FindEmitterInstanceByName(UNiagaraSystem* System, const FString& EmitterName)
{
    if (!System) return nullptr;
    for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
    {
        if (H.GetName() == FName(*EmitterName) || H.GetName() == FName(*(EmitterName + "0")))
        {
            return H.GetInstance().Emitter;
        }
    }
    if (System->GetEmitterHandles().Num() > 0)
    {
        return System->GetEmitterHandles().Last().GetInstance().Emitter;
    }
    return nullptr;
}

static void ApplyIntentModuleRules(
    UNiagaraSystem* System,
    const FString& EmitterName,
    const FVFXIntent& Intent,
    const FTemplateSelectionResult& Selection)
{
    UNiagaraEmitter* Emitter = FindEmitterInstanceByName(System, EmitterName);
    if (!Emitter)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("ApplyIntentModuleRules: emitter not found: %s"), *EmitterName);
        return;
    }

    FMotionBehaviorConfig MotionConfig = FVFXMotionModuleLibrary::GetMotionConfigByArchetype(
        FVFXMotionModuleLibrary::DetermineMotionArchetype(Intent));

    // Strip forbidden modules
    if (Selection.ModulesToStrip.Num() > 0)
    {
        FModuleStripResult StripResult = FVFXModuleStripper::StripModulesByPattern(Emitter, Selection.ModulesToStrip);
        UE_LOG(LogVFXAgent, Log, TEXT("ModuleStripper: removed %d modules for %s"), StripResult.ModulesRemoved, *EmitterName);
        if (StripResult.FailedToRemove.Num() > 0)
        {
            UE_LOG(LogVFXAgent, Warning, TEXT("ModuleStripper failures (%s): %s"), *EmitterName, *FString::Join(StripResult.FailedToRemove, TEXT(", ")));
        }
    }

    if (Selection.bMustStripAllVelocity)
    {
        FModuleStripResult StripResult = FVFXModuleStripper::StripAllVelocityModules(Emitter);
        UE_LOG(LogVFXAgent, Log, TEXT("ModuleStripper: removed velocity modules (%d) for %s"), StripResult.ModulesRemoved, *EmitterName);
    }
    if (Selection.bMustStripGravity)
    {
        FModuleStripResult StripResult = FVFXModuleStripper::StripGravityModules(Emitter);
        UE_LOG(LogVFXAgent, Log, TEXT("ModuleStripper: removed gravity modules (%d) for %s"), StripResult.ModulesRemoved, *EmitterName);
    }
    if (Selection.bMustStripNoise)
    {
        FModuleStripResult StripResult = FVFXModuleStripper::StripNoiseModules(Emitter);
        UE_LOG(LogVFXAgent, Log, TEXT("ModuleStripper: removed noise modules (%d) for %s"), StripResult.ModulesRemoved, *EmitterName);
    }

    // Insert required motion modules
    FModuleInsertResult InsertResult = FVFXModuleInserter::InsertModules(Emitter, MotionConfig.RequiredModules, EmitterName);
    if (InsertResult.ModulesInserted > 0)
    {
        UE_LOG(LogVFXAgent, Log, TEXT("ModuleInserter: inserted %d modules for %s"), InsertResult.ModulesInserted, *EmitterName);
    }

    // Apply motion parameter defaults
    TMap<FString, float> MotionParams = FVFXMotionModuleLibrary::GenerateMotionParameters(MotionConfig.Archetype, Intent);
    for (const TPair<FString, float>& KV : MotionParams)
    {
        FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, KV.Key, KV.Value);
    }
    for (const FMotionModuleDescriptor& Module : MotionConfig.RequiredModules)
    {
        for (const TPair<FString, float>& ParamKV : Module.DefaultParams)
        {
            FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, ParamKV.Key, ParamKV.Value);
        }
    }

    // Renderer validation and cleanup (remove None renderers)
    UMaterialInterface* PreferredMat = SelectPreferredMaterialFromLibrary(Intent, EmitterName);
    UMaterialInterface* DefaultMat = PreferredMat ? PreferredMat : GetDefaultParticleMaterial();
    FRendererValidationReport RenderReport = FVFXRendererValidationFixer::ValidateAndFixRenderers(Emitter, DefaultMat);
    if (RenderReport.InvalidRenderersRemoved > 0 || RenderReport.RenderersFixed > 0)
    {
        UE_LOG(LogVFXAgent, Log, TEXT("RendererValidationFixer: %s"), *RenderReport.Summary);
    }

    // Replace default materials with preferred library material when possible
    if (PreferredMat)
    {
        ApplyPreferredMaterialToEmitter(Emitter, PreferredMat);
    }
}

static void EnsureSingleRendererHasMaterial(UNiagaraEmitter* Emitter, EVFXRendererType DesiredType)
{
    if (!Emitter) return;

    TArray<UNiagaraRendererProperties*> Renderers = GetEmitterRenderers(Emitter);
    UNiagaraRendererProperties* FirstMatch = nullptr;
    for (UNiagaraRendererProperties* RP : Renderers)
    {
        if (IsRendererOfType(RP, DesiredType))
        {
            FirstMatch = RP;
            break;
        }
    }

    if (FirstMatch)
    {
        EnsureRendererMaterial(FirstMatch);
        Emitter->Modify();
        Emitter->PostEditChange();
    }
}

static void PruneDuplicateRenderers(UNiagaraEmitter* Emitter, EVFXRendererType DesiredType)
{
    if (!Emitter) return;

    const FName PossibleNames[] = { TEXT("RendererProperties"), TEXT("Renderers") };
    for (const FName& Name : PossibleNames)
    {
        FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), Name);
        if (!ArrayProp) continue;

        FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
        FObjectPropertyBase* InnerObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner);
        if (!InnerObjProp) break;

        TArray<int32> MatchingIndices;
        for (int32 i = 0; i < Helper.Num(); ++i)
        {
            void* ElemPtr = Helper.GetRawPtr(i);
            UObject* Obj = InnerObjProp->GetObjectPropertyValue(ElemPtr);
            UNiagaraRendererProperties* RP = Cast<UNiagaraRendererProperties>(Obj);
            if (IsRendererOfType(RP, DesiredType))
            {
                MatchingIndices.Add(i);
            }
        }

        if (MatchingIndices.Num() <= 1)
        {
            break;
        }

        int32 KeepIndex = MatchingIndices[0];
        if (DesiredType == EVFXRendererType::Sprite || DesiredType == EVFXRendererType::Ribbon)
        {
            for (int32 Idx : MatchingIndices)
            {
                void* ElemPtr = Helper.GetRawPtr(Idx);
                UObject* Obj = InnerObjProp->GetObjectPropertyValue(ElemPtr);
                UNiagaraRendererProperties* RP = Cast<UNiagaraRendererProperties>(Obj);
                if (RendererHasMaterial(RP))
                {
                    KeepIndex = Idx;
                    break;
                }
            }
        }

        for (int32 i = MatchingIndices.Num() - 1; i >= 0; --i)
        {
            const int32 Index = MatchingIndices[i];
            if (Index != KeepIndex)
            {
                Helper.RemoveValues(Index, 1);
            }
        }

        break;
    }

    Emitter->Modify();
    Emitter->PostEditChange();
}

static void GatherEmitterScripts(UNiagaraEmitter* Emitter, TArray<UNiagaraScript*>& OutScripts)
{
    OutScripts.Reset();
    if (!Emitter) return;
    ForEachObjectWithOuter(Emitter, [&OutScripts](UObject* Obj)
    {
        if (UNiagaraScript* Script = Cast<UNiagaraScript>(Obj))
        {
            OutScripts.AddUnique(Script);
        }
    }, true);
}

static bool TrySetFloatInStore(FNiagaraParameterStore& Store, const FString& NameContains, float Value)
{
    for (const FNiagaraVariableWithOffset& ParamWithOffset : Store.ReadParameterVariables())
    {
        if (ParamWithOffset.GetType() != FNiagaraTypeDefinition::GetFloatDef())
        {
            continue;
        }
        const FString VarName = ParamWithOffset.GetName().ToString();
        if (!VarName.Contains(NameContains, ESearchCase::IgnoreCase))
        {
            continue;
        }

        FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
        return Store.SetParameterData(reinterpret_cast<const uint8*>(&Value), Param, false);
    }
    return false;
}

static bool TrySetIntInStore(FNiagaraParameterStore& Store, const FString& NameContains, int32 Value)
{
    for (const FNiagaraVariableWithOffset& ParamWithOffset : Store.ReadParameterVariables())
    {
        if (ParamWithOffset.GetType() != FNiagaraTypeDefinition::GetIntDef())
        {
            continue;
        }
        const FString VarName = ParamWithOffset.GetName().ToString();
        if (!VarName.Contains(NameContains, ESearchCase::IgnoreCase))
        {
            continue;
        }

        FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
        return Store.SetParameterData(reinterpret_cast<const uint8*>(&Value), Param, false);
    }
    return false;
}

static bool TrySetVec3InStore(FNiagaraParameterStore& Store, const FString& NameContains, const FVector& Value)
{
    for (const FNiagaraVariableWithOffset& ParamWithOffset : Store.ReadParameterVariables())
    {
        if (ParamWithOffset.GetType() != FNiagaraTypeDefinition::GetVec3Def())
        {
            continue;
        }
        const FString VarName = ParamWithOffset.GetName().ToString();
        if (!VarName.Contains(NameContains, ESearchCase::IgnoreCase))
        {
            continue;
        }

        const FVector3f Value3f((float)Value.X, (float)Value.Y, (float)Value.Z);
        FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
        return Store.SetParameterData(reinterpret_cast<const uint8*>(&Value3f), Param, false);
    }
    return false;
}

static bool TrySetColorInStore(FNiagaraParameterStore& Store, const FString& NameContains, const FLinearColor& Value)
{
    for (const FNiagaraVariableWithOffset& ParamWithOffset : Store.ReadParameterVariables())
    {
        const FString VarName = ParamWithOffset.GetName().ToString();
        if (!VarName.Contains(NameContains, ESearchCase::IgnoreCase))
        {
            continue;
        }

        if (ParamWithOffset.GetType() == FNiagaraTypeDefinition::GetColorDef())
        {
            FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
            return Store.SetParameterData(reinterpret_cast<const uint8*>(&Value), Param, false);
        }
        if (ParamWithOffset.GetType() == FNiagaraTypeDefinition::GetVec4Def())
        {
            const FVector4f V(Value.R, Value.G, Value.B, Value.A);
            FNiagaraVariable Param(ParamWithOffset.GetType(), ParamWithOffset.GetName());
            return Store.SetParameterData(reinterpret_cast<const uint8*>(&V), Param, false);
        }
    }
    return false;
}

static void SetEmitterLocalSpace(UNiagaraEmitter* Emitter, bool bLocalSpace)
{
    if (!Emitter) return;
    FBoolProperty* BoolProp = FindFProperty<FBoolProperty>(Emitter->GetClass(), TEXT("bLocalSpace"));
    if (BoolProp)
    {
        BoolProp->SetPropertyValue_InContainer(Emitter, bLocalSpace);
        Emitter->Modify();
        Emitter->PostEditChange();
    }
}

UNiagaraSystem* FNiagaraSpecExecutor::CreateNiagaraSystemAsset(const FString& TargetPath, const FString& SystemName)
{
    IAssetTools& AssetTools = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    
    // Ensure the system name does not contain whitespace or invalid characters
    FString SafeSystemName = SanitizeNiagaraIdentifier(SystemName, TEXT("GeneratedSystem"));
    
    FString PackageName = FPaths::Combine(TargetPath, SafeSystemName);
    
    // Create a new Niagara System using the Factory
    UFactory* Factory = NewObject<UFactory>(GetTransientPackage(), FindObject<UClass>(nullptr, TEXT("/Script/NiagaraEditor.NiagaraSystemFactoryNew")));
    if (!Factory) return nullptr;

    UObject* NewAsset = AssetTools.CreateAsset(SafeSystemName, TargetPath, UNiagaraSystem::StaticClass(), Factory);
    return Cast<UNiagaraSystem>(NewAsset);
}

bool FNiagaraSpecExecutor::AddModuleToEmitter(UNiagaraSystem* System, const FString& EmitterName, const FString& ModuleScriptPath, const FString& StackName)
{
    if (!System) return false;

    const FString SafeEmitterName = SanitizeNiagaraIdentifier(EmitterName, TEXT("Emitter"));

    FNiagaraEmitterHandle* Handle = nullptr;
    for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
    {
        if (H.GetName() == FName(*EmitterName) || H.GetName() == FName(*SafeEmitterName))
        {
            Handle = &H;
            break;
        }
    }
    if (!Handle && System->GetEmitterHandles().Num() > 0)
    {
        Handle = &System->GetEmitterHandles().Last();
    }
    if (!Handle) return false;

    FVersionedNiagaraEmitter VersionedEmitter = Handle->GetInstance();
    UNiagaraEmitter* EmitterInstance = VersionedEmitter.Emitter;
    if (!EmitterInstance) return false;

    UNiagaraScript* Script = LoadNiagaraScriptFromPath(ModuleScriptPath);
    if (!Script)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("AddModuleToEmitter: failed to load script '%s'"), *ModuleScriptPath);
        return false;
    }

    FName ArrayPropName(TEXT("ParticleUpdateScriptProps"));
    const FString Lower = StackName.ToLower();
    if (Lower.Contains(TEXT("spawn")) && Lower.Contains(TEXT("particle"))) ArrayPropName = TEXT("ParticleSpawnScriptProps");
    else if (Lower.Contains(TEXT("update")) && Lower.Contains(TEXT("particle"))) ArrayPropName = TEXT("ParticleUpdateScriptProps");
    else if (Lower.Contains(TEXT("emitter")) && Lower.Contains(TEXT("spawn"))) ArrayPropName = TEXT("EmitterSpawnScriptProps");
    else if (Lower.Contains(TEXT("emitter")) && Lower.Contains(TEXT("update"))) ArrayPropName = TEXT("EmitterUpdateScriptProps");
    else if (Lower.Contains(TEXT("event"))) ArrayPropName = TEXT("EventHandlerScriptProps");
    else if (!StackName.IsEmpty()) ArrayPropName = FName(*StackName);

    FModuleInsertOptions Options;
    Options.Mode = TEXT("Last");

    const bool bInserted = InsertScriptWithOrdering(EmitterInstance, ArrayPropName, Script, Options);
    SortEmitterModuleStack(EmitterInstance, ArrayPropName);

    EmitterInstance->Modify();
    EmitterInstance->PostEditChange();
    if (bInserted)
    {
        MarkSystemDirtyAndFullRecompile(System, TEXT("AddModuleToEmitter"));
    }
    return bInserted;
}

bool FNiagaraSpecExecutor::AddEmitterFromTemplate(UNiagaraSystem* System, const FString& TemplatePath, const FString& EmitterName)
{
    if (!System) return false;

    const FString SafeEmitterName = SanitizeNiagaraIdentifier(EmitterName, TEXT("Emitter"));

    const bool bDisallowTemplates = GetVFXAgentSettingBool(TEXT("bDisallowTemplates"), false);
    if (bDisallowTemplates)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Template usage blocked"));
        FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::Niagara, TEXT("Template usage blocked"));
        return false;
    }

    const FString ObjectPath = NormalizeTemplateObjectPath(TemplatePath);
    if (ObjectPath.IsEmpty())
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Template path is empty for emitter '%s'. Creating basic emitter instead."), *SafeEmitterName);
        return AddBasicEmitterToSystem(System, SafeEmitterName);
    }

    // First try loading as a Niagara System (system templates contain emitters)
    UNiagaraSystem* TemplateSystem = LoadObject<UNiagaraSystem>(nullptr, *ObjectPath);
    if (!TemplateSystem)
    {
        // Try to load an emitter template directly
        UNiagaraEmitter* TemplateEmitter = LoadObject<UNiagaraEmitter>(nullptr, *ObjectPath);
        if (TemplateEmitter)
        {
            UE_LOG(LogVFXAgent, Log, TEXT("Loaded emitter template: %s"), *ObjectPath);
            
            // CRITICAL: Set bIsInheritable to false BEFORE calling AddEmitterHandle.
            // This tells the engine's AddEmitterHandle to call DisableVersioning and RemoveParent internally,
            // which creates a fully standalone emitter with no template/parent references.
            const bool bOriginalInheritable = TemplateEmitter->bIsInheritable;
            TemplateEmitter->bIsInheritable = false;
            
            // Get a valid version GUID from the template
            const FGuid VersionGuid = TemplateEmitter->GetExposedVersion().VersionGuid;
            
#if WITH_EDITOR
            // Add via editor utility to ensure overview graph and editor data stay in sync
            const FGuid HandleId = FNiagaraEditorUtilities::AddEmitterToSystem(*System, *TemplateEmitter, VersionGuid, true);
            for (FNiagaraEmitterHandle& SystemHandle : System->GetEmitterHandles())
            {
                if (SystemHandle.GetId() == HandleId)
                {
                    SystemHandle.SetName(FName(*SafeEmitterName), *System);
                    SystemHandle.SetIsEnabled(true, *System, true);
                    break;
                }
            }
#else
            System->AddEmitterHandle(*TemplateEmitter, FName(*SafeEmitterName), VersionGuid);
#endif
            
            // Restore original value on template (though it's likely a loaded asset and this may not matter)
            TemplateEmitter->bIsInheritable = bOriginalInheritable;
            
            MarkSystemDirtyAndFullRecompile(System, TEXT("AddEmitterFromTemplate"));
            return System->GetEmitterHandles().Num() > 0;
        }

        UE_LOG(LogVFXAgent, Warning, TEXT("Template system/emitter not found: %s. Creating basic emitter instead."), *ObjectPath);
        return AddBasicEmitterToSystem(System, SafeEmitterName);
    }

    // Handle System templates - iterate through their emitters
    UE_LOG(LogVFXAgent, Log, TEXT("Loaded system template: %s with %d emitters"), *ObjectPath, TemplateSystem->GetEmitterHandles().Num());
    
    for (const FNiagaraEmitterHandle& TemplateHandle : TemplateSystem->GetEmitterHandles())
    {
        FVersionedNiagaraEmitter Source = TemplateHandle.GetInstance(); 
        if (Source.Emitter)
        {
            // CRITICAL: Set bIsInheritable to false to create standalone emitter
            const bool bOriginalInheritable = Source.Emitter->bIsInheritable;
            Source.Emitter->bIsInheritable = false;
            
            #if WITH_EDITOR
            const FGuid HandleId = FNiagaraEditorUtilities::AddEmitterToSystem(*System, *Source.Emitter, Source.Version, true);
            for (FNiagaraEmitterHandle& SystemHandle : System->GetEmitterHandles())
            {
                if (SystemHandle.GetId() == HandleId)
                {
                    SystemHandle.SetName(FName(*SafeEmitterName), *System);
                    SystemHandle.SetIsEnabled(true, *System, true);
                    break;
                }
            }
#else
            System->AddEmitterHandle(*Source.Emitter, FName(*SafeEmitterName), Source.Version);
#endif
            
            // Restore original value
            Source.Emitter->bIsInheritable = bOriginalInheritable;
            break; // Only add the first emitter
        }
    }

    MarkSystemDirtyAndFullRecompile(System, TEXT("AddEmitterFromTemplate"));

    return System->GetEmitterHandles().Num() > 0;
}

void FNiagaraSpecExecutor::ConfigureEmitter(UNiagaraSystem* System, const FString& EmitterName, const FVFXEmitterSpec& Spec)
{
    if (!System) return;

    const FString SafeEmitterName = SanitizeNiagaraIdentifier(EmitterName, TEXT("Emitter"));

    // Find the handle
    FNiagaraEmitterHandle* Handle = nullptr;
    for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
    {
        if (H.GetName() == FName(*EmitterName)
            || H.GetName() == FName(*SafeEmitterName)
            || H.GetName() == FName(*(EmitterName + "0"))
            || H.GetName() == FName(*(SafeEmitterName + "0"))) // Name might be suffixed
        {
            Handle = &H;
            break;
        }
    }
    
    // Fallback: use the last one added if name mismatch (Niagara auto-renames)
    if (!Handle && System->GetEmitterHandles().Num() > 0)
    {
        Handle = &System->GetEmitterHandles().Last();
    }

    if (!Handle) return;

    FVersionedNiagaraEmitter VersionedEmitter = Handle->GetInstance();
    UNiagaraEmitter* EmitterInstance = VersionedEmitter.Emitter;
    if (!EmitterInstance) return;

    const bool bHasSpawnModules = HasAnyModules(EmitterInstance, TEXT("ParticleSpawnScriptProps"));
    const bool bHasUpdateModules = HasAnyModules(EmitterInstance, TEXT("ParticleUpdateScriptProps"));
    if (!bHasSpawnModules && !bHasUpdateModules)
    {
        AddMinimalModuleChain(System, EmitterName, Spec.RendererType);
    }

    // 1. Configure Renderer
    bool bHasCorrectRenderer = false;

    // Pre-clean: remove invalid renderers and ensure material binding if possible
    {
        UMaterialInterface* DefaultMat = GetDefaultParticleMaterial();
        FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Niagara, TEXT("Fixing extra empty renderer..."));
        FRendererValidationReport PreReport = FVFXRendererValidationFixer::ValidateAndFixRenderers(EmitterInstance, DefaultMat);
        if (PreReport.InvalidRenderersRemoved > 0 || PreReport.RenderersFixed > 0)
        {
            UE_LOG(LogVFXAgent, Log, TEXT("RendererValidationFixer (pre): %s"), *PreReport.Summary);
            FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Validate, PreReport.Summary);
        }
    }

    // Remove any renderers that don't match the requested type to avoid duplicates
    RemoveMismatchedRenderers(EmitterInstance, Spec.RendererType);
    // Remove duplicate renderers of the requested type (keep one)
    PruneDuplicateRenderers(EmitterInstance, Spec.RendererType);
    
    TArray<UNiagaraRendererProperties*> RendererProps = GetEmitterRenderers(EmitterInstance);
    for (UNiagaraRendererProperties* Prop : RendererProps)
    {
        if (!Prop) continue;
        if (Spec.RendererType == EVFXRendererType::Sprite && Prop->IsA<UNiagaraSpriteRendererProperties>()) bHasCorrectRenderer = true;
        if (Spec.RendererType == EVFXRendererType::Ribbon && Prop->IsA<UNiagaraRibbonRendererProperties>()) bHasCorrectRenderer = true;
        if (Spec.RendererType == EVFXRendererType::Light && Prop->IsA<UNiagaraLightRendererProperties>()) bHasCorrectRenderer = true;
    }

    if (!bHasCorrectRenderer)
    {
        UNiagaraRendererProperties* NewProps = nullptr;
        if (Spec.RendererType == EVFXRendererType::Sprite) NewProps = NewObject<UNiagaraSpriteRendererProperties>(EmitterInstance);
        else if (Spec.RendererType == EVFXRendererType::Ribbon) NewProps = NewObject<UNiagaraRibbonRendererProperties>(EmitterInstance);
        else if (Spec.RendererType == EVFXRendererType::Mesh) NewProps = NewObject<UNiagaraMeshRendererProperties>(EmitterInstance);
        else if (Spec.RendererType == EVFXRendererType::Light) NewProps = NewObject<UNiagaraLightRendererProperties>(EmitterInstance);
        
        if (NewProps)
        {
            EmitterInstance->AddRenderer(NewProps, VersionedEmitter.Version);
        }
    }

    // Ensure only a single renderer of the desired type remains after adding
    PruneDuplicateRenderers(EmitterInstance, Spec.RendererType);

    // Ensure the renderer has a valid material to avoid "None" in the editor
    if (Spec.RendererType == EVFXRendererType::Sprite || Spec.RendererType == EVFXRendererType::Ribbon)
    {
        EnsureSingleRendererHasMaterial(EmitterInstance, Spec.RendererType);
    }

    // Post-check: ensure exactly one renderer of correct type with non-null material
    {
        int32 MatchingCount = 0;
        bool bHasMaterial = false;
        for (UNiagaraRendererProperties* Prop : GetEmitterRenderers(EmitterInstance))
        {
            if (!Prop) continue;
            if (IsRendererOfType(Prop, Spec.RendererType))
            {
                ++MatchingCount;
                if (FVFXRendererValidationFixer::GetRendererMaterial(Prop) != nullptr)
                {
                    bHasMaterial = true;
                }
            }
        }
        if (MatchingCount != 1 || !bHasMaterial)
        {
            UE_LOG(LogVFXAgent, Warning, TEXT("Renderer self-check failed for '%s': count=%d, hasMaterial=%s"),
                *EmitterName, MatchingCount, bHasMaterial ? TEXT("YES") : TEXT("NO"));
            FPipelineLog::Get().Push(EPipelineLogLevel::Warning, EPipelineStage::Validate,
                FString::Printf(TEXT("Renderer self-check failed for '%s': count=%d, hasMaterial=%s"),
                    *EmitterName, MatchingCount, bHasMaterial ? TEXT("YES") : TEXT("NO")));
        }
        else
        {
            FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::Validate,
                FString::Printf(TEXT("Renderer self-check OK for '%s'"), *EmitterName));
        }
    }

    // Apply renderer sort order where supported
    if (Spec.SortOrder != 0)
    {
        RendererProps = GetEmitterRenderers(EmitterInstance);
        for (UNiagaraRendererProperties* Prop : RendererProps)
        {
            if (!Prop) continue;
            if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Prop))
            {
                Sprite->SortOrderHint = Spec.SortOrder;
            }
            else if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Prop))
            {
                Ribbon->SortOrderHint = Spec.SortOrder;
            }
        }
    }

    // Apply facing/alignment options for sprite renderer
    if (Spec.RendererType == EVFXRendererType::Sprite)
    {
        RendererProps = GetEmitterRenderers(EmitterInstance);
        for (UNiagaraRendererProperties* Prop : RendererProps)
        {
            if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Prop))
            {
                if (!Spec.FacingMode.IsEmpty())
                {
                    const FString Facing = Spec.FacingMode.ToLower();
                    if (Facing.Contains(TEXT("custom"))) Sprite->FacingMode = ENiagaraSpriteFacingMode::CustomFacingVector;
                    else Sprite->FacingMode = ENiagaraSpriteFacingMode::FaceCamera;
                }

                if (!Spec.Alignment.IsEmpty())
                {
                    const FString Align = Spec.Alignment.ToLower();
                    if (Align.Contains(TEXT("velocity"))) Sprite->Alignment = ENiagaraSpriteAlignment::VelocityAligned;
                    else if (Align.Contains(TEXT("custom"))) Sprite->Alignment = ENiagaraSpriteAlignment::CustomAlignment;
                    else Sprite->Alignment = ENiagaraSpriteAlignment::Unaligned;
                }
            }
        }
    }

    // Apply local space
    SetEmitterLocalSpace(EmitterInstance, Spec.bLocalSpace);

    // 2. Configure Parameters
    FString Namespace = Handle->GetName().ToString();
    
    // === SPAWN PARAMETERS ===
    if (Spec.Spawn.Rate > 0)
    {
        SetVariableFloat(System, Namespace, TEXT("SpawnRate.SpawnRate"), Spec.Spawn.Rate);
        SetVariableFloat(System, Namespace, TEXT("Spawn Rate"), Spec.Spawn.Rate);
    }
    if (Spec.Spawn.Burst > 0)
    {
        SetVariableFloat(System, Namespace, TEXT("SpawnBurst_Instant.SpawnBurst"), (float)Spec.Spawn.Burst);
        SetVariableFloat(System, Namespace, TEXT("Spawn Burst Instantaneous.Spawn Count"), (float)Spec.Spawn.Burst);
    }
    if (Spec.Spawn.BurstTime > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("SpawnBurst_Instant.SpawnTime"), Spec.Spawn.BurstTime);
        SetVariableFloat(System, Namespace, TEXT("Spawn Burst Instantaneous.Spawn Time"), Spec.Spawn.BurstTime);
    }

    // === LIFETIME & VARIATION ===
    SetVariableFloat(System, Namespace, TEXT("InitializeParticle.Lifetime"), Spec.Lifetime);
    SetVariableFloat(System, Namespace, TEXT("Lifetime"), Spec.Lifetime);
    if (Spec.LifetimeVariation > 0.001f)
    {
        const float MinLife = FMath::Max(0.0f, Spec.Lifetime * (1.0f - Spec.LifetimeVariation));
        const float MaxLife = Spec.Lifetime * (1.0f + Spec.LifetimeVariation);
        SetVariableFloat(System, Namespace, TEXT("InitializeParticle.LifetimeMin"), MinLife);
        SetVariableFloat(System, Namespace, TEXT("InitializeParticle.LifetimeMax"), MaxLife);
        SetVariableFloat(System, Namespace, TEXT("Lifetime Min"), MinLife);
        SetVariableFloat(System, Namespace, TEXT("Lifetime Max"), MaxLife);
    }
    
    // === SIZE PARAMETERS ===
    SetVariableFloat(System, Namespace, TEXT("InitializeParticle.SpriteSize"), Spec.Size);
    SetVariableFloat(System, Namespace, TEXT("Sprite Size"), Spec.Size);
    SetVariableFloat(System, Namespace, TEXT("Uniform Sprite Size"), Spec.Size);
    if (Spec.SizeVariation > 0.001f)
    {
        const float MinSize = FMath::Max(0.0f, Spec.Size * (1.0f - Spec.SizeVariation));
        const float MaxSize = Spec.Size * (1.0f + Spec.SizeVariation);
        SetVariableFloat(System, Namespace, TEXT("InitializeParticle.SpriteSizeMin"), MinSize);
        SetVariableFloat(System, Namespace, TEXT("InitializeParticle.SpriteSizeMax"), MaxSize);
        SetVariableFloat(System, Namespace, TEXT("Sprite Size Min"), MinSize);
        SetVariableFloat(System, Namespace, TEXT("Sprite Size Max"), MaxSize);
    }
    if (Spec.bUseSizeOverLife)
    {
        SetVariableFloat(System, Namespace, TEXT("Sprite Size End"), Spec.SizeEnd);
        SetVariableFloat(System, Namespace, TEXT("Scale Sprite Size.End Size"), Spec.SizeEnd);
        SetVariableFloat(System, Namespace, TEXT("Scale Sprite Size.End"), Spec.SizeEnd);
    }
    
    // === COLOR PARAMETERS ===
    SetVariableLinearColor(System, Namespace, TEXT("InitializeParticle.Color"), Spec.Color);
    SetVariableLinearColor(System, Namespace, TEXT("Color"), Spec.Color);
    SetVariableLinearColor(System, Namespace, TEXT("Particle Color"), Spec.Color);
    if (Spec.bUseColorGradient)
    {
        SetVariableLinearColor(System, Namespace, TEXT("Color End"), Spec.ColorEnd);
        SetVariableLinearColor(System, Namespace, TEXT("ColorEnd"), Spec.ColorEnd);
        SetVariableLinearColor(System, Namespace, TEXT("Scale Color.End Color"), Spec.ColorEnd);
    }

    // === ALPHA OVER LIFE ===
    SetVariableFloat(System, Namespace, TEXT("Alpha"), Spec.Alpha);
    if (Spec.bUseAlphaOverLife)
    {
        SetVariableFloat(System, Namespace, TEXT("Alpha End"), Spec.AlphaEnd);
        SetVariableFloat(System, Namespace, TEXT("Scale Color.End Alpha"), Spec.AlphaEnd);
        SetVariableFloat(System, Namespace, TEXT("Scale Color.EndAlpha"), Spec.AlphaEnd);
    }
    
    // === VELOCITY PARAMETERS ===
    SetVariableVec3(System, Namespace, TEXT("AddVelocity.Velocity"), Spec.Velocity);
    SetVariableVec3(System, Namespace, TEXT("AddVelocityInCone.Velocity"), Spec.Velocity);
    SetVariableVec3(System, Namespace, TEXT("Velocity"), Spec.Velocity);
    
    // Set velocity magnitude for cone/directional templates
    float VelocityMagnitude = Spec.Velocity.Length();
    if (VelocityMagnitude > 0.01f)
    {
        SetVariableFloat(System, Namespace, TEXT("Velocity Strength"), VelocityMagnitude);
        SetVariableFloat(System, Namespace, TEXT("VelocityMagnitude"), VelocityMagnitude);
    }

    if (Spec.VelocityVariation > 0.001f)
    {
        SetVariableFloat(System, Namespace, TEXT("Velocity Variation"), Spec.VelocityVariation);
        SetVariableFloat(System, Namespace, TEXT("Velocity Random"), Spec.VelocityVariation);
        SetVariableFloat(System, Namespace, TEXT("AddVelocity.Randomness"), Spec.VelocityVariation);
    }
    
    // === DRAG ===
    if (FMath::Abs(Spec.Drag) > 0.001f)
    {
        SetVariableFloat(System, Namespace, TEXT("Drag.Drag"), Spec.Drag);
        SetVariableFloat(System, Namespace, TEXT("Drag"), Spec.Drag);
    }

    // === NOISE / CURL NOISE / VORTEX / LIMIT VELOCITY / LIFT ===
    if (Spec.CurlNoiseStrength > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("Curl Noise Force.Strength"), Spec.CurlNoiseStrength);
        SetVariableFloat(System, Namespace, TEXT("CurlNoiseForce.Strength"), Spec.CurlNoiseStrength);
    }
    if (Spec.CurlNoiseFrequency > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("Curl Noise Force.Frequency"), Spec.CurlNoiseFrequency);
        SetVariableFloat(System, Namespace, TEXT("CurlNoiseForce.Frequency"), Spec.CurlNoiseFrequency);
    }
    if (Spec.NoiseStrength > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("Noise Force.Strength"), Spec.NoiseStrength);
        SetVariableFloat(System, Namespace, TEXT("NoiseForce.Strength"), Spec.NoiseStrength);
    }
    if (Spec.NoiseFrequency > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("Noise Force.Frequency"), Spec.NoiseFrequency);
        SetVariableFloat(System, Namespace, TEXT("NoiseForce.Frequency"), Spec.NoiseFrequency);
    }
    if (Spec.LimitVelocity > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("Limit Velocity.Max Speed"), Spec.LimitVelocity);
        SetVariableFloat(System, Namespace, TEXT("LimitVelocity.MaxVelocity"), Spec.LimitVelocity);
    }
    if (Spec.VortexStrength > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("Vortex Force.Strength"), Spec.VortexStrength);
        SetVariableVec3(System, Namespace, TEXT("Vortex Force.Axis"), Spec.VortexAxis);
    }
    if (Spec.LiftStrength > 0.0f)
    {
        SetVariableFloat(System, Namespace, TEXT("Lift Force.Strength"), Spec.LiftStrength);
        SetVariableFloat(System, Namespace, TEXT("Lift.Strength"), Spec.LiftStrength);
    }
    
    // === ACCELERATION / GRAVITY ===
    if (Spec.Acceleration.SquaredLength() > 0.01f || Spec.bUseGravity)
    {
        FVector Accel = Spec.bUseGravity ? FVector(0, 0, -980) : Spec.Acceleration;
        SetVariableVec3(System, Namespace, TEXT("Gravity.Acceleration"), Accel);
        SetVariableVec3(System, Namespace, TEXT("Gravity Force.Acceleration"), Accel);
        SetVariableVec3(System, Namespace, TEXT("Acceleration"), Accel);
    }
    
    // === ROTATION ===
    if (FMath::Abs(Spec.RotationRate) > 0.01f)
    {
        SetVariableFloat(System, Namespace, TEXT("RotationRate"), Spec.RotationRate);
        SetVariableFloat(System, Namespace, TEXT("Sprite Rotation Rate"), Spec.RotationRate);
        SetVariableFloat(System, Namespace, TEXT("Mesh Rotation Rate"), Spec.RotationRate);
    }

    if (FMath::Abs(Spec.RotationRateVariation) > 0.001f)
    {
        SetVariableFloat(System, Namespace, TEXT("Rotation Rate Variation"), Spec.RotationRateVariation);
        SetVariableFloat(System, Namespace, TEXT("RotationRate Random"), Spec.RotationRateVariation);
    }
    
    if (FMath::Abs(Spec.InitialRotation) > 0.01f)
    {
        SetVariableFloat(System, Namespace, TEXT("Initial Rotation"), Spec.InitialRotation);
        SetVariableFloat(System, Namespace, TEXT("Sprite Rotation"), Spec.InitialRotation);
    }
    
    // === MASS ===
    if (FMath::Abs(Spec.Mass - 1.0f) > 0.01f)
    {
        SetVariableFloat(System, Namespace, TEXT("Mass"), Spec.Mass);
        SetVariableFloat(System, Namespace, TEXT("Particle Mass"), Spec.Mass);
    }
    
    UE_LOG(LogVFXAgent, Log, TEXT("Configured emitter '%s' with %d parameters"), *EmitterName, 20);

    // 3. Also apply to Rapid Iteration parameters for better compatibility with templates
    TArray<UNiagaraScript*> Scripts;
    GatherEmitterScripts(EmitterInstance, Scripts);
    for (UNiagaraScript* Script : Scripts)
    {
        if (!Script) continue;
        FNiagaraParameterStore& Store = Script->RapidIterationParameters;

        // Spawn
        if (Spec.Spawn.Rate > 0.0f)
        {
            TrySetFloatInStore(Store, TEXT("Spawn Rate"), Spec.Spawn.Rate);
            TrySetFloatInStore(Store, TEXT("SpawnRate"), Spec.Spawn.Rate);
        }
        if (Spec.Spawn.Burst > 0)
        {
            TrySetIntInStore(Store, TEXT("Burst"), Spec.Spawn.Burst);
            TrySetFloatInStore(Store, TEXT("Burst"), (float)Spec.Spawn.Burst);
        }

        // Lifetime
        TrySetFloatInStore(Store, TEXT("Lifetime"), Spec.Lifetime);

        // Size
        TrySetFloatInStore(Store, TEXT("Sprite Size"), Spec.Size);
        TrySetFloatInStore(Store, TEXT("Size"), Spec.Size);
        if (Spec.bUseSizeOverLife)
        {
            TrySetFloatInStore(Store, TEXT("End Size"), Spec.SizeEnd);
        }

        // Color
        TrySetColorInStore(Store, TEXT("Color"), Spec.Color);
        if (Spec.bUseColorGradient)
        {
            TrySetColorInStore(Store, TEXT("End Color"), Spec.ColorEnd);
            TrySetColorInStore(Store, TEXT("Color End"), Spec.ColorEnd);
        }

        // Alpha
        TrySetFloatInStore(Store, TEXT("Alpha"), Spec.Alpha);
        if (Spec.bUseAlphaOverLife)
        {
            TrySetFloatInStore(Store, TEXT("End Alpha"), Spec.AlphaEnd);
            TrySetFloatInStore(Store, TEXT("Alpha End"), Spec.AlphaEnd);
        }

        // Velocity
        TrySetVec3InStore(Store, TEXT("Velocity"), Spec.Velocity);

        // Gravity / Acceleration
        if (Spec.Acceleration.SquaredLength() > 0.01f || Spec.bUseGravity)
        {
            const FVector Accel = Spec.bUseGravity ? FVector(0, 0, -980) : Spec.Acceleration;
            TrySetVec3InStore(Store, TEXT("Acceleration"), Accel);
            TrySetVec3InStore(Store, TEXT("Gravity"), Accel);
        }

        // Drag
        if (FMath::Abs(Spec.Drag) > 0.001f)
        {
            TrySetFloatInStore(Store, TEXT("Drag"), Spec.Drag);
        }

        // Noise / Curl / Vortex / Limit Velocity / Lift
        if (Spec.CurlNoiseStrength > 0.0f) TrySetFloatInStore(Store, TEXT("Curl Noise Strength"), Spec.CurlNoiseStrength);
        if (Spec.CurlNoiseFrequency > 0.0f) TrySetFloatInStore(Store, TEXT("Curl Noise Frequency"), Spec.CurlNoiseFrequency);
        if (Spec.NoiseStrength > 0.0f) TrySetFloatInStore(Store, TEXT("Noise Strength"), Spec.NoiseStrength);
        if (Spec.NoiseFrequency > 0.0f) TrySetFloatInStore(Store, TEXT("Noise Frequency"), Spec.NoiseFrequency);
        if (Spec.LimitVelocity > 0.0f) TrySetFloatInStore(Store, TEXT("Limit Velocity"), Spec.LimitVelocity);
        if (Spec.VortexStrength > 0.0f) TrySetFloatInStore(Store, TEXT("Vortex Strength"), Spec.VortexStrength);
        if (Spec.LiftStrength > 0.0f) TrySetFloatInStore(Store, TEXT("Lift Strength"), Spec.LiftStrength);

        // Rotation
        if (FMath::Abs(Spec.RotationRate) > 0.01f)
        {
            TrySetFloatInStore(Store, TEXT("Rotation Rate"), Spec.RotationRate);
            TrySetFloatInStore(Store, TEXT("RotationRate"), Spec.RotationRate);
        }
        if (FMath::Abs(Spec.InitialRotation) > 0.01f)
        {
            TrySetFloatInStore(Store, TEXT("Initial Rotation"), Spec.InitialRotation);
            TrySetFloatInStore(Store, TEXT("Rotation"), Spec.InitialRotation);
        }

        Script->MarkPackageDirty();
    }

    // Reorder update stacks using phase-based topo sort
    SortEmitterModuleStack(EmitterInstance, TEXT("UpdateScriptProps"));
    SortEmitterModuleStack(EmitterInstance, TEXT("ParticleUpdateScriptProps"));

    // Ensure spawn_rate and other rapid-iteration params become visible in UE5.5 Niagara UI immediately.
    MarkSystemDirtyAndFullRecompile(System, TEXT("ConfigureEmitter"));
}

bool FNiagaraSpecExecutor::ConfigureCollisionEventHandler(UNiagaraSystem* System, const FString& SourceEmitterName, const FString& TargetEmitterName, const FVFXEventRecipe& Event)
{
    if (!System) return false;

    FNiagaraEmitterHandle* SourceHandle = nullptr;
    FNiagaraEmitterHandle* TargetHandle = nullptr;
    for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
    {
        if (H.GetName() == FName(*SourceEmitterName)) SourceHandle = &H;
        if (H.GetName() == FName(*TargetEmitterName)) TargetHandle = &H;
    }

    if (!SourceHandle || !TargetHandle)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Collision event setup failed: missing source or target emitter."));
        return false;
    }

    UNiagaraEmitter* SourceEmitter = SourceHandle->GetInstance().Emitter;
    UNiagaraEmitter* TargetEmitter = TargetHandle->GetInstance().Emitter;
    if (!SourceEmitter || !TargetEmitter) return false;

    // Load module scripts from settings
    const FString CollisionModulePath = GetVFXAgentSetting(TEXT("CollisionModuleScriptPath"), TEXT("/Niagara/Modules/Collision/Collision.Collision"));
    const FString GenerateCollisionEventPath = GetVFXAgentSetting(TEXT("GenerateCollisionEventScriptPath"), TEXT("/Niagara/Modules/Collision/Generate Collision Event.Generate Collision Event"));
    const FString ReceiveCollisionEventPath = GetVFXAgentSetting(TEXT("ReceiveCollisionEventScriptPath"), TEXT("/Niagara/Modules/Events/Receive Collision Event.Receive Collision Event"));
    const FString EventSpawnPath = GetVFXAgentSetting(TEXT("EventSpawnScriptPath"), TEXT("/Niagara/Modules/Spawn/Spawn Burst Instantaneous.Spawn Burst Instantaneous"));

    UNiagaraScript* CollisionModule = LoadNiagaraScriptFromPath(CollisionModulePath);
    UNiagaraScript* GenerateCollisionEvent = LoadNiagaraScriptFromPath(GenerateCollisionEventPath);
    UNiagaraScript* ReceiveCollisionEvent = LoadNiagaraScriptFromPath(ReceiveCollisionEventPath);
    UNiagaraScript* EventSpawn = LoadNiagaraScriptFromPath(EventSpawnPath);

    FModuleInsertOptions CollisionOptions;
    CollisionOptions.Mode = GetVFXAgentSetting(TEXT("CollisionModuleInsertMode"), TEXT("Phase"));
    CollisionOptions.Phase = GetVFXAgentSetting(TEXT("CollisionModuleInsertPhase"), TEXT("CollisionDetect"));
    CollisionOptions.Anchor = GetVFXAgentSetting(TEXT("CollisionModuleInsertAnchor"), TEXT("@CollisionBegin"));
    CollisionOptions.Relative = GetVFXAgentSetting(TEXT("CollisionModuleInsertRelative"), TEXT("After"));
    CollisionOptions.Priority = FCString::Atoi(*GetVFXAgentSetting(TEXT("CollisionModuleInsertPriority"), TEXT("0")));

    FModuleInsertOptions GenerateOptions;
    GenerateOptions.Mode = GetVFXAgentSetting(TEXT("GenerateCollisionEventInsertMode"), TEXT("Anchor"));
    GenerateOptions.Phase = GetVFXAgentSetting(TEXT("GenerateCollisionEventInsertPhase"), TEXT("EventWrite"));
    GenerateOptions.Anchor = GetVFXAgentSetting(TEXT("GenerateCollisionEventInsertAnchor"), TEXT("@EventWriteEnd"));
    GenerateOptions.Relative = GetVFXAgentSetting(TEXT("GenerateCollisionEventInsertRelative"), TEXT("Before"));
    GenerateOptions.Priority = FCString::Atoi(*GetVFXAgentSetting(TEXT("GenerateCollisionEventInsertPriority"), TEXT("0")));

    FModuleInsertOptions ReceiveOptions;
    ReceiveOptions.Mode = GetVFXAgentSetting(TEXT("ReceiveCollisionEventInsertMode"), TEXT("Anchor"));
    ReceiveOptions.Phase = GetVFXAgentSetting(TEXT("ReceiveCollisionEventInsertPhase"), TEXT("EventWrite"));
    ReceiveOptions.Anchor = GetVFXAgentSetting(TEXT("ReceiveCollisionEventInsertAnchor"), TEXT("@EventWriteEnd"));
    ReceiveOptions.Relative = GetVFXAgentSetting(TEXT("ReceiveCollisionEventInsertRelative"), TEXT("Before"));
    ReceiveOptions.Priority = FCString::Atoi(*GetVFXAgentSetting(TEXT("ReceiveCollisionEventInsertPriority"), TEXT("0")));

    FModuleInsertOptions EventSpawnOptions;
    EventSpawnOptions.Mode = GetVFXAgentSetting(TEXT("EventSpawnInsertMode"), TEXT("Phase"));
    EventSpawnOptions.Phase = GetVFXAgentSetting(TEXT("EventSpawnInsertPhase"), TEXT("EventWrite"));
    EventSpawnOptions.Anchor = GetVFXAgentSetting(TEXT("EventSpawnInsertAnchor"), TEXT("@EventWriteEnd"));
    EventSpawnOptions.Relative = GetVFXAgentSetting(TEXT("EventSpawnInsertRelative"), TEXT("After"));
    EventSpawnOptions.Priority = FCString::Atoi(*GetVFXAgentSetting(TEXT("EventSpawnInsertPriority"), TEXT("0")));

    if (!GenerateCollisionEvent || !ReceiveCollisionEvent)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Missing collision event scripts. Check Niagara event module paths in settings."));
        return false;
    }

    // Ensure collision + generate event modules are present on source emitter
    if (CollisionModule)
    {
        InsertScriptWithOrdering(SourceEmitter, TEXT("UpdateScriptProps"), CollisionModule, CollisionOptions);
        InsertScriptWithOrdering(SourceEmitter, TEXT("ParticleUpdateScriptProps"), CollisionModule, CollisionOptions);
    }
    InsertScriptWithOrdering(SourceEmitter, TEXT("UpdateScriptProps"), GenerateCollisionEvent, GenerateOptions);
    InsertScriptWithOrdering(SourceEmitter, TEXT("ParticleUpdateScriptProps"), GenerateCollisionEvent, GenerateOptions);

    // Add event handler scripts to target emitter
    InsertScriptWithOrdering(TargetEmitter, TEXT("EventHandlerScriptProps"), ReceiveCollisionEvent, ReceiveOptions);
    if (EventSpawn)
    {
        InsertScriptWithOrdering(TargetEmitter, TEXT("EventHandlerScriptProps"), EventSpawn, EventSpawnOptions);
    }

    // Ensure persistent IDs for event routing
    SetEmitterRequiresPersistentIDs(SourceEmitter, true);

    // Patch handler source linkage and spawn counts
    void* HandlerContainer = nullptr;
    FArrayProperty* HandlerArrayProp = nullptr;
    if (ResolveEmitterArrayProperty(TargetEmitter, TEXT("EventHandlerScriptProps"), HandlerContainer, HandlerArrayProp)
        && HandlerContainer
        && HandlerArrayProp)
    {
        FScriptArrayHelper HandlerHelper(HandlerArrayProp, HandlerArrayProp->ContainerPtrToValuePtr<void>(HandlerContainer));
        if (FStructProperty* StructProp = CastField<FStructProperty>(HandlerArrayProp->Inner))
        {
            UStruct* StructType = StructProp->Struct;
            for (int32 i = 0; i < HandlerHelper.Num(); ++i)
            {
                void* ElemPtr = HandlerHelper.GetRawPtr(i);
                SetStructGuidField(ElemPtr, StructType, TEXT("SourceEmitterID"), SourceHandle->GetId());
                SetStructNameField(ElemPtr, StructType, TEXT("SourceEmitterName"), SourceHandle->GetName());
                SetStructNameField(ElemPtr, StructType, TEXT("EventName"), FName(TEXT("Collision")));
                SetStructFloatField(ElemPtr, StructType, TEXT("MaxEventsPerFrame"), 128.0f);

                if (Event.BurstOverride > 0)
                {
                    SetStructFloatField(ElemPtr, StructType, TEXT("SpawnNumber"), (float)Event.BurstOverride);
                    SetStructFloatField(ElemPtr, StructType, TEXT("SpawnNumberOverride"), (float)Event.BurstOverride);
                }
                else if (Event.BurstMultiplier != 1.0f)
                {
                    SetStructFloatField(ElemPtr, StructType, TEXT("SpawnNumber"), Event.BurstMultiplier);
                }
            }
        }
    }

    // Configure event generator props (if exposed)
    void* GeneratorContainer = nullptr;
    FArrayProperty* GeneratorArrayProp = nullptr;
    if (ResolveEmitterArrayProperty(SourceEmitter, TEXT("EventGeneratorProps"), GeneratorContainer, GeneratorArrayProp)
        && GeneratorContainer
        && GeneratorArrayProp)
    {
        FScriptArrayHelper GenHelper(GeneratorArrayProp, GeneratorArrayProp->ContainerPtrToValuePtr<void>(GeneratorContainer));
        if (FStructProperty* StructProp = CastField<FStructProperty>(GeneratorArrayProp->Inner))
        {
            UStruct* StructType = StructProp->Struct;
            if (GenHelper.Num() == 0)
            {
                GenHelper.AddValue();
            }
            for (int32 i = 0; i < GenHelper.Num(); ++i)
            {
                void* ElemPtr = GenHelper.GetRawPtr(i);
                SetStructNameField(ElemPtr, StructType, TEXT("EventName"), FName(TEXT("Collision")));
                SetStructFloatField(ElemPtr, StructType, TEXT("MaxEventsPerFrame"), 128.0f);
                SetStructObjectField(ElemPtr, StructType, TEXT("GeneratorScript"), GenerateCollisionEvent);
                SetStructObjectField(ElemPtr, StructType, TEXT("Script"), GenerateCollisionEvent);
            }
        }
    }

    // Enforce ordering on update stacks after event wiring
    SortEmitterModuleStack(SourceEmitter, TEXT("UpdateScriptProps"));
    SortEmitterModuleStack(SourceEmitter, TEXT("ParticleUpdateScriptProps"));

    SourceEmitter->Modify();
    TargetEmitter->Modify();
    SourceEmitter->PostEditChange();
    TargetEmitter->PostEditChange();

    UE_LOG(LogVFXAgent, Log, TEXT("Configured collision event handler (direct API): %s -> %s"), *SourceEmitterName, *TargetEmitterName);
    return true;
}

void FNiagaraSpecExecutor::SetVariableFloat(UNiagaraSystem* System, const FString& EmitterName, const FString& VarName, float Value)
{
    // Format: EmitterName.VarName  (e.g. MyEmitter.SpawnRate.SpawnRate)
    FString FullName = FString::Printf(TEXT("%s.%s"), *EmitterName, *VarName);
    
    // Also try the ParameterStore directly
    FNiagaraVariable Var(FNiagaraTypeDefinition::GetFloatDef(), FName(*FullName));
    Var.SetValue(Value);
    System->GetExposedParameters().SetParameterValue(Value, Var);
}

void FNiagaraSpecExecutor::SetVariableVec3(UNiagaraSystem* System, const FString& EmitterName, const FString& VarName, FVector Value)
{
    FString FullName = FString::Printf(TEXT("%s.%s"), *EmitterName, *VarName);
    FNiagaraVariable Var(FNiagaraTypeDefinition::GetVec3Def(), FName(*FullName));
    const FVector3f Value3f((float)Value.X, (float)Value.Y, (float)Value.Z);
    Var.SetValue(Value3f);
    System->GetExposedParameters().SetParameterValue(Value3f, Var);
}

void FNiagaraSpecExecutor::SetVariableLinearColor(UNiagaraSystem* System, const FString& EmitterName, const FString& VarName, FLinearColor Value)
{
    FString FullName = FString::Printf(TEXT("%s.%s"), *EmitterName, *VarName);
    FNiagaraVariable Var(FNiagaraTypeDefinition::GetColorDef(), FName(*FullName));
    Var.SetValue(Value);
    System->GetExposedParameters().SetParameterValue(Value, Var);
}

bool FNiagaraSpecExecutor::SaveCompileAndSelfCheck(UNiagaraSystem* System, FVFXRepairReport& OutReport)
{
    if (!System) return false;

#if WITH_EDITOR
    // CRITICAL FIX: Complete initialization sequence for Niagara preview display
    
    // Step 1: Force enable all emitters and configure their visibility
    for (int32 i = 0; i < System->GetNumEmitters(); ++i)
    {
        FNiagaraEmitterHandle& EmitterHandle = System->GetEmitterHandle(i);
        EmitterHandle.SetIsEnabled(true, *System, true);
    }

    // Step 2: Mark the package as dirty
    System->MarkPackageDirty();
    if (UPackage* Pkg = System->GetOutermost())
    {
        Pkg->MarkPackageDirty();
    }

    // Step 3: Request a FORCED full recompile (bForce = true is critical)
    System->RequestCompile(true);
    
    // Step 4: Wait for the compilation to complete - blocking call
    System->WaitForCompilationComplete(true, true);
    
    // Step 5: Invalidate cached data to force refresh
    System->InvalidateCachedData();

    // Step 6: Request+wait once more so invalidated data is guaranteed recompiled
    System->RequestCompile(true);
    System->WaitForCompilationComplete(true, true);
    
    // Step 7: Save the package
    FString PackageName = System->GetOutermost()->GetName();
    FSavePackageArgs SaveArgs;
    SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
    bool bSaved = UPackage::SavePackage(
        System->GetOutermost(), 
        System, 
        *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()), 
        SaveArgs
    );
    
    if (!bSaved)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Failed to save package for system '%s'"), *System->GetName());
    }
    
    // Step 7: Notify the asset system and editors
    FAssetRegistryModule::AssetCreated(System);
    
    // Step 8: Trigger PostEditChange to refresh any open editors
    System->PostEditChange();

    // Step 8.5: Ensure System Overview graph matches current emitters
    if (UNiagaraSystemEditorData* SystemEditorData = Cast<UNiagaraSystemEditorData>(System->GetEditorData()))
    {
        SystemEditorData->SynchronizeOverviewGraphWithSystem(*System);
    }
    
    // Step 9: If the asset is currently open in an editor, force it to reload
    // This is the key to making the preview work immediately
    if (GEditor)
    {
        UAssetEditorSubsystem* AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
        if (AssetEditorSubsystem)
        {
            // Close and reopen the asset to force a complete refresh
            if (AssetEditorSubsystem->FindEditorForAsset(System, false))
            {
                UE_LOG(LogVFXAgent, Log, TEXT("Asset is open in editor, triggering refresh..."));
                // The PostEditChange above should trigger the refresh
                // If still having issues, we could close and reopen:
                // AssetEditorSubsystem->CloseAllEditorsForAsset(System);
                // AssetEditorSubsystem->OpenEditorForAsset(System);
            }
        }
    }
    
    UE_LOG(LogVFXAgent, Log, TEXT("System '%s' saved and compiled, ready for preview"), *System->GetName());
#endif
    
    // Self Check
    OutReport.SystemPath = System->GetOutermost()->GetName();
    OutReport.bCompileSuccess = true; // Assume success initially

    // Check Renderers and Spawn
    if (System->GetEmitterHandles().Num() == 0)
    {
        OutReport.Errors.Add(TEXT("System has no emitters."));
        OutReport.bCompileSuccess = false;
    }

    for (const FNiagaraEmitterHandle& EmitterHandleRef : System->GetEmitterHandles())
    {
        FString HandleName = EmitterHandleRef.GetName().ToString();
        TArray<UNiagaraRendererProperties*> TmpRenderers = GetEmitterRenderers(EmitterHandleRef.GetInstance().Emitter);
        bool bHasRenderers = TmpRenderers.Num() > 0;

        if (!bHasRenderers)
        {
            OutReport.Errors.Add(FString::Printf(TEXT("Emitter %s has no renderers (renderer detection may be limited on this engine version)."), *HandleName));
        }

        // Check Spawn parameters
        bool bHasSpawn = false;
        FNiagaraParameterStore& Store = System->GetExposedParameters();
        TArray<FNiagaraVariable> Vars;
        Store.GetParameters(Vars);
        
        for(const FNiagaraVariable& Var : Vars)
        {
            if(Var.GetName().ToString().Contains(HandleName) && 
               (Var.GetName().ToString().Contains("SpawnRate") || Var.GetName().ToString().Contains("SpawnBurst")))
            {
                if(Var.IsDataInterface()) continue;
                if(Var.GetType() == FNiagaraTypeDefinition::GetFloatDef())
                {
                    if(Store.GetParameterValue<float>(Var) > 0.0f) bHasSpawn = true;
                }
                else if(Var.GetType() == FNiagaraTypeDefinition::GetIntDef())
                {
                    if(Store.GetParameterValue<int32>(Var) > 0) bHasSpawn = true;
                }
            }
        }
    }
    
    // Check overall validity
    if (!System->IsValid())
    {
        OutReport.Errors.Add(TEXT("Niagara System reported as Invalid."));
        OutReport.bCompileSuccess = false;
    }

    return OutReport.bCompileSuccess;
}
