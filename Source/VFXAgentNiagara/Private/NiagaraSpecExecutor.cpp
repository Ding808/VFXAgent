#include "NiagaraSpecExecutor.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraScript.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"   
#include "NiagaraLightRendererProperties.h"
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

static bool AddBasicEmitterToSystem(UNiagaraSystem* System, const FString& EmitterName)
{
    if (!System)
    {
        return false;
    }

#if WITH_EDITOR
    FModuleManager::LoadModuleChecked<IModuleInterface>(TEXT("NiagaraEditor"));

    UClass* FactoryClass = StaticLoadClass(UFactory::StaticClass(), nullptr, TEXT("/Script/NiagaraEditor.NiagaraEmitterFactoryNew"));
    if (!FactoryClass)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to load NiagaraEmitterFactoryNew class"));
        return false;
    }

    UFactory* Factory = NewObject<UFactory>(GetTransientPackage(), FactoryClass);
    if (!Factory)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to instantiate NiagaraEmitterFactoryNew"));
        return false;
    }

    const FName UniqueObjectName = MakeUniqueObjectName(System, UNiagaraEmitter::StaticClass(), FName(*EmitterName));
    UObject* CreatedObj = Factory->FactoryCreateNew(
        UNiagaraEmitter::StaticClass(),
        System,
        UniqueObjectName,
        RF_Transactional,
        nullptr,
        GWarn);
    UNiagaraEmitter* NewEmitter = Cast<UNiagaraEmitter>(CreatedObj);
    if (!NewEmitter)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to create embedded Niagara Emitter"));
        return false;
    }

    const FGuid VersionGuid = NewEmitter->GetExposedVersion().VersionGuid;
    System->AddEmitterHandle(*NewEmitter, FName(*EmitterName), VersionGuid);
    System->MarkPackageDirty();
    if (UPackage* Pkg = System->GetOutermost())
    {
        Pkg->MarkPackageDirty();
    }

    return System->GetEmitterHandles().Num() > 0;
#else
    return false;
#endif
}

bool FNiagaraSpecExecutor::ValidateSpec(const FVFXEffectSpec& Spec, FString& OutError)
{
    if (Spec.SystemName.IsEmpty())
    {
        OutError = TEXT("SystemName is empty");
        return false;
    }
    if (Spec.TargetPath.IsEmpty())
    {
        OutError = TEXT("TargetPath is empty");
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
    UNiagaraSystem* System = CreateNiagaraSystemAsset(Spec.TargetPath, Spec.SystemName);
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

        const bool bHasTemplate = !EmitterSpec.TemplatePath.IsEmpty() || (!EmitterSpec.TemplateId.IsEmpty() && !bExplicitNoTemplate);

        bool bAdded = false;
        if (bHasTemplate)
        {
            FString Template = EmitterSpec.TemplatePath;
            if (Template.IsEmpty()) Template = FindTemplatePath(EmitterSpec.TemplateId);

            bAdded = AddEmitterFromTemplate(System, Template, EmitterSpec.Name);
            if (!bAdded)
            {
                UE_LOG(LogVFXAgent, Warning, TEXT("Failed to add emitter from template '%s'. Falling back to Fountain."), *Template);
                bAdded = AddEmitterFromTemplate(System, FindTemplatePath(TEXT("Fountain")), EmitterSpec.Name);
            }
        }
        else
        {
            bAdded = AddBasicEmitterToSystem(System, EmitterSpec.Name);
        }

        if (!bAdded)
        {
            UE_LOG(LogVFXAgent, Error, TEXT("Failed to add emitter '%s'."), *EmitterSpec.Name);
            continue;
        }

        ConfigureEmitter(System, EmitterSpec.Name, EmitterSpec);
    }

    if (System->GetEmitterHandles().Num() == 0)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("No emitters were added to system '%s'."), *Spec.SystemName);
        return nullptr;
    }

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

