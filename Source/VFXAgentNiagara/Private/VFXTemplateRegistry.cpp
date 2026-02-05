#include "VFXTemplateRegistry.h"
#include "NiagaraEmitter.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "VFXAgentLog.h"

FVFXTemplateRegistry& FVFXTemplateRegistry::Get()
{
	static FVFXTemplateRegistry Instance;
	return Instance;
}

void FVFXTemplateRegistry::Initialize(const FString& RootPath)
{
	UE_LOG(LogVFXAgent, Warning, TEXT("TemplateRegistry disabled: templates are disallowed"));
	if (!RootPath.IsEmpty())
	{
		RootContentPath = RootPath;
	}
	Refresh();
}

void FVFXTemplateRegistry::Refresh()
{
	UE_LOG(LogVFXAgent, Warning, TEXT("TemplateRegistry refresh skipped: templates are disallowed"));
	TagToAssetPath.Reset();
	AssetPathToTag.Reset();
	// Templates are disallowed; do not scan assets.
}

UNiagaraEmitter* FVFXTemplateRegistry::FindByTag(const FString& Tag) const
{
	UE_LOG(LogVFXAgent, Warning, TEXT("TemplateRegistry find-by-tag blocked: templates are disallowed"));
	return nullptr;
}

UNiagaraEmitter* FVFXTemplateRegistry::FindByPath(const FString& AssetPath) const
{
	UE_LOG(LogVFXAgent, Warning, TEXT("TemplateRegistry find-by-path blocked: templates are disallowed"));
	return nullptr;
}

void FVFXTemplateRegistry::ScanAssets()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FARFilter Filter;
	Filter.PackagePaths.Add(*RootContentPath);
	Filter.ClassPaths.Add(UNiagaraEmitter::StaticClass()->GetClassPathName());
	Filter.bRecursivePaths = true;

	TArray<FAssetData> Assets;
	AssetRegistryModule.Get().GetAssets(Filter, Assets);

	for (const FAssetData& Asset : Assets)
	{
		const FString AssetPath = Asset.GetObjectPathString();
		FString TagKey;
		FString TagValue;
		if (Asset.GetTagValue(FName("Tags"), TagValue))
		{
			TagKey = TagValue.ToLower();
		}
		if (TagKey.IsEmpty())
		{
			TagKey = Asset.AssetName.ToString().ToLower();
		}

		TagToAssetPath.Add(TagKey, AssetPath);
		AssetPathToTag.Add(AssetPath, TagKey);
	}

	UE_LOG(LogVFXAgent, Log, TEXT("TemplateRegistry: found %d emitter templates under %s"), TagToAssetPath.Num(), *RootContentPath);
}
