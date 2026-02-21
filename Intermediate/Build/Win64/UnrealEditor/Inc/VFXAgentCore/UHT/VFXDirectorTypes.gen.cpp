// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXDirectorTypes.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeVFXDirectorTypes() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector4();
UPackage* Z_Construct_UPackage__Script_VFXAgentCore();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXActionType();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXValueType();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXAction();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXActionValue();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXColorTheme();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXCurvePoint();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXDirectorPlan();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXExecutionReport();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXPlan();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXPlanEmitter();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXPlanEvent();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXPlanLayer();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXStyleSpec();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXValidationTargets();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FVFXColorTheme ****************************************************
struct Z_Construct_UScriptStruct_FVFXColorTheme_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXColorTheme); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXColorTheme); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Primary_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Secondary_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Accent_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXColorTheme constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Primary;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Secondary;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Accent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXColorTheme constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXColorTheme>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXColorTheme_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXColorTheme;
class UScriptStruct* FVFXColorTheme::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXColorTheme.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXColorTheme.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXColorTheme, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXColorTheme"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXColorTheme.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXColorTheme Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXColorTheme_Statics::NewProp_Primary = { "Primary", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXColorTheme, Primary), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Primary_MetaData), NewProp_Primary_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXColorTheme_Statics::NewProp_Secondary = { "Secondary", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXColorTheme, Secondary), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Secondary_MetaData), NewProp_Secondary_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXColorTheme_Statics::NewProp_Accent = { "Accent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXColorTheme, Accent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Accent_MetaData), NewProp_Accent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXColorTheme_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXColorTheme_Statics::NewProp_Primary,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXColorTheme_Statics::NewProp_Secondary,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXColorTheme_Statics::NewProp_Accent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXColorTheme_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXColorTheme Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXColorTheme_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXColorTheme",
	Z_Construct_UScriptStruct_FVFXColorTheme_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXColorTheme_Statics::PropPointers),
	sizeof(FVFXColorTheme),
	alignof(FVFXColorTheme),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXColorTheme_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXColorTheme_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXColorTheme()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXColorTheme.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXColorTheme.InnerSingleton, Z_Construct_UScriptStruct_FVFXColorTheme_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXColorTheme.InnerSingleton);
}
// ********** End ScriptStruct FVFXColorTheme ******************************************************

// ********** Begin ScriptStruct FVFXStyleSpec *****************************************************
struct Z_Construct_UScriptStruct_FVFXStyleSpec_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXStyleSpec); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXStyleSpec); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Keywords_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorTheme_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intensity_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Scale_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXStyleSpec constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Keywords_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Keywords;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ColorTheme;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Intensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Scale;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXStyleSpec constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXStyleSpec>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXStyleSpec_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXStyleSpec;
class UScriptStruct* FVFXStyleSpec::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXStyleSpec.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXStyleSpec.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXStyleSpec, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXStyleSpec"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXStyleSpec.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXStyleSpec Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Keywords_Inner = { "Keywords", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Keywords = { "Keywords", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXStyleSpec, Keywords), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Keywords_MetaData), NewProp_Keywords_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_ColorTheme = { "ColorTheme", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXStyleSpec, ColorTheme), Z_Construct_UScriptStruct_FVFXColorTheme, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorTheme_MetaData), NewProp_ColorTheme_MetaData) }; // 1370816070
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Intensity = { "Intensity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXStyleSpec, Intensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intensity_MetaData), NewProp_Intensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Scale = { "Scale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXStyleSpec, Scale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Scale_MetaData), NewProp_Scale_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Keywords_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Keywords,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_ColorTheme,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Intensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewProp_Scale,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXStyleSpec Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXStyleSpec",
	Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::PropPointers),
	sizeof(FVFXStyleSpec),
	alignof(FVFXStyleSpec),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXStyleSpec()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXStyleSpec.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXStyleSpec.InnerSingleton, Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXStyleSpec.InnerSingleton);
}
// ********** End ScriptStruct FVFXStyleSpec *******************************************************