UNiagaraSystem* FNiagaraSpecExecutor::CreateNiagaraSystemAsset(const FString& TargetPath, const FString& SystemName)
{
    IAssetTools& AssetTools = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
    FString PackageName = FPaths::Combine(TargetPath, SystemName);
    
    // Create a new Niagara System using the Factory
    UFactory* Factory = NewObject<UFactory>(GetTransientPackage(), FindObject<UClass>(nullptr, TEXT("/Script/NiagaraEditor.NiagaraSystemFactoryNew")));
    if (!Factory) return nullptr;

    UObject* NewAsset = AssetTools.CreateAsset(SystemName, TargetPath, UNiagaraSystem::StaticClass(), Factory);
    return Cast<UNiagaraSystem>(NewAsset);
}

bool FNiagaraSpecExecutor::AddEmitterFromTemplate(UNiagaraSystem* System, const FString& TemplatePath, const FString& EmitterName)
{
    if (!System) return false;

    const FString ObjectPath = NormalizeTemplateObjectPath(TemplatePath);
    if (ObjectPath.IsEmpty())
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Template path is empty for emitter '%s'. Creating basic emitter instead."), *EmitterName);
        return AddBasicEmitterToSystem(System, EmitterName);
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
            
            // AddEmitterHandle will now create a standalone copy because bIsInheritable is false
            System->AddEmitterHandle(*TemplateEmitter, FName(*EmitterName), VersionGuid);
            
            // Restore original value on template (though it's likely a loaded asset and this may not matter)
            TemplateEmitter->bIsInheritable = bOriginalInheritable;
            
            System->MarkPackageDirty();
            if (UPackage* Pkg = System->GetOutermost())
            {
                Pkg->MarkPackageDirty();
            }
            return System->GetEmitterHandles().Num() > 0;
        }

        UE_LOG(LogVFXAgent, Warning, TEXT("Template system/emitter not found: %s. Creating basic emitter instead."), *ObjectPath);
        return AddBasicEmitterToSystem(System, EmitterName);
    }

    // Handle System templates - iterate through their emitters
    UE_LOG(LogVFXAgent, Log, TEXT("Loaded system template: %s with %d emitters"), *ObjectPath, TemplateSystem->GetEmitterHandles().Num());
    
    for (const FNiagaraEmitterHandle& Handle : TemplateSystem->GetEmitterHandles())
    {
        FVersionedNiagaraEmitter Source = Handle.GetInstance(); 
        if (Source.Emitter)
        {
            // CRITICAL: Set bIsInheritable to false to create standalone emitter
            const bool bOriginalInheritable = Source.Emitter->bIsInheritable;
            Source.Emitter->bIsInheritable = false;
            
            System->AddEmitterHandle(*Source.Emitter, FName(*EmitterName), Source.Version);
            
            // Restore original value
            Source.Emitter->bIsInheritable = bOriginalInheritable;
            break; // Only add the first emitter
        }
    }

    System->MarkPackageDirty();
    if (UPackage* Pkg = System->GetOutermost())
    {
        Pkg->MarkPackageDirty();
    }

    return System->GetEmitterHandles().Num() > 0;
}

