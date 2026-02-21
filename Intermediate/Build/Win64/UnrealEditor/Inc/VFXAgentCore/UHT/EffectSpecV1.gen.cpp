// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EffectSpecV1.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEffectSpecV1() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2f();
UPackage* Z_Construct_UPackage__Script_VFXAgentCore();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FEffectSpecV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FEffectStyleV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FExternalAssetsV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerInitSpecV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerSpawnSpecV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerSpecV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerUpdateSpecV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLCustom();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLInput();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLOutputs();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLTextureInput();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialSpecV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FModelRequestV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMotionSpecV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FQualityBudgetV1();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FTextureRequestV1();
// ********** End Cross Module References **********************************************************

// ********** Begin ScriptStruct FMaterialHLSLInput ************************************************
struct Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMaterialHLSLInput); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMaterialHLSLInput); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Default_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Min_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Max_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMaterialHLSLInput constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Type;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Default;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Min;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Max;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMaterialHLSLInput constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLInput>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMaterialHLSLInput;
class UScriptStruct* FMaterialHLSLInput::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLInput.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMaterialHLSLInput.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLInput, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLInput"));
	}
	return Z_Registration_Info_UScriptStruct_FMaterialHLSLInput.OuterSingleton;
	}

// ********** Begin ScriptStruct FMaterialHLSLInput Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLInput, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLInput, Type), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Default = { "Default", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLInput, Default), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Default_MetaData), NewProp_Default_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Min = { "Min", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLInput, Min), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Min_MetaData), NewProp_Min_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Max = { "Max", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLInput, Max), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Max_MetaData), NewProp_Max_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Default,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Min,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewProp_Max,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMaterialHLSLInput Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MaterialHLSLInput",
	Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::PropPointers),
	sizeof(FMaterialHLSLInput),
	alignof(FMaterialHLSLInput),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLInput()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLInput.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMaterialHLSLInput.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMaterialHLSLInput.InnerSingleton);
}
// ********** End ScriptStruct FMaterialHLSLInput **************************************************

// ********** Begin ScriptStruct FMaterialHLSLTextureInput *****************************************
struct Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMaterialHLSLTextureInput); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMaterialHLSLTextureInput); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Usage_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMaterialHLSLTextureInput constinit property declarations *********
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Usage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMaterialHLSLTextureInput constinit property declarations ***********
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLTextureInput>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput;
class UScriptStruct* FMaterialHLSLTextureInput::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLTextureInput, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLTextureInput"));
	}
	return Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput.OuterSingleton;
	}

// ********** Begin ScriptStruct FMaterialHLSLTextureInput Property Definitions ********************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLTextureInput, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Usage = { "Usage", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLTextureInput, Usage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Usage_MetaData), NewProp_Usage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Usage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMaterialHLSLTextureInput Property Definitions **********************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MaterialHLSLTextureInput",
	Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::PropPointers),
	sizeof(FMaterialHLSLTextureInput),
	alignof(FMaterialHLSLTextureInput),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLTextureInput()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput.InnerSingleton);
}
// ********** End ScriptStruct FMaterialHLSLTextureInput *******************************************

// ********** Begin ScriptStruct FMaterialHLSLOutputs **********************************************
struct Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMaterialHLSLOutputs); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMaterialHLSLOutputs); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_emissive_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_opacity_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_distortion_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMaterialHLSLOutputs constinit property declarations **************
	static void NewProp_emissive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_emissive;
	static void NewProp_opacity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_opacity;
	static void NewProp_distortion_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_distortion;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMaterialHLSLOutputs constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLOutputs>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs;
class UScriptStruct* FMaterialHLSLOutputs::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLOutputs, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLOutputs"));
	}
	return Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs.OuterSingleton;
	}

// ********** Begin ScriptStruct FMaterialHLSLOutputs Property Definitions *************************
void Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_emissive_SetBit(void* Obj)
{
	((FMaterialHLSLOutputs*)Obj)->emissive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_emissive = { "emissive", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialHLSLOutputs), &Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_emissive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_emissive_MetaData), NewProp_emissive_MetaData) };
void Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_opacity_SetBit(void* Obj)
{
	((FMaterialHLSLOutputs*)Obj)->opacity = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_opacity = { "opacity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialHLSLOutputs), &Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_opacity_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_opacity_MetaData), NewProp_opacity_MetaData) };
void Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_distortion_SetBit(void* Obj)
{
	((FMaterialHLSLOutputs*)Obj)->distortion = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_distortion = { "distortion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialHLSLOutputs), &Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_distortion_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_distortion_MetaData), NewProp_distortion_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_emissive,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_opacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewProp_distortion,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMaterialHLSLOutputs Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MaterialHLSLOutputs",
	Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::PropPointers),
	sizeof(FMaterialHLSLOutputs),
	alignof(FMaterialHLSLOutputs),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLOutputs()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs.InnerSingleton);
}
// ********** End ScriptStruct FMaterialHLSLOutputs ************************************************

// ********** Begin ScriptStruct FMaterialHLSLCustom ***********************************************
struct Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMaterialHLSLCustom); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMaterialHLSLCustom); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Enabled_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Code_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Inputs_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextureInputs_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Outputs_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Contract_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMaterialHLSLCustom constinit property declarations ***************
	static void NewProp_Enabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_Enabled;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Code;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Inputs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Inputs;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TextureInputs_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TextureInputs;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Outputs;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Contract;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMaterialHLSLCustom constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLCustom>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom;
class UScriptStruct* FMaterialHLSLCustom::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLCustom, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLCustom"));
	}
	return Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom.OuterSingleton;
	}