// ********** Begin ScriptStruct FVFXPlanEmitter ***************************************************
struct Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXPlanEmitter); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXPlanEmitter); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Alias_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Template_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXPlanEmitter constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Alias;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Template;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Role;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXPlanEmitter constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXPlanEmitter>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXPlanEmitter;
class UScriptStruct* FVFXPlanEmitter::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlanEmitter.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXPlanEmitter.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXPlanEmitter, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXPlanEmitter"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXPlanEmitter.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXPlanEmitter Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::NewProp_Alias = { "Alias", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanEmitter, Alias), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Alias_MetaData), NewProp_Alias_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::NewProp_Template = { "Template", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanEmitter, Template), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Template_MetaData), NewProp_Template_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanEmitter, Role), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::NewProp_Alias,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::NewProp_Template,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::NewProp_Role,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXPlanEmitter Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXPlanEmitter",
	Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::PropPointers),
	sizeof(FVFXPlanEmitter),
	alignof(FVFXPlanEmitter),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXPlanEmitter()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlanEmitter.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXPlanEmitter.InnerSingleton, Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXPlanEmitter.InnerSingleton);
}
// ********** End ScriptStruct FVFXPlanEmitter *****************************************************

// ********** Begin ScriptStruct FVFXPlanEvent *****************************************************
struct Z_Construct_UScriptStruct_FVFXPlanEvent_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXPlanEvent); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXPlanEvent); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Source_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Event_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Handler_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXPlanEvent constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Source;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Event;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Target;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Handler;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXPlanEvent constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXPlanEvent>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXPlanEvent_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXPlanEvent;
class UScriptStruct* FVFXPlanEvent::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlanEvent.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXPlanEvent.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXPlanEvent, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXPlanEvent"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXPlanEvent.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXPlanEvent Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Source = { "Source", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanEvent, Source), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Source_MetaData), NewProp_Source_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanEvent, Event), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Event_MetaData), NewProp_Event_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanEvent, Target), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Target_MetaData), NewProp_Target_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Handler = { "Handler", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanEvent, Handler), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Handler_MetaData), NewProp_Handler_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Source,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Event,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewProp_Handler,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXPlanEvent Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXPlanEvent",
	Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::PropPointers),
	sizeof(FVFXPlanEvent),
	alignof(FVFXPlanEvent),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXPlanEvent()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlanEvent.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXPlanEvent.InnerSingleton, Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXPlanEvent.InnerSingleton);
}
// ********** End ScriptStruct FVFXPlanEvent *******************************************************

// ********** Begin ScriptStruct FVFXPlanLayer *****************************************************
struct Z_Construct_UScriptStruct_FVFXPlanLayer_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXPlanLayer); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXPlanLayer); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchetypeTag_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Emitters_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Events_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXPlanLayer constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ArchetypeTag;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Emitters_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Emitters;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Events_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Events;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXPlanLayer constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXPlanLayer>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXPlanLayer_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXPlanLayer;
class UScriptStruct* FVFXPlanLayer::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlanLayer.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXPlanLayer.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXPlanLayer, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXPlanLayer"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXPlanLayer.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXPlanLayer Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanLayer, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_ArchetypeTag = { "ArchetypeTag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanLayer, ArchetypeTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchetypeTag_MetaData), NewProp_ArchetypeTag_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Emitters_Inner = { "Emitters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXPlanEmitter, METADATA_PARAMS(0, nullptr) }; // 2960332940
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Emitters = { "Emitters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanLayer, Emitters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Emitters_MetaData), NewProp_Emitters_MetaData) }; // 2960332940
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Events_Inner = { "Events", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXPlanEvent, METADATA_PARAMS(0, nullptr) }; // 2154839487
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Events = { "Events", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlanLayer, Events), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Events_MetaData), NewProp_Events_MetaData) }; // 2154839487
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_ArchetypeTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Emitters_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Emitters,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Events_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewProp_Events,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXPlanLayer Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXPlanLayer",
	Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::PropPointers),
	sizeof(FVFXPlanLayer),
	alignof(FVFXPlanLayer),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXPlanLayer()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlanLayer.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXPlanLayer.InnerSingleton, Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXPlanLayer.InnerSingleton);
}
// ********** End ScriptStruct FVFXPlanLayer *******************************************************

