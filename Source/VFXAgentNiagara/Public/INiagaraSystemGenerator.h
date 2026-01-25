#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"

class INiagaraSystemGenerator
{
public:
	virtual ~INiagaraSystemGenerator() = default;

	// Generate a Niagara system from recipe
	virtual class UNiagaraSystem* GenerateNiagaraSystem(
		const FString& SystemName,
		const FString& OutputPath,
		const FVFXRecipe& Recipe) = 0;

	// Update an existing Niagara system
	virtual bool UpdateNiagaraSystem(
		class UNiagaraSystem* System,
		const FVFXRecipe& Recipe) = 0;
};