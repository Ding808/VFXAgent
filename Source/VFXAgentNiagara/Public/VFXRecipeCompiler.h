#pragma once

#include "CoreMinimal.h"
#include "VFXRecipe.h"
#include "NiagaraSystem.h"
#include "NiagaraSpecExecutor.h"
#include "VFXRecipeCompiler.generated.h"

UCLASS()
class VFXAGENTNIAGARA_API UVFXRecipeCompiler : public UObject
{
	GENERATED_BODY()

public:
	static FVFXRecipe ValidateAndSanitize(const FVFXRecipe& InRecipe, TArray<FString>& OutWarnings);
	static FVFXEffectSpec CompileToSpec(const FString& SystemName, const FString& OutputPath, const FVFXRecipe& InRecipe, const FString& TemplateSystemPath, TArray<FString>& OutWarnings);
	static UNiagaraSystem* AssembleSystem(const FVFXEffectSpec& Spec, FVFXRepairReport& OutReport);
	static FString ResolveTemplatePath(const FString& TemplateId);

private:
	static void NormalizeCurve(TArray<FVFXCurveKey>& Curve, float DefaultStart, float DefaultEnd);
	static void NormalizeColorCurve(TArray<FVFXColorKey>& Curve);
	static FVFXLayerRecipe ConvertLegacyEmitter(const FVFXEmitterRecipe& Emitter);
	static FVFXEmitterSpec BuildEmitterSpecFromLayer(const FVFXLayerRecipe& Layer, const FString& TemplateSystemPath);
	static void ApplyForcesToSpec(const TArray<FVFXForceRecipe>& Forces, FVFXEmitterSpec& OutSpec, TArray<FString>& OutWarnings);
	static void ApplyCurvesToSpec(const FVFXCurveRecipe& Curves, FVFXEmitterSpec& OutSpec);
	static void ApplyRenderToSpec(const FVFXRenderRecipe& Render, FVFXEmitterSpec& OutSpec);
	static void ApplyEventsToLayers(FVFXRecipe& Recipe, TArray<FString>& OutWarnings);
};

// New pipeline interfaces
class VFXAGENTNIAGARA_API FRecipeValidator
{
public:
	static FVFXRecipe ValidateAndSanitize(const FVFXRecipe& InRecipe, TArray<FString>& OutWarnings);
};

class VFXAGENTNIAGARA_API FRecipeCompiler
{
public:
	static FVFXEffectSpec Compile(const FString& SystemName, const FString& OutputPath, const FVFXRecipe& InRecipe, const FString& TemplateSystemPath, TArray<FString>& OutWarnings);
};

class VFXAGENTNIAGARA_API FEmitterBuilder
{
public:
	static bool AddEmitter(UNiagaraSystem* System, const FVFXEmitterSpec& Spec);
};

class VFXAGENTNIAGARA_API FSystemAssembler
{
public:
	static UNiagaraSystem* Assemble(const FVFXEffectSpec& Spec, FVFXRepairReport& OutReport);
};