// ********** Begin ScriptStruct FVFXPlan **********************************************************
struct Z_Construct_UScriptStruct_FVFXPlan_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXPlan); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXPlan); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Style_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Layers_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXPlan constinit property declarations **************************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Version;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Style;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Layers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Layers;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXPlan constinit property declarations ****************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXPlan>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXPlan_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXPlan;
class UScriptStruct* FVFXPlan::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlan.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXPlan.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXPlan, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXPlan"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXPlan.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXPlan Property Definitions *************************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlan, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Style = { "Style", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlan, Style), Z_Construct_UScriptStruct_FVFXStyleSpec, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Style_MetaData), NewProp_Style_MetaData) }; // 634299043
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Layers_Inner = { "Layers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXPlanLayer, METADATA_PARAMS(0, nullptr) }; // 67782414
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Layers = { "Layers", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPlan, Layers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Layers_MetaData), NewProp_Layers_MetaData) }; // 67782414
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXPlan_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Version,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Style,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Layers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPlan_Statics::NewProp_Layers,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlan_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXPlan Property Definitions ***************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXPlan_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXPlan",
	Z_Construct_UScriptStruct_FVFXPlan_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlan_Statics::PropPointers),
	sizeof(FVFXPlan),
	alignof(FVFXPlan),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPlan_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXPlan_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXPlan()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPlan.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXPlan.InnerSingleton, Z_Construct_UScriptStruct_FVFXPlan_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXPlan.InnerSingleton);
}
// ********** End ScriptStruct FVFXPlan ************************************************************

