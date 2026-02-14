// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentNiagara/Public/VFXIterativeOptimizer.h"
#include "VFXAgentCore/Public/VFXRecipe.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVFXIterativeOptimizer() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
NIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXRecipe();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UVFXIterativeOptimizer();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UVFXIterativeOptimizer_NoRegister();
VFXAGENTNIAGARA_API UScriptStruct* Z_Construct_UScriptStruct_FVFXOptimizationConfig();
VFXAGENTNIAGARA_API UScriptStruct* Z_Construct_UScriptStruct_FVFXOptimizationResult();
// End Cross Module References

// Begin ScriptStruct FVFXOptimizationResult
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXOptimizationResult;
class UScriptStruct* FVFXOptimizationResult::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXOptimizationResult.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXOptimizationResult.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXOptimizationResult, (UObject*)Z_Construct_UPackage__Script_VFXAgentNiagara(), TEXT("VFXOptimizationResult"));
	}
	return Z_Registration_Info_UScriptStruct_VFXOptimizationResult.OuterSingleton;
}
template<> VFXAGENTNIAGARA_API UScriptStruct* StaticStruct<FVFXOptimizationResult>()
{
	return FVFXOptimizationResult::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Result of a single optimization iteration\n */" },
#endif
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Result of a single optimization iteration" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IterationCount_MetaData[] = {
		{ "Category", "Optimization" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_QualityScore_MetaData[] = {
		{ "Category", "Optimization" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FeedbackMessage_MetaData[] = {
		{ "Category", "Optimization" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 0-1, where 1 is perfect match\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0-1, where 1 is perfect match" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bShouldContinue_MetaData[] = {
		{ "Category", "Optimization" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ImprovementSuggestions_MetaData[] = {
		{ "Category", "Optimization" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_IterationCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_QualityScore;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FeedbackMessage;
	static void NewProp_bShouldContinue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bShouldContinue;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ImprovementSuggestions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ImprovementSuggestions;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXOptimizationResult>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_IterationCount = { "IterationCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationResult, IterationCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IterationCount_MetaData), NewProp_IterationCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_QualityScore = { "QualityScore", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationResult, QualityScore), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QualityScore_MetaData), NewProp_QualityScore_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_FeedbackMessage = { "FeedbackMessage", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationResult, FeedbackMessage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FeedbackMessage_MetaData), NewProp_FeedbackMessage_MetaData) };
void Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_bShouldContinue_SetBit(void* Obj)
{
	((FVFXOptimizationResult*)Obj)->bShouldContinue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_bShouldContinue = { "bShouldContinue", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXOptimizationResult), &Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_bShouldContinue_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bShouldContinue_MetaData), NewProp_bShouldContinue_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_ImprovementSuggestions_Inner = { "ImprovementSuggestions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_ImprovementSuggestions = { "ImprovementSuggestions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationResult, ImprovementSuggestions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ImprovementSuggestions_MetaData), NewProp_ImprovementSuggestions_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_IterationCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_QualityScore,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_FeedbackMessage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_bShouldContinue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_ImprovementSuggestions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewProp_ImprovementSuggestions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentNiagara,
	nullptr,
	&NewStructOps,
	"VFXOptimizationResult",
	Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::PropPointers),
	sizeof(FVFXOptimizationResult),
	alignof(FVFXOptimizationResult),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXOptimizationResult()
{
	if (!Z_Registration_Info_UScriptStruct_VFXOptimizationResult.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXOptimizationResult.InnerSingleton, Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXOptimizationResult.InnerSingleton;
}
// End ScriptStruct FVFXOptimizationResult

// Begin ScriptStruct FVFXOptimizationConfig
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXOptimizationConfig;
class UScriptStruct* FVFXOptimizationConfig::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXOptimizationConfig.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXOptimizationConfig.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXOptimizationConfig, (UObject*)Z_Construct_UPackage__Script_VFXAgentNiagara(), TEXT("VFXOptimizationConfig"));
	}
	return Z_Registration_Info_UScriptStruct_VFXOptimizationConfig.OuterSingleton;
}
template<> VFXAGENTNIAGARA_API UScriptStruct* StaticStruct<FVFXOptimizationConfig>()
{
	return FVFXOptimizationConfig::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Configuration for iterative optimization\n */" },
#endif
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Configuration for iterative optimization" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxIterations_MetaData[] = {
		{ "Category", "Optimization" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetQualityScore_MetaData[] = {
		{ "Category", "Optimization" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnableVisualComparison_MetaData[] = {
		{ "Category", "Optimization" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Stop when quality reaches this threshold\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stop when quality reaches this threshold" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReferenceImagePath_MetaData[] = {
		{ "Category", "Optimization" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Compare with reference image\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Compare with reference image" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OriginalPrompt_MetaData[] = {
		{ "Category", "Optimization" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxIterations;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TargetQualityScore;
	static void NewProp_bEnableVisualComparison_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnableVisualComparison;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReferenceImagePath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OriginalPrompt;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXOptimizationConfig>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_MaxIterations = { "MaxIterations", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationConfig, MaxIterations), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxIterations_MetaData), NewProp_MaxIterations_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_TargetQualityScore = { "TargetQualityScore", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationConfig, TargetQualityScore), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetQualityScore_MetaData), NewProp_TargetQualityScore_MetaData) };
void Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_bEnableVisualComparison_SetBit(void* Obj)
{
	((FVFXOptimizationConfig*)Obj)->bEnableVisualComparison = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_bEnableVisualComparison = { "bEnableVisualComparison", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXOptimizationConfig), &Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_bEnableVisualComparison_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnableVisualComparison_MetaData), NewProp_bEnableVisualComparison_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_ReferenceImagePath = { "ReferenceImagePath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationConfig, ReferenceImagePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReferenceImagePath_MetaData), NewProp_ReferenceImagePath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_OriginalPrompt = { "OriginalPrompt", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXOptimizationConfig, OriginalPrompt), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OriginalPrompt_MetaData), NewProp_OriginalPrompt_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_MaxIterations,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_TargetQualityScore,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_bEnableVisualComparison,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_ReferenceImagePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewProp_OriginalPrompt,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentNiagara,
	nullptr,
	&NewStructOps,
	"VFXOptimizationConfig",
	Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::PropPointers),
	sizeof(FVFXOptimizationConfig),
	alignof(FVFXOptimizationConfig),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXOptimizationConfig()
{
	if (!Z_Registration_Info_UScriptStruct_VFXOptimizationConfig.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXOptimizationConfig.InnerSingleton, Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXOptimizationConfig.InnerSingleton;
}
// End ScriptStruct FVFXOptimizationConfig

// Begin Class UVFXIterativeOptimizer Function EvaluateEffect
struct Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics
{
	struct VFXIterativeOptimizer_eventEvaluateEffect_Parms
	{
		FVFXRecipe Recipe;
		UNiagaraSystem* GeneratedSystem;
		FVFXOptimizationConfig Config;
		FVFXOptimizationResult ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n\x09 * Evaluate the quality of a generated effect\n\x09 * @param Recipe Current recipe\n\x09 * @param GeneratedSystem The generated Niagara system\n\x09 * @param Config Optimization configuration\n\x09 * @return Evaluation result with quality score and feedback\n\x09 */" },
#endif
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Evaluate the quality of a generated effect\n@param Recipe Current recipe\n@param GeneratedSystem The generated Niagara system\n@param Config Optimization configuration\n@return Evaluation result with quality score and feedback" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Recipe_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Config_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Recipe;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_GeneratedSystem;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Config;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_Recipe = { "Recipe", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VFXIterativeOptimizer_eventEvaluateEffect_Parms, Recipe), Z_Construct_UScriptStruct_FVFXRecipe, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Recipe_MetaData), NewProp_Recipe_MetaData) }; // 1585434955
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_GeneratedSystem = { "GeneratedSystem", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VFXIterativeOptimizer_eventEvaluateEffect_Parms, GeneratedSystem), Z_Construct_UClass_UNiagaraSystem_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_Config = { "Config", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VFXIterativeOptimizer_eventEvaluateEffect_Parms, Config), Z_Construct_UScriptStruct_FVFXOptimizationConfig, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Config_MetaData), NewProp_Config_MetaData) }; // 3612963578
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(VFXIterativeOptimizer_eventEvaluateEffect_Parms, ReturnValue), Z_Construct_UScriptStruct_FVFXOptimizationResult, METADATA_PARAMS(0, nullptr) }; // 1374944883
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_Recipe,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_GeneratedSystem,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_Config,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UVFXIterativeOptimizer, nullptr, "EvaluateEffect", nullptr, nullptr, Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::PropPointers), sizeof(Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::VFXIterativeOptimizer_eventEvaluateEffect_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00420401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::Function_MetaDataParams), Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::VFXIterativeOptimizer_eventEvaluateEffect_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UVFXIterativeOptimizer::execEvaluateEffect)
{
	P_GET_STRUCT_REF(FVFXRecipe,Z_Param_Out_Recipe);
	P_GET_OBJECT(UNiagaraSystem,Z_Param_GeneratedSystem);
	P_GET_STRUCT_REF(FVFXOptimizationConfig,Z_Param_Out_Config);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FVFXOptimizationResult*)Z_Param__Result=P_THIS->EvaluateEffect(Z_Param_Out_Recipe,Z_Param_GeneratedSystem,Z_Param_Out_Config);
	P_NATIVE_END;
}
// End Class UVFXIterativeOptimizer Function EvaluateEffect

// Begin Class UVFXIterativeOptimizer
void UVFXIterativeOptimizer::StaticRegisterNativesUVFXIterativeOptimizer()
{
	UClass* Class = UVFXIterativeOptimizer::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "EvaluateEffect", &UVFXIterativeOptimizer::execEvaluateEffect },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVFXIterativeOptimizer);
UClass* Z_Construct_UClass_UVFXIterativeOptimizer_NoRegister()
{
	return UVFXIterativeOptimizer::StaticClass();
}
struct Z_Construct_UClass_UVFXIterativeOptimizer_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Manages iterative optimization of VFX effects using LLM feedback\n */" },
#endif
		{ "IncludePath", "VFXIterativeOptimizer.h" },
		{ "ModuleRelativePath", "Public/VFXIterativeOptimizer.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Manages iterative optimization of VFX effects using LLM feedback" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UVFXIterativeOptimizer_EvaluateEffect, "EvaluateEffect" }, // 3651320186
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVFXIterativeOptimizer>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UVFXIterativeOptimizer_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentNiagara,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXIterativeOptimizer_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UVFXIterativeOptimizer_Statics::ClassParams = {
	&UVFXIterativeOptimizer::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXIterativeOptimizer_Statics::Class_MetaDataParams), Z_Construct_UClass_UVFXIterativeOptimizer_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UVFXIterativeOptimizer()
{
	if (!Z_Registration_Info_UClass_UVFXIterativeOptimizer.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVFXIterativeOptimizer.OuterSingleton, Z_Construct_UClass_UVFXIterativeOptimizer_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UVFXIterativeOptimizer.OuterSingleton;
}
template<> VFXAGENTNIAGARA_API UClass* StaticClass<UVFXIterativeOptimizer>()
{
	return UVFXIterativeOptimizer::StaticClass();
}
UVFXIterativeOptimizer::UVFXIterativeOptimizer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UVFXIterativeOptimizer);
UVFXIterativeOptimizer::~UVFXIterativeOptimizer() {}
// End Class UVFXIterativeOptimizer

// Begin Registration
struct Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FVFXOptimizationResult::StaticStruct, Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics::NewStructOps, TEXT("VFXOptimizationResult"), &Z_Registration_Info_UScriptStruct_VFXOptimizationResult, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXOptimizationResult), 1374944883U) },
		{ FVFXOptimizationConfig::StaticStruct, Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics::NewStructOps, TEXT("VFXOptimizationConfig"), &Z_Registration_Info_UScriptStruct_VFXOptimizationConfig, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXOptimizationConfig), 3612963578U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UVFXIterativeOptimizer, UVFXIterativeOptimizer::StaticClass, TEXT("UVFXIterativeOptimizer"), &Z_Registration_Info_UClass_UVFXIterativeOptimizer, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVFXIterativeOptimizer), 3236600667U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_1211393433(TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