// ********** Begin ScriptStruct FMaterialHLSLCustom Property Definitions **************************
void Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Enabled_SetBit(void* Obj)
{
	((FMaterialHLSLCustom*)Obj)->Enabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Enabled = { "Enabled", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialHLSLCustom), &Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Enabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Enabled_MetaData), NewProp_Enabled_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Code = { "Code", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, Code), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Code_MetaData), NewProp_Code_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Inputs_Inner = { "Inputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMaterialHLSLInput, METADATA_PARAMS(0, nullptr) }; // 3243923542
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Inputs = { "Inputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, Inputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Inputs_MetaData), NewProp_Inputs_MetaData) }; // 3243923542
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_TextureInputs_Inner = { "TextureInputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMaterialHLSLTextureInput, METADATA_PARAMS(0, nullptr) }; // 4226001081
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_TextureInputs = { "TextureInputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, TextureInputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextureInputs_MetaData), NewProp_TextureInputs_MetaData) }; // 4226001081
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Outputs = { "Outputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, Outputs), Z_Construct_UScriptStruct_FMaterialHLSLOutputs, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Outputs_MetaData), NewProp_Outputs_MetaData) }; // 603146422
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Contract = { "Contract", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, Contract), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Contract_MetaData), NewProp_Contract_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Enabled,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Code,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Inputs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Inputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_TextureInputs_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_TextureInputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Outputs,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Contract,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMaterialHLSLCustom Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MaterialHLSLCustom",
	Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::PropPointers),
	sizeof(FMaterialHLSLCustom),
	alignof(FMaterialHLSLCustom),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMaterialHLSLCustom()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom.InnerSingleton);
}
// ********** End ScriptStruct FMaterialHLSLCustom *************************************************

// ********** Begin ScriptStruct FMaterialSpecV1 ***************************************************
struct Z_Construct_UScriptStruct_FMaterialSpecV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMaterialSpecV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMaterialSpecV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Shading_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Blend_MetaData[] = {
		{ "Comment", "// unlit|lit\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
		{ "ToolTip", "unlit|lit" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Features_MetaData[] = {
		{ "Comment", "// additive|translucent|masked|opaque\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
		{ "ToolTip", "additive|translucent|masked|opaque" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ScalarParams_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VectorParams_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextureSlots_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HLSLCustom_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMaterialSpecV1 constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Shading;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Blend;
	static const UECodeGen_Private::FBoolPropertyParams NewProp_Features_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Features_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Features;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ScalarParams_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ScalarParams_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_ScalarParams;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VectorParams_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_VectorParams_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_VectorParams;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TextureSlots_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TextureSlots_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_TextureSlots;
	static const UECodeGen_Private::FStructPropertyParams NewProp_HLSLCustom;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMaterialSpecV1 constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMaterialSpecV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMaterialSpecV1;
class UScriptStruct* FMaterialSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMaterialSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_FMaterialSpecV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FMaterialSpecV1 Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Shading = { "Shading", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, Shading), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Shading_MetaData), NewProp_Shading_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Blend = { "Blend", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, Blend), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Blend_MetaData), NewProp_Blend_MetaData) };
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Features_ValueProp = { "Features", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Features_Key_KeyProp = { "Features_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Features = { "Features", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, Features), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Features_MetaData), NewProp_Features_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_ScalarParams_ValueProp = { "ScalarParams", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_ScalarParams_Key_KeyProp = { "ScalarParams_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_ScalarParams = { "ScalarParams", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, ScalarParams), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ScalarParams_MetaData), NewProp_ScalarParams_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_VectorParams_ValueProp = { "VectorParams", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_VectorParams_Key_KeyProp = { "VectorParams_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_VectorParams = { "VectorParams", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, VectorParams), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VectorParams_MetaData), NewProp_VectorParams_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_TextureSlots_ValueProp = { "TextureSlots", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_TextureSlots_Key_KeyProp = { "TextureSlots_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_TextureSlots = { "TextureSlots", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, TextureSlots), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextureSlots_MetaData), NewProp_TextureSlots_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_HLSLCustom = { "HLSLCustom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, HLSLCustom), Z_Construct_UScriptStruct_FMaterialHLSLCustom, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HLSLCustom_MetaData), NewProp_HLSLCustom_MetaData) }; // 1922422627
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Shading,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Blend,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Features_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Features_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_Features,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_ScalarParams_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_ScalarParams_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_ScalarParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_VectorParams_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_VectorParams_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_VectorParams,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_TextureSlots_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_TextureSlots_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_TextureSlots,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_HLSLCustom,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMaterialSpecV1 Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MaterialSpecV1",
	Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::PropPointers),
	sizeof(FMaterialSpecV1),
	alignof(FMaterialSpecV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMaterialSpecV1()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMaterialSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMaterialSpecV1.InnerSingleton);
}
// ********** End ScriptStruct FMaterialSpecV1 *****************************************************

// ********** Begin ScriptStruct FLayerSpawnSpecV1 *************************************************
struct Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerSpawnSpecV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerSpawnSpecV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mode_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rate_MetaData[] = {
		{ "Comment", "// rate|burst\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
		{ "ToolTip", "rate|burst" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Duration_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerSpawnSpecV1 constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Mode;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BurstCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Duration;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerSpawnSpecV1 constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerSpawnSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1;
class UScriptStruct* FLayerSpawnSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerSpawnSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerSpawnSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerSpawnSpecV1 Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_Mode = { "Mode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpawnSpecV1, Mode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mode_MetaData), NewProp_Mode_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_Rate = { "Rate", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpawnSpecV1, Rate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rate_MetaData), NewProp_Rate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_BurstCount = { "BurstCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpawnSpecV1, BurstCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstCount_MetaData), NewProp_BurstCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_Duration = { "Duration", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpawnSpecV1, Duration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Duration_MetaData), NewProp_Duration_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_Mode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_Rate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_BurstCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewProp_Duration,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerSpawnSpecV1 Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerSpawnSpecV1",
	Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::PropPointers),
	sizeof(FLayerSpawnSpecV1),
	alignof(FLayerSpawnSpecV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerSpawnSpecV1()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1.InnerSingleton);
}
// ********** End ScriptStruct FLayerSpawnSpecV1 ***************************************************

// ********** Begin ScriptStruct FLayerInitSpecV1 **************************************************
struct Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerInitSpecV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerInitSpecV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeRange_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DirectionMode_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerInitSpecV1 constinit property declarations ******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SizeRange;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DirectionMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerInitSpecV1 constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerInitSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerInitSpecV1;
class UScriptStruct* FLayerInitSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerInitSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerInitSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerInitSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerInitSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerInitSpecV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerInitSpecV1 Property Definitions *****************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitSpecV1, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_SizeRange = { "SizeRange", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitSpecV1, SizeRange), Z_Construct_UScriptStruct_FVector2f, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeRange_MetaData), NewProp_SizeRange_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitSpecV1, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_DirectionMode = { "DirectionMode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitSpecV1, DirectionMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DirectionMode_MetaData), NewProp_DirectionMode_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_Lifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_SizeRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewProp_DirectionMode,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerInitSpecV1 Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerInitSpecV1",
	Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::PropPointers),
	sizeof(FLayerInitSpecV1),
	alignof(FLayerInitSpecV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerInitSpecV1()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerInitSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerInitSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerInitSpecV1.InnerSingleton);
}
// ********** End ScriptStruct FLayerInitSpecV1 ****************************************************

// ********** Begin ScriptStruct FLayerUpdateSpecV1 ************************************************
struct Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerUpdateSpecV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerUpdateSpecV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Drag_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurlNoiseStrength_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorOverLife_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlphaOverLife_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerUpdateSpecV1 constinit property declarations ****************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Drag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurlNoiseStrength;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ColorOverLife;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AlphaOverLife;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerUpdateSpecV1 constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerUpdateSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1;
class UScriptStruct* FLayerUpdateSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerUpdateSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerUpdateSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerUpdateSpecV1 Property Definitions ***************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_Drag = { "Drag", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateSpecV1, Drag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Drag_MetaData), NewProp_Drag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_CurlNoiseStrength = { "CurlNoiseStrength", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateSpecV1, CurlNoiseStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurlNoiseStrength_MetaData), NewProp_CurlNoiseStrength_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_ColorOverLife = { "ColorOverLife", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateSpecV1, ColorOverLife), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorOverLife_MetaData), NewProp_ColorOverLife_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_AlphaOverLife = { "AlphaOverLife", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateSpecV1, AlphaOverLife), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlphaOverLife_MetaData), NewProp_AlphaOverLife_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_Drag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_CurlNoiseStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_ColorOverLife,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewProp_AlphaOverLife,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerUpdateSpecV1 Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerUpdateSpecV1",
	Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::PropPointers),
	sizeof(FLayerUpdateSpecV1),
	alignof(FLayerUpdateSpecV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerUpdateSpecV1()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1.InnerSingleton);
}
// ********** End ScriptStruct FLayerUpdateSpecV1 **************************************************

