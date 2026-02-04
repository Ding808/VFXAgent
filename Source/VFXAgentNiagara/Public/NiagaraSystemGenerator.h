#pragma once

#include "CoreMinimal.h"
#include "INiagaraSystemGenerator.h"
#include "NiagaraSystemGenerator.generated.h"

UCLASS()
class VFXAGENTNIAGARA_API UNiagaraSystemGenerator : public UObject, public INiagaraSystemGenerator
{
	GENERATED_BODY()

public:
	virtual UNiagaraSystem* GenerateNiagaraSystem(
		const FString& SystemName,
		const FString& OutputPath,
		const FVFXRecipe& Recipe,
		const FString& TemplateSystemPath) override;

	virtual bool UpdateNiagaraSystem(
		UNiagaraSystem* System,
		const FVFXRecipe& Recipe) override;
	
	// Factory function
	static FORCEINLINE UNiagaraSystemGenerator* CreateInstance()
	{
		return NewObject<UNiagaraSystemGenerator>();
	}

private:
	// Assign materials from the library to generated emitters
	void AssignMaterialsFromLibrary(
		const FVFXRecipe& Recipe,
		UNiagaraSystem* System);
};