// ********** Begin Enum EVFXActionType ************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXActionType;
static UEnum* EVFXActionType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXActionType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXActionType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXActionType, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXActionType"));
	}
	return Z_Registration_Info_UEnum_EVFXActionType.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXActionType>()
{
	return EVFXActionType_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "AddEmitterFromTemplate.Name", "EVFXActionType::AddEmitterFromTemplate" },
		{ "AddModule.Name", "EVFXActionType::AddModule" },
		{ "AssignRendererMaterial.Name", "EVFXActionType::AssignRendererMaterial" },
		{ "BindEventHandler.Name", "EVFXActionType::BindEventHandler" },
		{ "BlueprintType", "true" },
		{ "CompileAndValidate.Name", "EVFXActionType::CompileAndValidate" },
		{ "CreateMaterialInstance.Name", "EVFXActionType::CreateMaterialInstance" },
		{ "CreateSystem.Name", "EVFXActionType::CreateSystem" },
		{ "EnableDrag.Name", "EVFXActionType::EnableDrag" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
		{ "RenderThumbnail.Name", "EVFXActionType::RenderThumbnail" },
		{ "SetParameter.Name", "EVFXActionType::SetParameter" },
		{ "Unknown.Name", "EVFXActionType::Unknown" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXActionType::CreateSystem", (int64)EVFXActionType::CreateSystem },
		{ "EVFXActionType::AddEmitterFromTemplate", (int64)EVFXActionType::AddEmitterFromTemplate },
		{ "EVFXActionType::AddModule", (int64)EVFXActionType::AddModule },
		{ "EVFXActionType::SetParameter", (int64)EVFXActionType::SetParameter },
		{ "EVFXActionType::BindEventHandler", (int64)EVFXActionType::BindEventHandler },
		{ "EVFXActionType::EnableDrag", (int64)EVFXActionType::EnableDrag },
		{ "EVFXActionType::CreateMaterialInstance", (int64)EVFXActionType::CreateMaterialInstance },
		{ "EVFXActionType::AssignRendererMaterial", (int64)EVFXActionType::AssignRendererMaterial },
		{ "EVFXActionType::CompileAndValidate", (int64)EVFXActionType::CompileAndValidate },
		{ "EVFXActionType::RenderThumbnail", (int64)EVFXActionType::RenderThumbnail },
		{ "EVFXActionType::Unknown", (int64)EVFXActionType::Unknown },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXActionType",
	"EVFXActionType",
	Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXActionType()
{
	if (!Z_Registration_Info_UEnum_EVFXActionType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXActionType.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXActionType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXActionType.InnerSingleton;
}
// ********** End Enum EVFXActionType **************************************************************

// ********** Begin Enum EVFXValueType *************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXValueType;
static UEnum* EVFXValueType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXValueType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXValueType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXValueType, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXValueType"));
	}
	return Z_Registration_Info_UEnum_EVFXValueType.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXValueType>()
{
	return EVFXValueType_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Bool.Name", "EVFXValueType::Bool" },
		{ "Color.Name", "EVFXValueType::Color" },
		{ "Curve.Name", "EVFXValueType::Curve" },
		{ "Float.Name", "EVFXValueType::Float" },
		{ "Int.Name", "EVFXValueType::Int" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
		{ "None.Name", "EVFXValueType::None" },
		{ "Vec2.Name", "EVFXValueType::Vec2" },
		{ "Vec3.Name", "EVFXValueType::Vec3" },
		{ "Vec4.Name", "EVFXValueType::Vec4" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXValueType::None", (int64)EVFXValueType::None },
		{ "EVFXValueType::Float", (int64)EVFXValueType::Float },
		{ "EVFXValueType::Int", (int64)EVFXValueType::Int },
		{ "EVFXValueType::Bool", (int64)EVFXValueType::Bool },
		{ "EVFXValueType::Vec2", (int64)EVFXValueType::Vec2 },
		{ "EVFXValueType::Vec3", (int64)EVFXValueType::Vec3 },
		{ "EVFXValueType::Vec4", (int64)EVFXValueType::Vec4 },
		{ "EVFXValueType::Color", (int64)EVFXValueType::Color },
		{ "EVFXValueType::Curve", (int64)EVFXValueType::Curve },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXValueType",
	"EVFXValueType",
	Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXValueType()
{
	if (!Z_Registration_Info_UEnum_EVFXValueType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXValueType.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXValueType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXValueType.InnerSingleton;
}
// ********** End Enum EVFXValueType ***************************************************************

// ********** Begin ScriptStruct FVFXCurvePoint ****************************************************
struct Z_Construct_UScriptStruct_FVFXCurvePoint_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXCurvePoint); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXCurvePoint); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArriveTangent_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LeaveTangent_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXCurvePoint constinit property declarations ********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ArriveTangent;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LeaveTangent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXCurvePoint constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXCurvePoint>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXCurvePoint_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXCurvePoint;
class UScriptStruct* FVFXCurvePoint::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXCurvePoint.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXCurvePoint.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXCurvePoint, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXCurvePoint"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXCurvePoint.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXCurvePoint Property Definitions *******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurvePoint, Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Time_MetaData), NewProp_Time_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurvePoint, Value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_ArriveTangent = { "ArriveTangent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurvePoint, ArriveTangent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArriveTangent_MetaData), NewProp_ArriveTangent_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_LeaveTangent = { "LeaveTangent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurvePoint, LeaveTangent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LeaveTangent_MetaData), NewProp_LeaveTangent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_ArriveTangent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewProp_LeaveTangent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXCurvePoint Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXCurvePoint",
	Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::PropPointers),
	sizeof(FVFXCurvePoint),
	alignof(FVFXCurvePoint),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXCurvePoint()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXCurvePoint.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXCurvePoint.InnerSingleton, Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXCurvePoint.InnerSingleton);
}
// ********** End ScriptStruct FVFXCurvePoint ******************************************************

// ********** Begin ScriptStruct FVFXActionValue ***************************************************
struct Z_Construct_UScriptStruct_FVFXActionValue_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXActionValue); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXActionValue); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FloatValue_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_IntValue_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoolValue_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vec2_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vec3_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Vec4_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Curve_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RawJson_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXActionValue constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FloatValue;
	static const UECodeGen_Private::FIntPropertyParams NewProp_IntValue;
	static void NewProp_BoolValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_BoolValue;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Vec2;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Vec3;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Vec4;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Curve_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Curve;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RawJson;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXActionValue constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXActionValue>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXActionValue_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXActionValue;
