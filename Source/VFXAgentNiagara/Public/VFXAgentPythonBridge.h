#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "VFXAgentPythonBridge.generated.h"

USTRUCT(BlueprintType)
struct FMeshyTaskInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	FString RunId;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	FString TaskID;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	FString Status;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	class UStaticMesh* ResultMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	FString OutputPath;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	FString Error;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	float ElapsedSeconds = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	bool bCompleted = false;

	UPROPERTY(BlueprintReadOnly, Category = "VFXAgent|Python")
	bool bSucceeded = false;
};

UCLASS()
class VFXAGENTNIAGARA_API UVFXAgentPythonBridge : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool PrepareEditorContext(const FString& RootPath = TEXT("/Niagara"));

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static FString CreateSystem(const FString& TargetPath, const FString& SystemName);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool SetActiveSystemContext(const FString& SystemObjectPath);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool CreateEmitter(const FString& SystemObjectPath, const FString& TemplateName, const FString& EmitterName);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool BindEmitterMaterial(const FString& SystemObjectPath, const FString& EmitterName, const FString& MaterialObjectPath);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static int32 GetEmitterCount(const FString& SystemObjectPath);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool SaveCompile(const FString& SystemObjectPath, FString& OutReport);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool SaveCompileSimple(const FString& SystemObjectPath);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static FString GenerateMesh(const FString& Prompt, const FString& Format = TEXT("glb"));

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static FString GenerateMeshBlocking(const FString& Prompt, const FString& Format = TEXT("glb"));

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static FString GenerateMeshAsync(
		const FString& Prompt,
		const FString& Format = TEXT("glb"),
		const FString& OnReadyPythonCallback = TEXT(""));

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static FString GetMeshTaskStatus(const FString& TaskId);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static FMeshyTaskInfo GetMeshTaskInfo(const FString& TaskId);

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static FString GetMeshyEndpoint();

	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static void PushPythonErrorToBuffer(const FString& ErrorMessage);

	// -------------------------------------------------------------------------
	// Template-based emitter creation
	// -------------------------------------------------------------------------

	/** Load a built-in Niagara emitter template and add a copy to TargetSystem.
	 *  TemplateAssetPath  – full UE asset path, e.g.
	 *    /Niagara/DefaultAssets/Templates/Emitters/Fountain.Fountain
	 *  NewEmitterName     – name assigned to the newly added emitter handle.
	 *  Returns true on success. */
	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool AddEmitterFromTemplate(
		UNiagaraSystem* TargetSystem,
		const FString& TemplateAssetPath,
		const FString& NewEmitterName);

	// -------------------------------------------------------------------------
	// User Parameter setters (modify exposed User.* parameters on a system)
	// -------------------------------------------------------------------------

	/** Set a float User Parameter on a Niagara System (e.g. "User.SpawnRate"). */
	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool SetUserParameterFloat(
		UNiagaraSystem* System,
		const FString& ParamName,
		float Value);

	/** Set a vector User Parameter on a Niagara System (e.g. "User.Velocity"). */
	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool SetUserParameterVector(
		UNiagaraSystem* System,
		const FString& ParamName,
		FVector Value);

	/** Set a linear-color User Parameter on a Niagara System (e.g. "User.Color"). */
	UFUNCTION(BlueprintCallable, Category = "VFXAgent|Python")
	static bool SetUserParameterColor(
		UNiagaraSystem* System,
		const FString& ParamName,
		FLinearColor Value);
};
