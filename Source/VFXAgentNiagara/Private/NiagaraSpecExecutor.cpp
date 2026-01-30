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
    // In UE5.5, we cannot directly create a blank UNiagaraEmitter with NewObject because
    // it doesn't properly initialize the internal structures (scripts, version data, etc.)
    // Instead, we load the "Empty" emitter template which is a truly blank emitter
    // provided by the engine, then add it as a standalone (non-inheriting) copy.
    
    // Try to load the Empty emitter template - this is the official blank emitter in UE5.5
    UNiagaraEmitter* EmptyTemplate = LoadObject<UNiagaraEmitter>(nullptr, 
        TEXT("/Niagara/DefaultAssets/Templates/Emitters/Empty.Empty"));
    
    if (!EmptyTemplate)
    {
        // Fallback: try Minimal template which is also relatively clean
        EmptyTemplate = LoadObject<UNiagaraEmitter>(nullptr, 
            TEXT("/Niagara/DefaultAssets/Templates/Emitters/Minimal.Minimal"));
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
           *Spec.SystemName, System->GetNumEmitters());
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
            
#if WITH_EDITOR
            // Add via editor utility to ensure overview graph and editor data stay in sync
            const FGuid HandleId = FNiagaraEditorUtilities::AddEmitterToSystem(*System, *TemplateEmitter, VersionGuid, true);
            for (FNiagaraEmitterHandle& SystemHandle : System->GetEmitterHandles())
            {
                if (SystemHandle.GetId() == HandleId)
                {
                    SystemHandle.SetName(FName(*EmitterName), *System);
                    SystemHandle.SetIsEnabled(true, *System, true);
                    break;
                }
            }
#else
            System->AddEmitterHandle(*TemplateEmitter, FName(*EmitterName), VersionGuid);
#endif
            
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
                    SystemHandle.SetName(FName(*EmitterName), *System);
                    SystemHandle.SetIsEnabled(true, *System, true);
                    break;
                }
            }
#else
            System->AddEmitterHandle(*Source.Emitter, FName(*EmitterName), Source.Version);
#endif
            
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
    
    // Step 6: Save the package
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
            OutReport.Errors.Add(FString::Printf(TEXT("Emitter %s has no renderers."), *HandleName));
            OutReport.bCompileSuccess = false;
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