class UScriptStruct* FVFXActionValue::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXActionValue.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXActionValue.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXActionValue, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXActionValue"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXActionValue.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXActionValue Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, Type), Z_Construct_UEnum_VFXAgentCore_EVFXValueType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 500366059
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_FloatValue = { "FloatValue", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, FloatValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FloatValue_MetaData), NewProp_FloatValue_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_IntValue = { "IntValue", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, IntValue), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_IntValue_MetaData), NewProp_IntValue_MetaData) };
void Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_BoolValue_SetBit(void* Obj)
{
	((FVFXActionValue*)Obj)->BoolValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_BoolValue = { "BoolValue", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXActionValue), &Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_BoolValue_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoolValue_MetaData), NewProp_BoolValue_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Vec2 = { "Vec2", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, Vec2), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vec2_MetaData), NewProp_Vec2_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Vec3 = { "Vec3", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, Vec3), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vec3_MetaData), NewProp_Vec3_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Vec4 = { "Vec4", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, Vec4), Z_Construct_UScriptStruct_FVector4, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Vec4_MetaData), NewProp_Vec4_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Curve_Inner = { "Curve", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXCurvePoint, METADATA_PARAMS(0, nullptr) }; // 1534847902
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Curve = { "Curve", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, Curve), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Curve_MetaData), NewProp_Curve_MetaData) }; // 1534847902
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_RawJson = { "RawJson", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXActionValue, RawJson), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RawJson_MetaData), NewProp_RawJson_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXActionValue_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_FloatValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_IntValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_BoolValue,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Vec2,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Vec3,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Vec4,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Curve_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_Curve,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewProp_RawJson,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXActionValue_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXActionValue Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXActionValue_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXActionValue",
	Z_Construct_UScriptStruct_FVFXActionValue_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXActionValue_Statics::PropPointers),
	sizeof(FVFXActionValue),
	alignof(FVFXActionValue),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXActionValue_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXActionValue_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXActionValue()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXActionValue.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXActionValue.InnerSingleton, Z_Construct_UScriptStruct_FVFXActionValue_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXActionValue.InnerSingleton);
}
// ********** End ScriptStruct FVFXActionValue *****************************************************

// ********** Begin ScriptStruct FVFXAction ********************************************************
struct Z_Construct_UScriptStruct_FVFXAction_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXAction); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXAction); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_System_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Path_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Template_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Alias_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Target_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParamName_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Module_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Stack_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Event_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Handler_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DragCoef_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InheritVel_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Parent_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Out_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Material_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Params_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraPreset_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXAction constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static const UECodeGen_Private::FStrPropertyParams NewProp_System;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Path;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Template;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Alias;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Target;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ParamName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Value;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Module;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Stack;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Event;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Handler;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DragCoef;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InheritVel;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Parent;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Out;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Material;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Params_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Params_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Params;
	static const UECodeGen_Private::FStrPropertyParams NewProp_CameraPreset;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXAction constinit property declarations **************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXAction>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXAction_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXAction;