// ********** Begin ScriptStruct FTextureRequestV1 *************************************************
struct Z_Construct_UScriptStruct_FTextureRequestV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTextureRequestV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTextureRequestV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Usage_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Width_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Height_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTextureRequestV1 constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Usage;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Width;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Height;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTextureRequestV1 constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTextureRequestV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTextureRequestV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTextureRequestV1;
class UScriptStruct* FTextureRequestV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTextureRequestV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTextureRequestV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTextureRequestV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("TextureRequestV1"));
	}
	return Z_Registration_Info_UScriptStruct_FTextureRequestV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FTextureRequestV1 Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTextureRequestV1, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Usage = { "Usage", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTextureRequestV1, Usage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Usage_MetaData), NewProp_Usage_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Width = { "Width", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTextureRequestV1, Width), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Width_MetaData), NewProp_Width_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Height = { "Height", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTextureRequestV1, Height), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Height_MetaData), NewProp_Height_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTextureRequestV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Usage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Width,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewProp_Height,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureRequestV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTextureRequestV1 Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTextureRequestV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"TextureRequestV1",
	Z_Construct_UScriptStruct_FTextureRequestV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureRequestV1_Statics::PropPointers),
	sizeof(FTextureRequestV1),
	alignof(FTextureRequestV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTextureRequestV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTextureRequestV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTextureRequestV1()
{
	if (!Z_Registration_Info_UScriptStruct_FTextureRequestV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTextureRequestV1.InnerSingleton, Z_Construct_UScriptStruct_FTextureRequestV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTextureRequestV1.InnerSingleton);
}
// ********** End ScriptStruct FTextureRequestV1 ***************************************************

// ********** Begin ScriptStruct FModelRequestV1 ***************************************************
struct Z_Construct_UScriptStruct_FModelRequestV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FModelRequestV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FModelRequestV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Format_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FModelRequestV1 constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Format;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FModelRequestV1 constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FModelRequestV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FModelRequestV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FModelRequestV1;
class UScriptStruct* FModelRequestV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FModelRequestV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FModelRequestV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FModelRequestV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("ModelRequestV1"));
	}
	return Z_Registration_Info_UScriptStruct_FModelRequestV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FModelRequestV1 Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModelRequestV1, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Format = { "Format", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModelRequestV1, Format), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Format_MetaData), NewProp_Format_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FModelRequestV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Format,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FModelRequestV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FModelRequestV1 Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FModelRequestV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"ModelRequestV1",
	Z_Construct_UScriptStruct_FModelRequestV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FModelRequestV1_Statics::PropPointers),
	sizeof(FModelRequestV1),
	alignof(FModelRequestV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FModelRequestV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FModelRequestV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FModelRequestV1()
{
	if (!Z_Registration_Info_UScriptStruct_FModelRequestV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FModelRequestV1.InnerSingleton, Z_Construct_UScriptStruct_FModelRequestV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FModelRequestV1.InnerSingleton);
}
// ********** End ScriptStruct FModelRequestV1 *****************************************************

// ********** Begin ScriptStruct FMotionSpecV1 *****************************************************
struct Z_Construct_UScriptStruct_FMotionSpecV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMotionSpecV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMotionSpecV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Semantic_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMotionSpecV1 constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Semantic;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMotionSpecV1 constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMotionSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMotionSpecV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMotionSpecV1;
class UScriptStruct* FMotionSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMotionSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMotionSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMotionSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MotionSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_FMotionSpecV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FMotionSpecV1 Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMotionSpecV1_Statics::NewProp_Semantic = { "Semantic", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionSpecV1, Semantic), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Semantic_MetaData), NewProp_Semantic_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMotionSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionSpecV1_Statics::NewProp_Semantic,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMotionSpecV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMotionSpecV1 Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMotionSpecV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MotionSpecV1",
	Z_Construct_UScriptStruct_FMotionSpecV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMotionSpecV1_Statics::PropPointers),
	sizeof(FMotionSpecV1),
	alignof(FMotionSpecV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMotionSpecV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMotionSpecV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMotionSpecV1()
{
	if (!Z_Registration_Info_UScriptStruct_FMotionSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMotionSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FMotionSpecV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMotionSpecV1.InnerSingleton);
}
// ********** End ScriptStruct FMotionSpecV1 *******************************************************

// ********** Begin ScriptStruct FQualityBudgetV1 **************************************************
struct Z_Construct_UScriptStruct_FQualityBudgetV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FQualityBudgetV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FQualityBudgetV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PerfCostHint_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxParticlesHint_MetaData[] = {
		{ "Comment", "// low|mid|high\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
		{ "ToolTip", "low|mid|high" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FQualityBudgetV1 constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_PerfCostHint;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxParticlesHint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FQualityBudgetV1 constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FQualityBudgetV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FQualityBudgetV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FQualityBudgetV1;
class UScriptStruct* FQualityBudgetV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FQualityBudgetV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FQualityBudgetV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FQualityBudgetV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("QualityBudgetV1"));
	}
	return Z_Registration_Info_UScriptStruct_FQualityBudgetV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FQualityBudgetV1 Property Definitions *****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_PerfCostHint = { "PerfCostHint", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FQualityBudgetV1, PerfCostHint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PerfCostHint_MetaData), NewProp_PerfCostHint_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_MaxParticlesHint = { "MaxParticlesHint", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FQualityBudgetV1, MaxParticlesHint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxParticlesHint_MetaData), NewProp_MaxParticlesHint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_PerfCostHint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_MaxParticlesHint,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FQualityBudgetV1 Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"QualityBudgetV1",
	Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::PropPointers),
	sizeof(FQualityBudgetV1),
	alignof(FQualityBudgetV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FQualityBudgetV1()
{
	if (!Z_Registration_Info_UScriptStruct_FQualityBudgetV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FQualityBudgetV1.InnerSingleton, Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FQualityBudgetV1.InnerSingleton);
}
// ********** End ScriptStruct FQualityBudgetV1 ****************************************************

// ********** Begin ScriptStruct FLayerSpecV1 ******************************************************
struct Z_Construct_UScriptStruct_FLayerSpecV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerSpecV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerSpecV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RendererType_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Spawn_MetaData[] = {
		{ "Comment", "// sprite|ribbon|mesh\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
		{ "ToolTip", "sprite|ribbon|mesh" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Init_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Update_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Material_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TexturesNeeded_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ModelNeeded_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Motion_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_QualityBudget_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerSpecV1 constinit property declarations **********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Id;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Role;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Spawn;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Init;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Update;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Material;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TexturesNeeded_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_TexturesNeeded;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ModelNeeded;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Motion;
	static const UECodeGen_Private::FStructPropertyParams NewProp_QualityBudget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerSpecV1 constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerSpecV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerSpecV1;
class UScriptStruct* FLayerSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerSpecV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerSpecV1 Property Definitions *********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Id), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Id_MetaData), NewProp_Id_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Role), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, RendererType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Spawn = { "Spawn", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Spawn), Z_Construct_UScriptStruct_FLayerSpawnSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spawn_MetaData), NewProp_Spawn_MetaData) }; // 4258502672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Init = { "Init", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Init), Z_Construct_UScriptStruct_FLayerInitSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Init_MetaData), NewProp_Init_MetaData) }; // 1872821897
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Update = { "Update", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Update), Z_Construct_UScriptStruct_FLayerUpdateSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Update_MetaData), NewProp_Update_MetaData) }; // 1920722500
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Material), Z_Construct_UScriptStruct_FMaterialSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Material_MetaData), NewProp_Material_MetaData) }; // 1341355002
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_TexturesNeeded_Inner = { "TexturesNeeded", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTextureRequestV1, METADATA_PARAMS(0, nullptr) }; // 2979864525
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_TexturesNeeded = { "TexturesNeeded", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, TexturesNeeded), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TexturesNeeded_MetaData), NewProp_TexturesNeeded_MetaData) }; // 2979864525
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_ModelNeeded = { "ModelNeeded", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, ModelNeeded), Z_Construct_UScriptStruct_FModelRequestV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelNeeded_MetaData), NewProp_ModelNeeded_MetaData) }; // 1079469488
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Motion = { "Motion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Motion), Z_Construct_UScriptStruct_FMotionSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Motion_MetaData), NewProp_Motion_MetaData) }; // 2955677861
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_QualityBudget = { "QualityBudget", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, QualityBudget), Z_Construct_UScriptStruct_FQualityBudgetV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QualityBudget_MetaData), NewProp_QualityBudget_MetaData) }; // 2706606290
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Spawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Init,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Update,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_TexturesNeeded_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_TexturesNeeded,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_ModelNeeded,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Motion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_QualityBudget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpecV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerSpecV1 Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerSpecV1",
	Z_Construct_UScriptStruct_FLayerSpecV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpecV1_Statics::PropPointers),
	sizeof(FLayerSpecV1),
	alignof(FLayerSpecV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpecV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerSpecV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerSpecV1()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerSpecV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerSpecV1.InnerSingleton);
}
// ********** End ScriptStruct FLayerSpecV1 ********************************************************

