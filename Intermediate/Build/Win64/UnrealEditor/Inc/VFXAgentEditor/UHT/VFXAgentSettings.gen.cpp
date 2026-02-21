// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentSettings.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeVFXAgentSettings() {}

// ********** Begin Cross Module References ********************************************************
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
UPackage* Z_Construct_UPackage__Script_VFXAgentEditor();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UVFXAgentSettings();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UVFXAgentSettings_NoRegister();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UVFXAgentSettings ********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UVFXAgentSettings;
UClass* UVFXAgentSettings::GetPrivateStaticClass()
{
	using TClass = UVFXAgentSettings;
	if (!Z_Registration_Info_UClass_UVFXAgentSettings.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("VFXAgentSettings"),
			Z_Registration_Info_UClass_UVFXAgentSettings.InnerSingleton,
			StaticRegisterNativesUVFXAgentSettings,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UVFXAgentSettings.InnerSingleton;
}
UClass* Z_Construct_UClass_UVFXAgentSettings_NoRegister()
{
	return UVFXAgentSettings::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UVFXAgentSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "VFXAgentSettings.h" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LLMEndpoint_MetaData[] = {
		{ "Category", "LLM" },
		{ "DisplayName", "LLM Endpoint" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LLMModel_MetaData[] = {
		{ "Category", "LLM" },
		{ "DisplayName", "LLM Model" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LLMApiKey_MetaData[] = {
		{ "Category", "LLM" },
		{ "Comment", "// For OpenAI-compatible endpoints (e.g. https://api.openai.com/v1/chat/completions)\n" },
		{ "DisplayName", "LLM API Key" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "PasswordField", "true" },
		{ "ToolTip", "For OpenAI-compatible endpoints (e.g. https:api.openai.com/v1/chat/completions)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LLMBackend_MetaData[] = {
		{ "Category", "LLM" },
		{ "DisplayName", "LLM Backend" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LLMTimeoutSeconds_MetaData[] = {
		{ "Category", "LLM" },
		{ "ClampMin", "1.0" },
		{ "Comment", "// Mock | OpenAI | GPT5o | Ollama | ChatGPT\n" },
		{ "DisplayName", "LLM Timeout Seconds" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Mock | OpenAI | GPT5o | Ollama | ChatGPT" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultOutputPath_MetaData[] = {
		{ "Category", "Generation" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultTemplatePath_MetaData[] = {
		{ "Category", "Generation" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseTemplates_MetaData[] = {
		{ "Category", "Generation" },
		{ "Comment", "// If false, generator will create emitters without using templates.\n" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "If false, generator will create emitters without using templates." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDisallowTemplates_MetaData[] = {
		{ "Category", "Generation" },
		{ "Comment", "// If true, any attempt to use templates will be blocked (recommended).\n" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "If true, any attempt to use templates will be blocked (recommended)." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDryRun_MetaData[] = {
		{ "Category", "Generation" },
		{ "Comment", "// If true, build pipeline validates but does not create assets.\n" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "If true, build pipeline validates but does not create assets." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetNamePrefix_MetaData[] = {
		{ "Category", "Generation" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaterialLibraryPaths_MetaData[] = {
		{ "Category", "Materials" },
		{ "Comment", "// Preferred material library search roots for auto material selection\n" },
		{ "DisplayName", "Material Library Paths" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Preferred material library search roots for auto material selection" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreferredImageGenProvider_MetaData[] = {
		{ "Category", "Providers" },
		{ "Comment", "// Preferred providers for model services\n" },
		{ "DisplayName", "Preferred ImageGen Provider" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Preferred providers for model services" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreferredImageTo3DProvider_MetaData[] = {
		{ "Category", "Providers" },
		{ "DisplayName", "Preferred ImageTo3D Provider" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImageGenEndpoint_MetaData[] = {
		{ "Category", "Providers" },
		{ "DisplayName", "ImageGen Endpoint" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImageGenApiKey_MetaData[] = {
		{ "Category", "Providers" },
		{ "DisplayName", "ImageGen API Key" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "PasswordField", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImageTo3DEndpoint_MetaData[] = {
		{ "Category", "Providers" },
		{ "DisplayName", "ImageTo3D Endpoint" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImageTo3DApiKey_MetaData[] = {
		{ "Category", "Providers" },
		{ "DisplayName", "ImageTo3D API Key" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "PasswordField", "true" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshyApiKey_MetaData[] = {
		{ "Category", "Providers|Meshy" },
		{ "Comment", "// Meshy API Settings\n" },
		{ "DisplayName", "Meshy API Key" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "PasswordField", "true" },
		{ "ToolTip", "Meshy API Settings" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MeshyEndpoint_MetaData[] = {
		{ "Category", "Providers|Meshy" },
		{ "DisplayName", "Meshy Endpoint" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionModuleScriptPath_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// Niagara module script paths for collision event handling\n" },
		{ "DisplayName", "Collision Module Script Path" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Niagara module script paths for collision event handling" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GenerateCollisionEventScriptPath_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Generate Collision Event Script Path" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReceiveCollisionEventScriptPath_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Receive Collision Event Script Path" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventSpawnScriptPath_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Event Spawn Script Path" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionModuleInsertPosition_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// Insert position: First | Last\n" },
		{ "DisplayName", "Collision Module Insert Position" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Insert position: First | Last" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionModuleInsertMode_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Collision Module Insert Mode" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionModuleInsertPhase_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// First | Last | Phase | Anchor\n" },
		{ "DisplayName", "Collision Module Insert Phase" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "First | Last | Phase | Anchor" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionModuleInsertAnchor_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Collision Module Insert Anchor" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionModuleInsertRelative_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Collision Module Insert Relative" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CollisionModuleInsertPriority_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// Before | After\n" },
		{ "DisplayName", "Collision Module Insert Priority" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Before | After" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GenerateCollisionEventInsertPosition_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Generate Collision Event Insert Position" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GenerateCollisionEventInsertMode_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Generate Collision Event Insert Mode" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GenerateCollisionEventInsertPhase_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// First | Last | Phase | Anchor\n" },
		{ "DisplayName", "Generate Collision Event Insert Phase" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "First | Last | Phase | Anchor" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GenerateCollisionEventInsertAnchor_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Generate Collision Event Insert Anchor" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GenerateCollisionEventInsertRelative_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Generate Collision Event Insert Relative" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GenerateCollisionEventInsertPriority_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// Before | After\n" },
		{ "DisplayName", "Generate Collision Event Insert Priority" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Before | After" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReceiveCollisionEventInsertPosition_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Receive Collision Event Insert Position" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReceiveCollisionEventInsertMode_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Receive Collision Event Insert Mode" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReceiveCollisionEventInsertPhase_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// First | Last | Phase | Anchor\n" },
		{ "DisplayName", "Receive Collision Event Insert Phase" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "First | Last | Phase | Anchor" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReceiveCollisionEventInsertAnchor_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Receive Collision Event Insert Anchor" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReceiveCollisionEventInsertRelative_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Receive Collision Event Insert Relative" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReceiveCollisionEventInsertPriority_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// Before | After\n" },
		{ "DisplayName", "Receive Collision Event Insert Priority" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Before | After" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventSpawnInsertPosition_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Event Spawn Insert Position" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventSpawnInsertMode_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Event Spawn Insert Mode" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventSpawnInsertPhase_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// First | Last | Phase | Anchor\n" },
		{ "DisplayName", "Event Spawn Insert Phase" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "First | Last | Phase | Anchor" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventSpawnInsertAnchor_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Event Spawn Insert Anchor" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventSpawnInsertRelative_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "DisplayName", "Event Spawn Insert Relative" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EventSpawnInsertPriority_MetaData[] = {
		{ "Category", "Niagara|Events" },
		{ "Comment", "// Before | After\n" },
		{ "DisplayName", "Event Spawn Insert Priority" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Before | After" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModuleSortRules_MetaData[] = {
		{ "Category", "Niagara|Sorting" },
		{ "Comment", "// Global module sort rules applied to all Update stacks.\n// Format: \"match=<text>;mode=contains|exact|regex;phase=Forces|CollisionDetect|EventWrite|Curves|RenderPrep;priority=0;before=@Anchor;after=@Anchor\"\n" },
		{ "DisplayName", "Module Sort Rules" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Global module sort rules applied to all Update stacks.\nFormat: \"match=<text>;mode=contains|exact|regex;phase=Forces|CollisionDetect|EventWrite|Curves|RenderPrep;priority=0;before=@Anchor;after=@Anchor\"" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseV2Pipeline_MetaData[] = {
		{ "Category", "V2 Pipeline" },
		{ "Comment", "/** Enable the V2 multi-candidate pipeline (EffectSpec v2 + scoring + revision). */" },
		{ "DisplayName", "Use V2 Pipeline" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Enable the V2 multi-candidate pipeline (EffectSpec v2 + scoring + revision)." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_V2NumCandidates_MetaData[] = {
		{ "Category", "V2 Pipeline" },
		{ "ClampMax", "10" },
		{ "ClampMin", "1" },
		{ "Comment", "/** Number of candidate specs to generate in parallel. */" },
		{ "DisplayName", "Candidate Count" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Number of candidate specs to generate in parallel." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_V2TargetScore_MetaData[] = {
		{ "Category", "V2 Pipeline" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Target quality score (0-1). If best candidate scores below this, a revision pass runs. */" },
		{ "DisplayName", "Target Score" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Target quality score (0-1). If best candidate scores below this, a revision pass runs." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_V2MinAcceptScore_MetaData[] = {
		{ "Category", "V2 Pipeline" },
		{ "ClampMax", "1.0" },
		{ "ClampMin", "0.0" },
		{ "Comment", "/** Minimum acceptable score. Candidates below this threshold are rejected. */" },
		{ "DisplayName", "Minimum Accept Score" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Minimum acceptable score. Candidates below this threshold are rejected." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_V2MaxRevisionPasses_MetaData[] = {
		{ "Category", "V2 Pipeline" },
		{ "ClampMax", "5" },
		{ "ClampMin", "0" },
		{ "Comment", "/** Maximum number of revision passes per pipeline run. */" },
		{ "DisplayName", "Max Revision Passes" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
		{ "ToolTip", "Maximum number of revision passes per pipeline run." },
	};
#endif // WITH_METADATA

// ********** Begin Class UVFXAgentSettings constinit property declarations ************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_LLMEndpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LLMModel;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LLMApiKey;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LLMBackend;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LLMTimeoutSeconds;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultOutputPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultTemplatePath;
	static void NewProp_bUseTemplates_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseTemplates;
	static void NewProp_bDisallowTemplates_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDisallowTemplates;
	static void NewProp_bDryRun_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDryRun;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetNamePrefix;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MaterialLibraryPaths_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_MaterialLibraryPaths;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PreferredImageGenProvider;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PreferredImageTo3DProvider;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ImageGenEndpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ImageGenApiKey;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ImageTo3DEndpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ImageTo3DApiKey;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MeshyApiKey;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MeshyEndpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CollisionModuleScriptPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GenerateCollisionEventScriptPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReceiveCollisionEventScriptPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventSpawnScriptPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CollisionModuleInsertPosition;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CollisionModuleInsertMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CollisionModuleInsertPhase;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CollisionModuleInsertAnchor;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CollisionModuleInsertRelative;
	static const UECodeGen_Private::FIntPropertyParams NewProp_CollisionModuleInsertPriority;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GenerateCollisionEventInsertPosition;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GenerateCollisionEventInsertMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GenerateCollisionEventInsertPhase;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GenerateCollisionEventInsertAnchor;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GenerateCollisionEventInsertRelative;
	static const UECodeGen_Private::FIntPropertyParams NewProp_GenerateCollisionEventInsertPriority;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReceiveCollisionEventInsertPosition;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReceiveCollisionEventInsertMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReceiveCollisionEventInsertPhase;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReceiveCollisionEventInsertAnchor;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReceiveCollisionEventInsertRelative;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReceiveCollisionEventInsertPriority;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventSpawnInsertPosition;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventSpawnInsertMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventSpawnInsertPhase;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventSpawnInsertAnchor;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EventSpawnInsertRelative;
	static const UECodeGen_Private::FIntPropertyParams NewProp_EventSpawnInsertPriority;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ModuleSortRules_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ModuleSortRules;
	static void NewProp_bUseV2Pipeline_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseV2Pipeline;
	static const UECodeGen_Private::FIntPropertyParams NewProp_V2NumCandidates;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_V2TargetScore;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_V2MinAcceptScore;
	static const UECodeGen_Private::FIntPropertyParams NewProp_V2MaxRevisionPasses;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End Class UVFXAgentSettings constinit property declarations **************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVFXAgentSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UVFXAgentSettings_Statics

// ********** Begin Class UVFXAgentSettings Property Definitions ***********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMEndpoint = { "LLMEndpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, LLMEndpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LLMEndpoint_MetaData), NewProp_LLMEndpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMModel = { "LLMModel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, LLMModel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LLMModel_MetaData), NewProp_LLMModel_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMApiKey = { "LLMApiKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, LLMApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LLMApiKey_MetaData), NewProp_LLMApiKey_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMBackend = { "LLMBackend", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, LLMBackend), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LLMBackend_MetaData), NewProp_LLMBackend_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMTimeoutSeconds = { "LLMTimeoutSeconds", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, LLMTimeoutSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LLMTimeoutSeconds_MetaData), NewProp_LLMTimeoutSeconds_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultOutputPath = { "DefaultOutputPath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, DefaultOutputPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultOutputPath_MetaData), NewProp_DefaultOutputPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultTemplatePath = { "DefaultTemplatePath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, DefaultTemplatePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultTemplatePath_MetaData), NewProp_DefaultTemplatePath_MetaData) };
void Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseTemplates_SetBit(void* Obj)
{
	((UVFXAgentSettings*)Obj)->bUseTemplates = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseTemplates = { "bUseTemplates", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UVFXAgentSettings), &Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseTemplates_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseTemplates_MetaData), NewProp_bUseTemplates_MetaData) };
void Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDisallowTemplates_SetBit(void* Obj)
{
	((UVFXAgentSettings*)Obj)->bDisallowTemplates = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDisallowTemplates = { "bDisallowTemplates", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UVFXAgentSettings), &Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDisallowTemplates_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDisallowTemplates_MetaData), NewProp_bDisallowTemplates_MetaData) };
void Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDryRun_SetBit(void* Obj)
{
	((UVFXAgentSettings*)Obj)->bDryRun = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDryRun = { "bDryRun", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UVFXAgentSettings), &Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDryRun_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDryRun_MetaData), NewProp_bDryRun_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_AssetNamePrefix = { "AssetNamePrefix", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, AssetNamePrefix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetNamePrefix_MetaData), NewProp_AssetNamePrefix_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MaterialLibraryPaths_Inner = { "MaterialLibraryPaths", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MaterialLibraryPaths = { "MaterialLibraryPaths", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, MaterialLibraryPaths), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaterialLibraryPaths_MetaData), NewProp_MaterialLibraryPaths_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_PreferredImageGenProvider = { "PreferredImageGenProvider", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, PreferredImageGenProvider), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreferredImageGenProvider_MetaData), NewProp_PreferredImageGenProvider_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_PreferredImageTo3DProvider = { "PreferredImageTo3DProvider", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, PreferredImageTo3DProvider), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreferredImageTo3DProvider_MetaData), NewProp_PreferredImageTo3DProvider_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageGenEndpoint = { "ImageGenEndpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ImageGenEndpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImageGenEndpoint_MetaData), NewProp_ImageGenEndpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageGenApiKey = { "ImageGenApiKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ImageGenApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImageGenApiKey_MetaData), NewProp_ImageGenApiKey_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageTo3DEndpoint = { "ImageTo3DEndpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ImageTo3DEndpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImageTo3DEndpoint_MetaData), NewProp_ImageTo3DEndpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageTo3DApiKey = { "ImageTo3DApiKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ImageTo3DApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImageTo3DApiKey_MetaData), NewProp_ImageTo3DApiKey_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MeshyApiKey = { "MeshyApiKey", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, MeshyApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshyApiKey_MetaData), NewProp_MeshyApiKey_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MeshyEndpoint = { "MeshyEndpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, MeshyEndpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MeshyEndpoint_MetaData), NewProp_MeshyEndpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleScriptPath = { "CollisionModuleScriptPath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, CollisionModuleScriptPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionModuleScriptPath_MetaData), NewProp_CollisionModuleScriptPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventScriptPath = { "GenerateCollisionEventScriptPath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, GenerateCollisionEventScriptPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GenerateCollisionEventScriptPath_MetaData), NewProp_GenerateCollisionEventScriptPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventScriptPath = { "ReceiveCollisionEventScriptPath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ReceiveCollisionEventScriptPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReceiveCollisionEventScriptPath_MetaData), NewProp_ReceiveCollisionEventScriptPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnScriptPath = { "EventSpawnScriptPath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, EventSpawnScriptPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventSpawnScriptPath_MetaData), NewProp_EventSpawnScriptPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertPosition = { "CollisionModuleInsertPosition", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, CollisionModuleInsertPosition), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionModuleInsertPosition_MetaData), NewProp_CollisionModuleInsertPosition_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertMode = { "CollisionModuleInsertMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, CollisionModuleInsertMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionModuleInsertMode_MetaData), NewProp_CollisionModuleInsertMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertPhase = { "CollisionModuleInsertPhase", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, CollisionModuleInsertPhase), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionModuleInsertPhase_MetaData), NewProp_CollisionModuleInsertPhase_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertAnchor = { "CollisionModuleInsertAnchor", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, CollisionModuleInsertAnchor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionModuleInsertAnchor_MetaData), NewProp_CollisionModuleInsertAnchor_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertRelative = { "CollisionModuleInsertRelative", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, CollisionModuleInsertRelative), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionModuleInsertRelative_MetaData), NewProp_CollisionModuleInsertRelative_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertPriority = { "CollisionModuleInsertPriority", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, CollisionModuleInsertPriority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CollisionModuleInsertPriority_MetaData), NewProp_CollisionModuleInsertPriority_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertPosition = { "GenerateCollisionEventInsertPosition", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, GenerateCollisionEventInsertPosition), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GenerateCollisionEventInsertPosition_MetaData), NewProp_GenerateCollisionEventInsertPosition_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertMode = { "GenerateCollisionEventInsertMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, GenerateCollisionEventInsertMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GenerateCollisionEventInsertMode_MetaData), NewProp_GenerateCollisionEventInsertMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertPhase = { "GenerateCollisionEventInsertPhase", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, GenerateCollisionEventInsertPhase), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GenerateCollisionEventInsertPhase_MetaData), NewProp_GenerateCollisionEventInsertPhase_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertAnchor = { "GenerateCollisionEventInsertAnchor", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, GenerateCollisionEventInsertAnchor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GenerateCollisionEventInsertAnchor_MetaData), NewProp_GenerateCollisionEventInsertAnchor_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertRelative = { "GenerateCollisionEventInsertRelative", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, GenerateCollisionEventInsertRelative), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GenerateCollisionEventInsertRelative_MetaData), NewProp_GenerateCollisionEventInsertRelative_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertPriority = { "GenerateCollisionEventInsertPriority", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, GenerateCollisionEventInsertPriority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GenerateCollisionEventInsertPriority_MetaData), NewProp_GenerateCollisionEventInsertPriority_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertPosition = { "ReceiveCollisionEventInsertPosition", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ReceiveCollisionEventInsertPosition), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReceiveCollisionEventInsertPosition_MetaData), NewProp_ReceiveCollisionEventInsertPosition_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertMode = { "ReceiveCollisionEventInsertMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ReceiveCollisionEventInsertMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReceiveCollisionEventInsertMode_MetaData), NewProp_ReceiveCollisionEventInsertMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertPhase = { "ReceiveCollisionEventInsertPhase", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ReceiveCollisionEventInsertPhase), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReceiveCollisionEventInsertPhase_MetaData), NewProp_ReceiveCollisionEventInsertPhase_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertAnchor = { "ReceiveCollisionEventInsertAnchor", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ReceiveCollisionEventInsertAnchor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReceiveCollisionEventInsertAnchor_MetaData), NewProp_ReceiveCollisionEventInsertAnchor_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertRelative = { "ReceiveCollisionEventInsertRelative", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ReceiveCollisionEventInsertRelative), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReceiveCollisionEventInsertRelative_MetaData), NewProp_ReceiveCollisionEventInsertRelative_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertPriority = { "ReceiveCollisionEventInsertPriority", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ReceiveCollisionEventInsertPriority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReceiveCollisionEventInsertPriority_MetaData), NewProp_ReceiveCollisionEventInsertPriority_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertPosition = { "EventSpawnInsertPosition", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, EventSpawnInsertPosition), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventSpawnInsertPosition_MetaData), NewProp_EventSpawnInsertPosition_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertMode = { "EventSpawnInsertMode", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, EventSpawnInsertMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventSpawnInsertMode_MetaData), NewProp_EventSpawnInsertMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertPhase = { "EventSpawnInsertPhase", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, EventSpawnInsertPhase), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventSpawnInsertPhase_MetaData), NewProp_EventSpawnInsertPhase_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertAnchor = { "EventSpawnInsertAnchor", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, EventSpawnInsertAnchor), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventSpawnInsertAnchor_MetaData), NewProp_EventSpawnInsertAnchor_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertRelative = { "EventSpawnInsertRelative", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, EventSpawnInsertRelative), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventSpawnInsertRelative_MetaData), NewProp_EventSpawnInsertRelative_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertPriority = { "EventSpawnInsertPriority", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, EventSpawnInsertPriority), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EventSpawnInsertPriority_MetaData), NewProp_EventSpawnInsertPriority_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ModuleSortRules_Inner = { "ModuleSortRules", nullptr, (EPropertyFlags)0x0000000000004000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ModuleSortRules = { "ModuleSortRules", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, ModuleSortRules), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModuleSortRules_MetaData), NewProp_ModuleSortRules_MetaData) };
void Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseV2Pipeline_SetBit(void* Obj)
{
	((UVFXAgentSettings*)Obj)->bUseV2Pipeline = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseV2Pipeline = { "bUseV2Pipeline", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(UVFXAgentSettings), &Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseV2Pipeline_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseV2Pipeline_MetaData), NewProp_bUseV2Pipeline_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2NumCandidates = { "V2NumCandidates", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, V2NumCandidates), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_V2NumCandidates_MetaData), NewProp_V2NumCandidates_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2TargetScore = { "V2TargetScore", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, V2TargetScore), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_V2TargetScore_MetaData), NewProp_V2TargetScore_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2MinAcceptScore = { "V2MinAcceptScore", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, V2MinAcceptScore), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_V2MinAcceptScore_MetaData), NewProp_V2MinAcceptScore_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2MaxRevisionPasses = { "V2MaxRevisionPasses", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, V2MaxRevisionPasses), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_V2MaxRevisionPasses_MetaData), NewProp_V2MaxRevisionPasses_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMEndpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMModel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMApiKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMBackend,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMTimeoutSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultOutputPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultTemplatePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseTemplates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDisallowTemplates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bDryRun,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_AssetNamePrefix,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MaterialLibraryPaths_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MaterialLibraryPaths,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_PreferredImageGenProvider,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_PreferredImageTo3DProvider,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageGenEndpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageGenApiKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageTo3DEndpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ImageTo3DApiKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MeshyApiKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_MeshyEndpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleScriptPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventScriptPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventScriptPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnScriptPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertPhase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertAnchor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertRelative,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_CollisionModuleInsertPriority,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertPhase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertAnchor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertRelative,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_GenerateCollisionEventInsertPriority,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertPhase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertAnchor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertRelative,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ReceiveCollisionEventInsertPriority,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertPosition,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertPhase,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertAnchor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertRelative,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_EventSpawnInsertPriority,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ModuleSortRules_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_ModuleSortRules,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_bUseV2Pipeline,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2NumCandidates,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2TargetScore,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2MinAcceptScore,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_V2MaxRevisionPasses,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers) < 2048);
// ********** End Class UVFXAgentSettings Property Definitions *************************************
UObject* (*const Z_Construct_UClass_UVFXAgentSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UVFXAgentSettings_Statics::ClassParams = {
	&UVFXAgentSettings::StaticClass,
	"VFXAgent",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UVFXAgentSettings_Statics::Class_MetaDataParams)
};
void UVFXAgentSettings::StaticRegisterNativesUVFXAgentSettings()
{
}
UClass* Z_Construct_UClass_UVFXAgentSettings()
{
	if (!Z_Registration_Info_UClass_UVFXAgentSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVFXAgentSettings.OuterSingleton, Z_Construct_UClass_UVFXAgentSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UVFXAgentSettings.OuterSingleton;
}
UVFXAgentSettings::UVFXAgentSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UVFXAgentSettings);
UVFXAgentSettings::~UVFXAgentSettings() {}
// ********** End Class UVFXAgentSettings **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h__Script_VFXAgentEditor_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UVFXAgentSettings, UVFXAgentSettings::StaticClass, TEXT("UVFXAgentSettings"), &Z_Registration_Info_UClass_UVFXAgentSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVFXAgentSettings), 2502320276U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h__Script_VFXAgentEditor_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h__Script_VFXAgentEditor_1368938782{
	TEXT("/Script/VFXAgentEditor"),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h__Script_VFXAgentEditor_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h__Script_VFXAgentEditor_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