class UScriptStruct* FVFXAction::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXAction.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXAction.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXAction, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXAction"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXAction.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXAction Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Type), Z_Construct_UEnum_VFXAgentCore_EVFXActionType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 1325220185
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_System = { "System", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, System), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_System_MetaData), NewProp_System_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Path = { "Path", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Path), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Path_MetaData), NewProp_Path_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Template = { "Template", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Template), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Template_MetaData), NewProp_Template_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Alias = { "Alias", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Alias), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Alias_MetaData), NewProp_Alias_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Target = { "Target", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Target), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Target_MetaData), NewProp_Target_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_ParamName = { "ParamName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, ParamName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParamName_MetaData), NewProp_ParamName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Value), Z_Construct_UScriptStruct_FVFXActionValue, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) }; // 2645122040
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Module = { "Module", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Module), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Module_MetaData), NewProp_Module_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Stack = { "Stack", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Stack), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Stack_MetaData), NewProp_Stack_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Event = { "Event", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Event), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Event_MetaData), NewProp_Event_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Handler = { "Handler", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Handler), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Handler_MetaData), NewProp_Handler_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_DragCoef = { "DragCoef", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, DragCoef), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DragCoef_MetaData), NewProp_DragCoef_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_InheritVel = { "InheritVel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, InheritVel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InheritVel_MetaData), NewProp_InheritVel_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Parent = { "Parent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Parent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Parent_MetaData), NewProp_Parent_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Out = { "Out", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Out), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Out_MetaData), NewProp_Out_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Material), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Material_MetaData), NewProp_Material_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Params_ValueProp = { "Params", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FVFXActionValue, METADATA_PARAMS(0, nullptr) }; // 2645122040
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Params_Key_KeyProp = { "Params_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Params = { "Params", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, Params), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Params_MetaData), NewProp_Params_MetaData) }; // 2645122040
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_CameraPreset = { "CameraPreset", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXAction, CameraPreset), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraPreset_MetaData), NewProp_CameraPreset_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXAction_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_System,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Path,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Template,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Alias,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Target,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_ParamName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Value,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Module,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Stack,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Event,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Handler,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_DragCoef,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_InheritVel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Parent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Out,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Params_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Params_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_Params,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXAction_Statics::NewProp_CameraPreset,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXAction_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXAction Property Definitions *************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXAction_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXAction",
	Z_Construct_UScriptStruct_FVFXAction_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXAction_Statics::PropPointers),
	sizeof(FVFXAction),
	alignof(FVFXAction),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXAction_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXAction_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXAction()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXAction.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXAction.InnerSingleton, Z_Construct_UScriptStruct_FVFXAction_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXAction.InnerSingleton);
}
// ********** End ScriptStruct FVFXAction **********************************************************

// ********** Begin ScriptStruct FVFXValidationTargets *********************************************
struct Z_Construct_UScriptStruct_FVFXValidationTargets_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXValidationTargets); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXValidationTargets); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsMin_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsMax_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ParticleCountRange_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXValidationTargets constinit property declarations *************
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundsMin;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BoundsMax;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ParticleCountRange;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXValidationTargets constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXValidationTargets>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXValidationTargets_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXValidationTargets;
class UScriptStruct* FVFXValidationTargets::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXValidationTargets.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXValidationTargets.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXValidationTargets, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXValidationTargets"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXValidationTargets.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXValidationTargets Property Definitions ************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::NewProp_BoundsMin = { "BoundsMin", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXValidationTargets, BoundsMin), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsMin_MetaData), NewProp_BoundsMin_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::NewProp_BoundsMax = { "BoundsMax", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXValidationTargets, BoundsMax), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsMax_MetaData), NewProp_BoundsMax_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::NewProp_ParticleCountRange = { "ParticleCountRange", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXValidationTargets, ParticleCountRange), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ParticleCountRange_MetaData), NewProp_ParticleCountRange_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::NewProp_BoundsMin,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::NewProp_BoundsMax,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::NewProp_ParticleCountRange,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXValidationTargets Property Definitions **************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXValidationTargets",
	Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::PropPointers),
	sizeof(FVFXValidationTargets),
	alignof(FVFXValidationTargets),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXValidationTargets()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXValidationTargets.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXValidationTargets.InnerSingleton, Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXValidationTargets.InnerSingleton);
}
// ********** End ScriptStruct FVFXValidationTargets ***********************************************

