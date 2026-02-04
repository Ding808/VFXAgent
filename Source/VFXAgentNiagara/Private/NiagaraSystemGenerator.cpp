#include "NiagaraSystemGenerator.h"
#include "NiagaraSpecExecutor.h"
#include "VFXRecipeCompiler.h"
#include "VFXAgentLog.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "Materials/MaterialInterface.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Modules/ModuleManager.h"
#include "Misc/ConfigCacheIni.h"
#include "UObject/UnrealType.h"

// NOTE: Removed automatic repair/retry logic that appended "_Fixed" to the system name.
// Generation now performs a single Create + Save/Compile + SelfCheck pass.

UNiagaraSystem* UNiagaraSystemGenerator::GenerateNiagaraSystem(
    const FString& SystemName,
    const FString& OutputPath,
    const FVFXRecipe& Recipe,
    const FString& TemplateSystemPath)
{
    UE_LOG(LogVFXAgent, Log, TEXT("Starting Recipe-Driven Niagara Generation for: %s"), *SystemName);

    TArray<FString> Warnings;
    FVFXEffectSpec Spec = FRecipeCompiler::Compile(SystemName, OutputPath, Recipe, TemplateSystemPath, Warnings);

    if (Warnings.Num() > 0)
    {
        for (const FString& W : Warnings)
        {
            UE_LOG(LogVFXAgent, Warning, TEXT("Recipe Warning: %s"), *W);
        }
    }

    UE_LOG(LogVFXAgent, Log, TEXT("Generating System (single attempt)"));
    FVFXRepairReport Report;
    UNiagaraSystem* ResultSystem = FSystemAssembler::Assemble(Spec, Report);
    if (!ResultSystem)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Failed to assemble system from recipe: %s"), *SystemName);
        return nullptr;
    }

    // Assign materials from the library (no material generation)
    AssignMaterialsFromLibrary(Recipe, ResultSystem);

    // Apply collision event handlers (module-stack level) after system creation
    if (Recipe.Events.Num() > 0)
    {
        for (const FVFXEventRecipe& Event : Recipe.Events)
        {
            if (Event.Type == EVFXEventType::OnEmitterCollision)
            {
                FNiagaraSpecExecutor::ConfigureCollisionEventHandler(ResultSystem, Event.SourceLayer, Event.TargetLayer, Event);
            }
        }
    }

    if (FNiagaraSpecExecutor::SaveCompileAndSelfCheck(ResultSystem, Report))
    {
        UE_LOG(LogVFXAgent, Log, TEXT("Generation Success! Asset: %s"), *Report.SystemPath);
        return ResultSystem;
    }

    UE_LOG(LogVFXAgent, Warning, TEXT("SelfCheck Failed for system '%s' but automatic repair/retry is disabled."), *Spec.Name);
    for (const FString& E : Report.Errors)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("Error: %s"), *E);
    }

    // Return the generated system even if self-check failed; caller can decide further action.
    return ResultSystem;
}

bool UNiagaraSystemGenerator::UpdateNiagaraSystem(UNiagaraSystem* System, const FVFXRecipe& Recipe)
{
    // Simplified update using Executor's Configure
    if (!System) return false;

    TArray<FString> Warnings;
    FVFXEffectSpec Spec = FRecipeCompiler::Compile(System->GetName(), System->GetPathName(), Recipe, FString(), Warnings);
    if (Spec.Emitters.Num() == 0) return false;

    for (const FVFXEmitterSpec& EmitterSpec : Spec.Emitters)
    {
        FNiagaraSpecExecutor::ConfigureEmitter(System, EmitterSpec.Name, EmitterSpec);
    }

    if (Recipe.Events.Num() > 0)
    {
        for (const FVFXEventRecipe& Event : Recipe.Events)
        {
            if (Event.Type == EVFXEventType::OnEmitterCollision)
            {
                FNiagaraSpecExecutor::ConfigureCollisionEventHandler(System, Event.SourceLayer, Event.TargetLayer, Event);
            }
        }
    }
    return true;
}

static TArray<FString> GetMaterialLibraryPaths()
{
    TArray<FString> Paths;
    const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
    const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
    for (const FString& File : ConfigFiles)
    {
        if (GConfig && GConfig->GetArray(Section, TEXT("MaterialLibraryPaths"), Paths, File) && Paths.Num() > 0)
        {
            break;
        }
    }
    if (Paths.Num() == 0)
    {
        Paths.Add(TEXT("/Game/VFXAgent/Materials"));
    }
    return Paths;
}

