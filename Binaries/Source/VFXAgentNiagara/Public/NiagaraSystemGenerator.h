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
		const FVFXRecipe& Recipe) override;

	virtual bool UpdateNiagaraSystem(
		UNiagaraSystem* System,
		const FVFXRecipe& Recipe) override;
	
	// Factory function
	static FORCEINLINE UNiagaraSystemGenerator* CreateInstance()
	{
		return NewObject<UNiagaraSystemGenerator>();
	}

private:
	// Helper functions
	class UNiagaraEmitter* CreateBasicEmitter(
		const FVFXEmitterRecipe& EmitterRecipe,
		UNiagaraSystem* ParentSystem);

	bool BindMaterialToEmitter(
		class UNiagaraEmitter* Emitter,
		const FVFXMaterialRecipe& MaterialRecipe);

	// Get or create a basic material
	class UMaterialInstanceConstant* GetOrCreateBasicMaterial(
		const FString& Path,
		const FVFXMaterialRecipe& MaterialRecipe);
};