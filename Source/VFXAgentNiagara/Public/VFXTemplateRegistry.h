#pragma once

#include "CoreMinimal.h"

class UNiagaraEmitter;

class VFXAGENTNIAGARA_API FVFXTemplateRegistry
{
public:
	static FVFXTemplateRegistry& Get();

	void Initialize(const FString& RootPath);
	void Refresh();

	UNiagaraEmitter* FindByTag(const FString& Tag) const;
	UNiagaraEmitter* FindByPath(const FString& AssetPath) const;

private:
	FVFXTemplateRegistry() = default;
	void ScanAssets();

	FString RootContentPath = TEXT("/Game/VFX/Archetypes");
	TMap<FString, FString> TagToAssetPath;
	TMap<FString, FString> AssetPathToTag;
};