static void CollectMaterialAssets(const TArray<FString>& RootPaths, TArray<FAssetData>& OutAssets)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    FARFilter Filter;
    for (const FString& Root : RootPaths)
    {
        Filter.PackagePaths.Add(*Root);
    }
    Filter.ClassPaths.Add(UMaterialInterface::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UMaterial::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UMaterialInstanceConstant::StaticClass()->GetClassPathName());
    Filter.bRecursivePaths = true;
    AssetRegistryModule.Get().GetAssets(Filter, OutAssets);
}

static void AppendKeywordsFromText(const FString& Text, TSet<FString>& Out)
{
    FString Token;
    for (int32 i = 0; i < Text.Len(); ++i)
    {
        const TCHAR C = Text[i];
        if (FChar::IsAlnum(C))
        {
            Token.AppendChar(FChar::ToLower(C));
        }
        else if (!Token.IsEmpty())
        {
            if (Token.Len() > 2)
            {
                Out.Add(Token);
            }
            Token.Reset();
        }
    }
    if (Token.Len() > 2)
    {
        Out.Add(Token);
    }

    const FString Lower = Text.ToLower();
    if (Lower.Contains(TEXT("烟")) || Lower.Contains(TEXT("雾"))) Out.Add(TEXT("smoke"));
    if (Lower.Contains(TEXT("火")) || Lower.Contains(TEXT("焰"))) Out.Add(TEXT("fire"));
    if (Lower.Contains(TEXT("电")) || Lower.Contains(TEXT("雷"))) Out.Add(TEXT("electric"));
    if (Lower.Contains(TEXT("光")) || Lower.Contains(TEXT("辉"))) Out.Add(TEXT("glow"));
    if (Lower.Contains(TEXT("尘"))) Out.Add(TEXT("dust"));
    if (Lower.Contains(TEXT("爆"))) Out.Add(TEXT("burst"));
    if (Lower.Contains(TEXT("尾")) || Lower.Contains(TEXT("拖"))) Out.Add(TEXT("trail"));
}

static TArray<FString> BuildKeywords(const FString& Text)
{
    TSet<FString> Keywords;
    AppendKeywordsFromText(Text, Keywords);

    if (Keywords.Contains(TEXT("smoke"))) { Keywords.Add(TEXT("fog")); Keywords.Add(TEXT("mist")); }
    if (Keywords.Contains(TEXT("spark"))) { Keywords.Add(TEXT("sparks")); Keywords.Add(TEXT("ember")); }
    if (Keywords.Contains(TEXT("electric"))) { Keywords.Add(TEXT("lightning")); }
    if (Keywords.Contains(TEXT("fire"))) { Keywords.Add(TEXT("flame")); }
    if (Keywords.Contains(TEXT("trail"))) { Keywords.Add(TEXT("ribbon")); }
    if (Keywords.Contains(TEXT("glow"))) { Keywords.Add(TEXT("flare")); }

    TArray<FString> Result = Keywords.Array();
    return Result;
}

static int32 ScoreMaterialName(const FString& MaterialNameLower, const TArray<FString>& Keywords)
{
    int32 Score = 0;
    for (const FString& Key : Keywords)
    {
        if (MaterialNameLower == Key)
        {
            Score += 20;
        }
        else if (MaterialNameLower.Contains(Key))
        {
            Score += 10;
        }
    }
    return Score;
}

static FString NormalizeEmitterNameForMatch(const FString& Name)
{
    FString Result = Name;
    while (Result.Len() > 0 && FChar::IsDigit(Result[Result.Len() - 1]))
    {
        Result.LeftChopInline(1);
    }
    return Result.ToLower();
}