void FNiagaraSpecExecutor::ConfigureEmitter(UNiagaraSystem* System, const FString& EmitterName, const FVFXEmitterSpec& Spec)
{
    if (!System) return;

    // Find the handle
    FNiagaraEmitterHandle* Handle = nullptr;
    for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
    {
        if (H.GetName() == FName(*EmitterName) || H.GetName() == FName(*(EmitterName + "0"))) // Name might be suffixed
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

    // 1. Configure Renderer
    // This is tricky: we need to remove existing renderers that don't match or add new ones.
    // For safety, we just add the requested one if missing.
    bool bHasCorrectRenderer = false;
    
    // Check renderers via Emitter Instance (use reflection helper)
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
        else if (Spec.RendererType == EVFXRendererType::Light) NewProps = NewObject<UNiagaraLightRendererProperties>(EmitterInstance);
        
        if (NewProps)
        {
            // AddRenderer is on UNiagaraEmitter and takes version guid
            EmitterInstance->AddRenderer(NewProps, VersionedEmitter.Version);
        }
    }

    // 2. Configure Parameters via Overrides (easiest way)
    // Common variable names in Templates
    FString Namespace = Handle->GetName().ToString();
    
    // Spawn Rate / Burst
    if (Spec.Spawn.Rate > 0)
    {
        SetVariableFloat(System, Namespace, TEXT("SpawnRate.SpawnRate"), Spec.Spawn.Rate);
    }
    if (Spec.Spawn.Burst > 0)
    {
        SetVariableFloat(System, Namespace, TEXT("SpawnBurst_Instant.SpawnBurst"), (float)Spec.Spawn.Burst);
    }

    // Basic Attributes
    SetVariableFloat(System, Namespace, TEXT("InitializeParticle.Lifetime"), Spec.Lifetime);
    SetVariableFloat(System, Namespace, TEXT("InitializeParticle.SpriteSize"), Spec.Size);
    SetVariableLinearColor(System, Namespace, TEXT("InitializeParticle.Color"), Spec.Color);
    
    // Velocity is harder as it depends on the module (Add Velocity, Velocity in Cone, etc.)
    // We try to set a generic "Velocity" var if it exists, or specific common ones.
    SetVariableVec3(System, Namespace, TEXT("AddVelocity.Velocity"), Spec.Velocity);
    SetVariableVec3(System, Namespace, TEXT("AddVelocityInCone.Velocity"), Spec.Velocity);
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

    // Compile
    System->RequestCompile(false);
    
    // Wait for compilation (blocking for simplicity in this tool context, though usually async)
    // For automation, we might need to assume it triggers.
    // In Editor, RequestCompile queues it.
    
    // Save
    FString PackageName = System->GetOutermost()->GetName();
    FSavePackageArgs SaveArgs;
    SaveArgs.TopLevelFlags = RF_Public | RF_Standalone;
    UPackage::SavePackage(System->GetOutermost(), System, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()), SaveArgs);

    // Self Check
    OutReport.SystemPath = PackageName;
    OutReport.bCompileSuccess = true; // Assume success initially

    // Check Renderers and Spawn
    if (System->GetEmitterHandles().Num() == 0)
    {
        OutReport.Errors.Add(TEXT("System has no emitters."));
        OutReport.bCompileSuccess = false;
    }

    for (const FNiagaraEmitterHandle& Handle : System->GetEmitterHandles())
    {
        FString HandleName = Handle.GetName().ToString();
        // Handle.GetInstance() returns FVersionedNiagaraEmitter, access .Emitter for renderers
        TArray<UNiagaraRendererProperties*> TmpRenderers = GetEmitterRenderers(Handle.GetInstance().Emitter);
        bool bHasRenderers = TmpRenderers.Num() > 0;

        if (!bHasRenderers)
        {
            OutReport.Errors.Add(FString::Printf(TEXT("Emitter %s has no renderers."), *HandleName));
            OutReport.bCompileSuccess = false;
        }

        // Check Spawn (Simple heuristic on Overrides)
        // We look for SpawnRate or SpawnBurst in the system overrides for this emitter
        bool bHasSpawn = false;
        
        // This is a naive check of the ParameterStore. 
        // Real validation would require inspecting the Stack.
        // We check if we have ANY variable related to spawn that is > 0.
        // In a real plugin, we might assume if we set it, it's there.
        FNiagaraParameterStore& Store = System->GetExposedParameters();
        TArray<FNiagaraVariable> Vars;
        Store.GetParameters(Vars);
        
        for(const FNiagaraVariable& Var : Vars)
        {
            if(Var.GetName().ToString().Contains(HandleName) && (Var.GetName().ToString().Contains("SpawnRate") || Var.GetName().ToString().Contains("SpawnBurst")))
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
    
    // Check Compile Status
    if (!System->IsValid())
    {
        OutReport.Errors.Add(TEXT("Niagara System Invalid."));
        OutReport.bCompileSuccess = false;
    }

    return OutReport.bCompileSuccess;
}