// ********** Begin ScriptStruct FVFXDirectorPlan **************************************************
struct Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXDirectorPlan); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXDirectorPlan); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Plan_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Actions_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Validation_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RawJson_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXDirectorPlan constinit property declarations ******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Plan;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Actions_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Actions;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Validation;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RawJson;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXDirectorPlan constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXDirectorPlan>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXDirectorPlan;
class UScriptStruct* FVFXDirectorPlan::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXDirectorPlan.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXDirectorPlan.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXDirectorPlan, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXDirectorPlan"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXDirectorPlan.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXDirectorPlan Property Definitions *****************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Plan = { "Plan", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXDirectorPlan, Plan), Z_Construct_UScriptStruct_FVFXPlan, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Plan_MetaData), NewProp_Plan_MetaData) }; // 1110994003
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Actions_Inner = { "Actions", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXAction, METADATA_PARAMS(0, nullptr) }; // 1433613801
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Actions = { "Actions", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXDirectorPlan, Actions), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Actions_MetaData), NewProp_Actions_MetaData) }; // 1433613801
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Validation = { "Validation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXDirectorPlan, Validation), Z_Construct_UScriptStruct_FVFXValidationTargets, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Validation_MetaData), NewProp_Validation_MetaData) }; // 2969517886
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_RawJson = { "RawJson", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXDirectorPlan, RawJson), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RawJson_MetaData), NewProp_RawJson_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Plan,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Actions_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Actions,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_Validation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewProp_RawJson,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXDirectorPlan Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXDirectorPlan",
	Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::PropPointers),
	sizeof(FVFXDirectorPlan),
	alignof(FVFXDirectorPlan),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXDirectorPlan()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXDirectorPlan.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXDirectorPlan.InnerSingleton, Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXDirectorPlan.InnerSingleton);
}
// ********** End ScriptStruct FVFXDirectorPlan ****************************************************