void UNiagaraSystemGenerator::AssignMaterialsFromLibrary(
    const FVFXRecipe& Recipe,
    UNiagaraSystem* System)
{
    if (!System)
    {
        UE_LOG(LogVFXAgent, Error, TEXT("Cannot assign materials for null system"));
        return;
    }

    const TArray<FString> LibraryPaths = GetMaterialLibraryPaths();
    TArray<FAssetData> MaterialAssets;
    CollectMaterialAssets(LibraryPaths, MaterialAssets);

    if (MaterialAssets.Num() == 0)
    {
        UE_LOG(LogVFXAgent, Warning, TEXT("No materials found in library paths. Using default Niagara material."));
    }

    TArray<TArray<FString>> MaterialKeywords;
    MaterialKeywords.Reserve(Recipe.Materials.Num());
    for (const FVFXMaterialRecipe& Mat : Recipe.Materials)
    {
        MaterialKeywords.Add(BuildKeywords(Mat.Name + TEXT(" ") + Mat.Description));
    }

    TMap<FString, TArray<FString>> EmitterKeywords;
    for (const FVFXLayerRecipe& Layer : Recipe.Layers)
    {
        EmitterKeywords.Add(Layer.Name.ToLower(), BuildKeywords(Layer.Name + TEXT(" ") + Layer.Role));
    }
    for (const FVFXEmitterRecipe& Emitter : Recipe.Emitters)
    {
        EmitterKeywords.Add(Emitter.Name.ToLower(), BuildKeywords(Emitter.Name + TEXT(" ") + Emitter.RendererType));
    }

    // Helper to retrieve renderer properties from a UNiagaraEmitter using reflection.
    auto GetEmitterRenderers = [](UNiagaraEmitter* Emitter)
    {
        TArray<UNiagaraRendererProperties*> Result;
        if (!Emitter) return Result;
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
            break;
        }
        return Result;
    };

    auto ApplyMaterialToEmitter = [&](UNiagaraEmitter* Emitter, UMaterialInterface* Material)
    {
        if (!Emitter || !Material) return;
        TArray<UNiagaraRendererProperties*> Renderers = GetEmitterRenderers(Emitter);
        for (UNiagaraRendererProperties* Prop : Renderers)
        {
            if (!Prop) continue;
            if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Prop))
            {
                Sprite->Material = Material;
            }
            else if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Prop))
            {
                Ribbon->Material = Material;
            }
        }
        Emitter->Modify();
        Emitter->PostEditChange();
    };

    auto PickMaterialByKeywords = [&](const TArray<FString>& Keywords) -> UMaterialInterface*
    {
        int32 BestScore = 0;
        FAssetData BestAsset;
        for (const FAssetData& Asset : MaterialAssets)
        {
            const FString AssetNameLower = Asset.AssetName.ToString().ToLower();
            const int32 Score = ScoreMaterialName(AssetNameLower, Keywords);
            if (Score > BestScore)
            {
                BestScore = Score;
                BestAsset = Asset;
            }
        }
        if (BestScore == 0)
        {
            return nullptr;
        }
        return LoadObject<UMaterialInterface>(nullptr, *BestAsset.GetObjectPathString());
    };

    UMaterialInterface* DefaultMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Niagara/DefaultAssets/DefaultSpriteMaterial.DefaultSpriteMaterial"));

    const TArray<FNiagaraEmitterHandle>& Handles = System->GetEmitterHandles();
    for (const FNiagaraEmitterHandle& Handle : Handles)
    {
        UNiagaraEmitter* Emitter = Handle.GetInstance().Emitter;
        if (!Emitter) continue;

        const FString HandleName = Handle.GetName().ToString();
        const FString Normalized = NormalizeEmitterNameForMatch(HandleName);

        int32 MatIndex = -1;
        for (const FVFXEmitterRecipe& EmitterRecipe : Recipe.Emitters)
        {
            if (NormalizeEmitterNameForMatch(EmitterRecipe.Name) == Normalized)
            {
                MatIndex = EmitterRecipe.MaterialIndex;
                break;
            }
        }
        for (const FVFXLayerRecipe& Layer : Recipe.Layers)
        {
            if (NormalizeEmitterNameForMatch(Layer.Name) == Normalized)
            {
                MatIndex = (MatIndex >= 0) ? MatIndex : Layer.MaterialIndex;
                break;
            }
        }

        TArray<FString> Keywords;
        if (MatIndex >= 0 && MaterialKeywords.IsValidIndex(MatIndex))
        {
            Keywords = MaterialKeywords[MatIndex];
        }
        else if (EmitterKeywords.Contains(Normalized))
        {
            Keywords = EmitterKeywords[Normalized];
        }
        else
        {
            Keywords = BuildKeywords(HandleName);
        }

        UMaterialInterface* ChosenMaterial = PickMaterialByKeywords(Keywords);
        if (!ChosenMaterial && MaterialAssets.Num() > 0)
        {
            ChosenMaterial = LoadObject<UMaterialInterface>(nullptr, *MaterialAssets[0].GetObjectPathString());
        }
        if (!ChosenMaterial)
        {
            ChosenMaterial = DefaultMaterial;
        }

        if (ChosenMaterial)
        {
            ApplyMaterialToEmitter(Emitter, ChosenMaterial);
        }
    }
}