// ********** Begin ScriptStruct FEffectStyleV1 ****************************************************
struct Z_Construct_UScriptStruct_FEffectStyleV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEffectStyleV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEffectStyleV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Palette_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RealismToAnime_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Brightness_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Contrast_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseStyle_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEffectStyleV1 constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Palette;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RealismToAnime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Brightness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Contrast;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NoiseStyle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEffectStyleV1 constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEffectStyleV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEffectStyleV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEffectStyleV1;
class UScriptStruct* FEffectStyleV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectStyleV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEffectStyleV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEffectStyleV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EffectStyleV1"));
	}
	return Z_Registration_Info_UScriptStruct_FEffectStyleV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FEffectStyleV1 Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_Palette = { "Palette", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV1, Palette), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Palette_MetaData), NewProp_Palette_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_RealismToAnime = { "RealismToAnime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV1, RealismToAnime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RealismToAnime_MetaData), NewProp_RealismToAnime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_Brightness = { "Brightness", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV1, Brightness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Brightness_MetaData), NewProp_Brightness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_Contrast = { "Contrast", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV1, Contrast), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Contrast_MetaData), NewProp_Contrast_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_NoiseStyle = { "NoiseStyle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV1, NoiseStyle), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseStyle_MetaData), NewProp_NoiseStyle_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEffectStyleV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_Palette,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_RealismToAnime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_Brightness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_Contrast,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewProp_NoiseStyle,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectStyleV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEffectStyleV1 Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEffectStyleV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"EffectStyleV1",
	Z_Construct_UScriptStruct_FEffectStyleV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectStyleV1_Statics::PropPointers),
	sizeof(FEffectStyleV1),
	alignof(FEffectStyleV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectStyleV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEffectStyleV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEffectStyleV1()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectStyleV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEffectStyleV1.InnerSingleton, Z_Construct_UScriptStruct_FEffectStyleV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEffectStyleV1.InnerSingleton);
}
// ********** End ScriptStruct FEffectStyleV1 ******************************************************

