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
	FString LLMModel = "gpt-5o";

	// For OpenAI-compatible endpoints (e.g. https://api.openai.com/v1/chat/completions)
	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM API Key", PasswordField="true"))
	FString LLMApiKey = "";

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Backend"))
	FString LLMBackend = "OpenAI"; // Mock | OpenAI | GPT5o | Ollama | ChatGPT

	UPROPERTY(EditAnywhere, config, Category = "LLM", meta=(DisplayName="LLM Timeout Seconds", ClampMin="1.0"))
	float LLMTimeoutSeconds = 120.0f;

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultOutputPath = "/Game/VFXAgent/Generated";

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString DefaultTemplatePath = "/Game/VFXAgent/Templates/SimpleSpriteSystem.SimpleSpriteSystem";

	// If false, generator will create emitters without using templates.
	UPROPERTY(EditAnywhere, config, Category = "Generation")
	bool bUseTemplates = true;

	// If true, any attempt to use templates will be blocked (recommended).
	UPROPERTY(EditAnywhere, config, Category = "Generation")
	bool bDisallowTemplates = true;

	// If true, build pipeline validates but does not create assets.
	UPROPERTY(EditAnywhere, config, Category = "Generation")
	bool bDryRun = false;

	UPROPERTY(EditAnywhere, config, Category = "Generation")
	FString AssetNamePrefix = "VFX_";

	// Preferred material library search roots for auto material selection
	UPROPERTY(EditAnywhere, config, Category = "Materials", meta=(DisplayName="Material Library Paths"))
	TArray<FString> MaterialLibraryPaths;

	// Preferred providers for model services
	UPROPERTY(EditAnywhere, config, Category = "Providers", meta=(DisplayName="Preferred ImageGen Provider"))
	FString PreferredImageGenProvider = "Local";

	UPROPERTY(EditAnywhere, config, Category = "Providers", meta=(DisplayName="Preferred ImageTo3D Provider"))
	FString PreferredImageTo3DProvider = "Local";

	UPROPERTY(EditAnywhere, config, Category = "Providers", meta=(DisplayName="ImageGen Endpoint"))
	FString ImageGenEndpoint = "";

	UPROPERTY(EditAnywhere, config, Category = "Providers", meta=(DisplayName="ImageGen API Key", PasswordField="true"))
	FString ImageGenApiKey = "";

	UPROPERTY(EditAnywhere, config, Category = "Providers", meta=(DisplayName="ImageTo3D Endpoint"))
	FString ImageTo3DEndpoint = "";

	UPROPERTY(EditAnywhere, config, Category = "Providers", meta=(DisplayName="ImageTo3D API Key", PasswordField="true"))
	FString ImageTo3DApiKey = "";

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

	// =====================================================================
	// V2 Pipeline Settings
	// =====================================================================

	/** Enable the V2 multi-candidate pipeline (EffectSpec v2 + scoring + revision). */
	UPROPERTY(EditAnywhere, config, Category = "V2 Pipeline", meta=(DisplayName="Use V2 Pipeline"))
	bool bUseV2Pipeline = true;

	/** Number of candidate specs to generate in parallel. */
	UPROPERTY(EditAnywhere, config, Category = "V2 Pipeline", meta=(DisplayName="Candidate Count", ClampMin="1", ClampMax="10"))
	int32 V2NumCandidates = 3;

	/** Target quality score (0-1). If best candidate scores below this, a revision pass runs. */
	UPROPERTY(EditAnywhere, config, Category = "V2 Pipeline", meta=(DisplayName="Target Score", ClampMin="0.0", ClampMax="1.0"))
	float V2TargetScore = 0.85f;

	/** Minimum acceptable score. Candidates below this threshold are rejected. */
	UPROPERTY(EditAnywhere, config, Category = "V2 Pipeline", meta=(DisplayName="Minimum Accept Score", ClampMin="0.0", ClampMax="1.0"))
	float V2MinAcceptScore = 0.6f;

	/** Maximum number of revision passes per pipeline run. */
	UPROPERTY(EditAnywhere, config, Category = "V2 Pipeline", meta=(DisplayName="Max Revision Passes", ClampMin="0", ClampMax="5"))
	int32 V2MaxRevisionPasses = 2;

	virtual FName GetCategoryName() const override { return FName(TEXT("VFXAgent")); }
	virtual FText GetSectionText() const override { return FText::FromString(TEXT("VFX Agent Settings")); }
};