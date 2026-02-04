#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "VFXAgentSettings.generated.h"

UCLASS(config=VFXAgent, defaultconfig)
class VFXAGENTEDITOR_API UVFXAgentSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Endpoint"))
	FString LLMEndpoint = "https://api.openai.com/v1/chat/completions";

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Model"))
	FString LLMModel = "gpt-4o-mini";

	// For OpenAI-compatible endpoints (e.g. https://api.openai.com/v1/chat/completions)
	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM API Key", PasswordField="true"))
	FString LLMApiKey = "";

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Backend"))
	FString LLMBackend = "OpenAI"; // Mock | OpenAI | Ollama | ChatGPT

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Timeout Seconds", ClampMin="1.0"))
	float LLMTimeoutSeconds = 60.0f;

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultOutputPath = "/Game/VFXAgent/Generated";

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultTemplatePath = "/Game/VFXAgent/Templates/SimpleSpriteSystem.SimpleSpriteSystem";

	// If false, generator will create emitters without using templates.
	UPROPERTY(EditAnywhere, config, Category = "Generation")
	bool bUseTemplates = true;

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString AssetNamePrefix = "VFX_";

	// Preferred material library search roots for auto material selection
	UPROPERTY(EditAnywhere, config, Category = "Materials", meta=(DisplayName="Material Library Paths"))
	TArray<FString> MaterialLibraryPaths;

	// Niagara module script paths for collision event handling
	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Collision Module Script Path"))
	FString CollisionModuleScriptPath = "/Niagara/Modules/Collision/Collision.Collision";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Generate Collision Event Script Path"))
	FString GenerateCollisionEventScriptPath = "/Niagara/Modules/Collision/Generate Collision Event.Generate Collision Event";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Receive Collision Event Script Path"))
	FString ReceiveCollisionEventScriptPath = "/Niagara/Modules/Events/Receive Collision Event.Receive Collision Event";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Event Spawn Script Path"))
	FString EventSpawnScriptPath = "/Niagara/Modules/Spawn/Spawn Burst Instantaneous.Spawn Burst Instantaneous";

	// Insert position: First | Last
	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Collision Module Insert Position"))
	FString CollisionModuleInsertPosition = "Last";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Collision Module Insert Mode"))
	FString CollisionModuleInsertMode = "Phase"; // First | Last | Phase | Anchor

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Collision Module Insert Phase"))
	FString CollisionModuleInsertPhase = "CollisionDetect";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Collision Module Insert Anchor"))
	FString CollisionModuleInsertAnchor = "@CollisionBegin";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Collision Module Insert Relative"))
	FString CollisionModuleInsertRelative = "After"; // Before | After

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Collision Module Insert Priority"))
	int32 CollisionModuleInsertPriority = 0;

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Generate Collision Event Insert Position"))
	FString GenerateCollisionEventInsertPosition = "Last";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Generate Collision Event Insert Mode"))
	FString GenerateCollisionEventInsertMode = "Anchor"; // First | Last | Phase | Anchor

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Generate Collision Event Insert Phase"))
	FString GenerateCollisionEventInsertPhase = "EventWrite";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Generate Collision Event Insert Anchor"))
	FString GenerateCollisionEventInsertAnchor = "@EventWriteEnd";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Generate Collision Event Insert Relative"))
	FString GenerateCollisionEventInsertRelative = "Before"; // Before | After

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Generate Collision Event Insert Priority"))
	int32 GenerateCollisionEventInsertPriority = 0;

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Receive Collision Event Insert Position"))
	FString ReceiveCollisionEventInsertPosition = "Last";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Receive Collision Event Insert Mode"))
	FString ReceiveCollisionEventInsertMode = "Anchor"; // First | Last | Phase | Anchor

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Receive Collision Event Insert Phase"))
	FString ReceiveCollisionEventInsertPhase = "EventWrite";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Receive Collision Event Insert Anchor"))
	FString ReceiveCollisionEventInsertAnchor = "@EventWriteEnd";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Receive Collision Event Insert Relative"))
	FString ReceiveCollisionEventInsertRelative = "Before"; // Before | After

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Receive Collision Event Insert Priority"))
	int32 ReceiveCollisionEventInsertPriority = 0;

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Event Spawn Insert Position"))
	FString EventSpawnInsertPosition = "Last";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Event Spawn Insert Mode"))
	FString EventSpawnInsertMode = "Phase"; // First | Last | Phase | Anchor

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Event Spawn Insert Phase"))
	FString EventSpawnInsertPhase = "EventWrite";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Event Spawn Insert Anchor"))
	FString EventSpawnInsertAnchor = "@EventWriteEnd";

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Event Spawn Insert Relative"))
	FString EventSpawnInsertRelative = "After"; // Before | After

	UPROPERTY(EditAnywhere, config, Category = "Niagara|Events", meta=(DisplayName="Event Spawn Insert Priority"))
	int32 EventSpawnInsertPriority = 0;

	// Global module sort rules applied to all Update stacks.
	// Format: "match=<text>;mode=contains|exact|regex;phase=Forces|CollisionDetect|EventWrite|Curves|RenderPrep;priority=0;before=@Anchor;after=@Anchor"
	UPROPERTY(EditAnywhere, config, Category = "Niagara|Sorting", meta=(DisplayName="Module Sort Rules"))
	TArray<FString> ModuleSortRules;

	virtual FName GetCategoryName() const override { return FName(TEXT("VFXAgent")); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("VFX Agent Settings")); }
};