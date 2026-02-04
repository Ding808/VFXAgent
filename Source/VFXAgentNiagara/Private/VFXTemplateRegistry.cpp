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
	if (!RootPath.IsEmpty())
	{
		RootContentPath = RootPath;
	}
	Refresh();
}

void FVFXTemplateRegistry::Refresh()
{
	TagToAssetPath.Reset();
	AssetPathToTag.Reset();
	ScanAssets();
}

UNiagaraEmitter* FVFXTemplateRegistry::FindByTag(const FString& Tag) const
{
	const FString* FoundPath = TagToAssetPath.Find(Tag.ToLower());
	if (!FoundPath)
	{
		return nullptr;
	}
	return FindByPath(*FoundPath);
}

UNiagaraEmitter* FVFXTemplateRegistry::FindByPath(const FString& AssetPath) const
{
	if (AssetPath.IsEmpty())
	{
		return nullptr;
	}
	return LoadObject<UNiagaraEmitter>(nullptr, *AssetPath);
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