// ********** Begin ScriptStruct FVFXExecutionReport ***********************************************
struct Z_Construct_UScriptStruct_FVFXExecutionReport_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXExecutionReport); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXExecutionReport); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSuccess_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Logs_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Warnings_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Errors_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GeneratedAssets_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ThumbnailPath_MetaData[] = {
		{ "Category", "VFXAgent|Director" },
		{ "ModuleRelativePath", "Public/VFXDirectorTypes.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXExecutionReport constinit property declarations ***************
	static void NewProp_bSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Logs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Logs;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Warnings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Warnings;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Errors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Errors;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GeneratedAssets_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_GeneratedAssets;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ThumbnailPath;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXExecutionReport constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXExecutionReport>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXExecutionReport_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXExecutionReport;
class UScriptStruct* FVFXExecutionReport::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXExecutionReport.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXExecutionReport.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXExecutionReport, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXExecutionReport"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXExecutionReport.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXExecutionReport Property Definitions **************************
void Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_bSuccess_SetBit(void* Obj)
{
	((FVFXExecutionReport*)Obj)->bSuccess = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXExecutionReport), &Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSuccess_MetaData), NewProp_bSuccess_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Logs_Inner = { "Logs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Logs = { "Logs", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXExecutionReport, Logs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Logs_MetaData), NewProp_Logs_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Warnings_Inner = { "Warnings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Warnings = { "Warnings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXExecutionReport, Warnings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Warnings_MetaData), NewProp_Warnings_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Errors_Inner = { "Errors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Errors = { "Errors", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXExecutionReport, Errors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Errors_MetaData), NewProp_Errors_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_GeneratedAssets_Inner = { "GeneratedAssets", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_GeneratedAssets = { "GeneratedAssets", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXExecutionReport, GeneratedAssets), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GeneratedAssets_MetaData), NewProp_GeneratedAssets_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_ThumbnailPath = { "ThumbnailPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXExecutionReport, ThumbnailPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ThumbnailPath_MetaData), NewProp_ThumbnailPath_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_bSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Logs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Logs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Warnings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Warnings,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Errors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_Errors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_GeneratedAssets_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_GeneratedAssets,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewProp_ThumbnailPath,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXExecutionReport Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXExecutionReport",
	Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::PropPointers),
	sizeof(FVFXExecutionReport),
	alignof(FVFXExecutionReport),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXExecutionReport()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXExecutionReport.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXExecutionReport.InnerSingleton, Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXExecutionReport.InnerSingleton);
}
// ********** End ScriptStruct FVFXExecutionReport *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h__Script_VFXAgentCore_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EVFXActionType_StaticEnum, TEXT("EVFXActionType"), &Z_Registration_Info_UEnum_EVFXActionType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1325220185U) },
		{ EVFXValueType_StaticEnum, TEXT("EVFXValueType"), &Z_Registration_Info_UEnum_EVFXValueType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 500366059U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FVFXColorTheme::StaticStruct, Z_Construct_UScriptStruct_FVFXColorTheme_Statics::NewStructOps, TEXT("VFXColorTheme"),&Z_Registration_Info_UScriptStruct_FVFXColorTheme, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXColorTheme), 1370816070U) },
		{ FVFXStyleSpec::StaticStruct, Z_Construct_UScriptStruct_FVFXStyleSpec_Statics::NewStructOps, TEXT("VFXStyleSpec"),&Z_Registration_Info_UScriptStruct_FVFXStyleSpec, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXStyleSpec), 634299043U) },
		{ FVFXPlanEmitter::StaticStruct, Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics::NewStructOps, TEXT("VFXPlanEmitter"),&Z_Registration_Info_UScriptStruct_FVFXPlanEmitter, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXPlanEmitter), 2960332940U) },
		{ FVFXPlanEvent::StaticStruct, Z_Construct_UScriptStruct_FVFXPlanEvent_Statics::NewStructOps, TEXT("VFXPlanEvent"),&Z_Registration_Info_UScriptStruct_FVFXPlanEvent, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXPlanEvent), 2154839487U) },
		{ FVFXPlanLayer::StaticStruct, Z_Construct_UScriptStruct_FVFXPlanLayer_Statics::NewStructOps, TEXT("VFXPlanLayer"),&Z_Registration_Info_UScriptStruct_FVFXPlanLayer, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXPlanLayer), 67782414U) },
		{ FVFXPlan::StaticStruct, Z_Construct_UScriptStruct_FVFXPlan_Statics::NewStructOps, TEXT("VFXPlan"),&Z_Registration_Info_UScriptStruct_FVFXPlan, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXPlan), 1110994003U) },
		{ FVFXCurvePoint::StaticStruct, Z_Construct_UScriptStruct_FVFXCurvePoint_Statics::NewStructOps, TEXT("VFXCurvePoint"),&Z_Registration_Info_UScriptStruct_FVFXCurvePoint, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXCurvePoint), 1534847902U) },
		{ FVFXActionValue::StaticStruct, Z_Construct_UScriptStruct_FVFXActionValue_Statics::NewStructOps, TEXT("VFXActionValue"),&Z_Registration_Info_UScriptStruct_FVFXActionValue, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXActionValue), 2645122040U) },
		{ FVFXAction::StaticStruct, Z_Construct_UScriptStruct_FVFXAction_Statics::NewStructOps, TEXT("VFXAction"),&Z_Registration_Info_UScriptStruct_FVFXAction, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXAction), 1433613801U) },
		{ FVFXValidationTargets::StaticStruct, Z_Construct_UScriptStruct_FVFXValidationTargets_Statics::NewStructOps, TEXT("VFXValidationTargets"),&Z_Registration_Info_UScriptStruct_FVFXValidationTargets, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXValidationTargets), 2969517886U) },
		{ FVFXDirectorPlan::StaticStruct, Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics::NewStructOps, TEXT("VFXDirectorPlan"),&Z_Registration_Info_UScriptStruct_FVFXDirectorPlan, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXDirectorPlan), 3362562632U) },
		{ FVFXExecutionReport::StaticStruct, Z_Construct_UScriptStruct_FVFXExecutionReport_Statics::NewStructOps, TEXT("VFXExecutionReport"),&Z_Registration_Info_UScriptStruct_FVFXExecutionReport, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXExecutionReport), 1667360187U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h__Script_VFXAgentCore_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h__Script_VFXAgentCore_4245640236{
	TEXT("/Script/VFXAgentCore"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h__Script_VFXAgentCore_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h__Script_VFXAgentCore_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h__Script_VFXAgentCore_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h__Script_VFXAgentCore_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