// ********** Begin ScriptStruct FExternalAssetsV1 *************************************************
struct Z_Construct_UScriptStruct_FExternalAssetsV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FExternalAssetsV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FExternalAssetsV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ReferenceImage_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ElementImages_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FExternalAssetsV1 constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReferenceImage;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ElementImages_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ElementImages;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FExternalAssetsV1 constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExternalAssetsV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FExternalAssetsV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FExternalAssetsV1;
class UScriptStruct* FExternalAssetsV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FExternalAssetsV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FExternalAssetsV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExternalAssetsV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("ExternalAssetsV1"));
	}
	return Z_Registration_Info_UScriptStruct_FExternalAssetsV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FExternalAssetsV1 Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ReferenceImage = { "ReferenceImage", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExternalAssetsV1, ReferenceImage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReferenceImage_MetaData), NewProp_ReferenceImage_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages_Inner = { "ElementImages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages = { "ElementImages", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExternalAssetsV1, ElementImages), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ElementImages_MetaData), NewProp_ElementImages_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ReferenceImage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FExternalAssetsV1 Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"ExternalAssetsV1",
	Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::PropPointers),
	sizeof(FExternalAssetsV1),
	alignof(FExternalAssetsV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FExternalAssetsV1()
{
	if (!Z_Registration_Info_UScriptStruct_FExternalAssetsV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FExternalAssetsV1.InnerSingleton, Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FExternalAssetsV1.InnerSingleton);
}
// ********** End ScriptStruct FExternalAssetsV1 ***************************************************

// ********** Begin ScriptStruct FEffectSpecV1 *****************************************************
struct Z_Construct_UScriptStruct_FEffectSpecV1_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEffectSpecV1); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEffectSpecV1); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EffectName_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GlobalStyle_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Layers_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ExternalAssets_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEffectSpecV1 constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_EffectName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GlobalStyle;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Layers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Layers;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ExternalAssets;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEffectSpecV1 constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEffectSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEffectSpecV1_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEffectSpecV1;
class UScriptStruct* FEffectSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEffectSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEffectSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EffectSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_FEffectSpecV1.OuterSingleton;
	}

// ********** Begin ScriptStruct FEffectSpecV1 Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_EffectName = { "EffectName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, EffectName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EffectName_MetaData), NewProp_EffectName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_GlobalStyle = { "GlobalStyle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, GlobalStyle), Z_Construct_UScriptStruct_FEffectStyleV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GlobalStyle_MetaData), NewProp_GlobalStyle_MetaData) }; // 2238228518
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers_Inner = { "Layers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FLayerSpecV1, METADATA_PARAMS(0, nullptr) }; // 3157470415
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers = { "Layers", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, Layers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Layers_MetaData), NewProp_Layers_MetaData) }; // 3157470415
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_ExternalAssets = { "ExternalAssets", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, ExternalAssets), Z_Construct_UScriptStruct_FExternalAssetsV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExternalAssets_MetaData), NewProp_ExternalAssets_MetaData) }; // 606971044
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEffectSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_EffectName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_GlobalStyle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_ExternalAssets,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectSpecV1_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEffectSpecV1 Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"EffectSpecV1",
	Z_Construct_UScriptStruct_FEffectSpecV1_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectSpecV1_Statics::PropPointers),
	sizeof(FEffectSpecV1),
	alignof(FEffectSpecV1),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectSpecV1_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEffectSpecV1_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEffectSpecV1()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEffectSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FEffectSpecV1_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEffectSpecV1.InnerSingleton);
}
// ********** End ScriptStruct FEffectSpecV1 *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h__Script_VFXAgentCore_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FMaterialHLSLInput::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewStructOps, TEXT("MaterialHLSLInput"),&Z_Registration_Info_UScriptStruct_FMaterialHLSLInput, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLInput), 3243923542U) },
		{ FMaterialHLSLTextureInput::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewStructOps, TEXT("MaterialHLSLTextureInput"),&Z_Registration_Info_UScriptStruct_FMaterialHLSLTextureInput, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLTextureInput), 4226001081U) },
		{ FMaterialHLSLOutputs::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewStructOps, TEXT("MaterialHLSLOutputs"),&Z_Registration_Info_UScriptStruct_FMaterialHLSLOutputs, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLOutputs), 603146422U) },
		{ FMaterialHLSLCustom::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewStructOps, TEXT("MaterialHLSLCustom"),&Z_Registration_Info_UScriptStruct_FMaterialHLSLCustom, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLCustom), 1922422627U) },
		{ FMaterialSpecV1::StaticStruct, Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewStructOps, TEXT("MaterialSpecV1"),&Z_Registration_Info_UScriptStruct_FMaterialSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialSpecV1), 1341355002U) },
		{ FLayerSpawnSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewStructOps, TEXT("LayerSpawnSpecV1"),&Z_Registration_Info_UScriptStruct_FLayerSpawnSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerSpawnSpecV1), 4258502672U) },
		{ FLayerInitSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewStructOps, TEXT("LayerInitSpecV1"),&Z_Registration_Info_UScriptStruct_FLayerInitSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerInitSpecV1), 1872821897U) },
		{ FLayerUpdateSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewStructOps, TEXT("LayerUpdateSpecV1"),&Z_Registration_Info_UScriptStruct_FLayerUpdateSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerUpdateSpecV1), 1920722500U) },
		{ FTextureRequestV1::StaticStruct, Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewStructOps, TEXT("TextureRequestV1"),&Z_Registration_Info_UScriptStruct_FTextureRequestV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTextureRequestV1), 2979864525U) },
		{ FModelRequestV1::StaticStruct, Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewStructOps, TEXT("ModelRequestV1"),&Z_Registration_Info_UScriptStruct_FModelRequestV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FModelRequestV1), 1079469488U) },
		{ FMotionSpecV1::StaticStruct, Z_Construct_UScriptStruct_FMotionSpecV1_Statics::NewStructOps, TEXT("MotionSpecV1"),&Z_Registration_Info_UScriptStruct_FMotionSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMotionSpecV1), 2955677861U) },
		{ FQualityBudgetV1::StaticStruct, Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewStructOps, TEXT("QualityBudgetV1"),&Z_Registration_Info_UScriptStruct_FQualityBudgetV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FQualityBudgetV1), 2706606290U) },
		{ FLayerSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewStructOps, TEXT("LayerSpecV1"),&Z_Registration_Info_UScriptStruct_FLayerSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerSpecV1), 3157470415U) },
		{ FEffectStyleV1::StaticStruct, Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewStructOps, TEXT("EffectStyleV1"),&Z_Registration_Info_UScriptStruct_FEffectStyleV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEffectStyleV1), 2238228518U) },
		{ FExternalAssetsV1::StaticStruct, Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewStructOps, TEXT("ExternalAssetsV1"),&Z_Registration_Info_UScriptStruct_FExternalAssetsV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExternalAssetsV1), 606971044U) },
		{ FEffectSpecV1::StaticStruct, Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewStructOps, TEXT("EffectSpecV1"),&Z_Registration_Info_UScriptStruct_FEffectSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEffectSpecV1), 2820674956U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h__Script_VFXAgentCore_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h__Script_VFXAgentCore_3350632011{
	TEXT("/Script/VFXAgentCore"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h__Script_VFXAgentCore_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h__Script_VFXAgentCore_Statics::ScriptStructInfo),
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
