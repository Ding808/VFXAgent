// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentCore/Public/EffectSpecV1.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEffectSpecV1() {}

// Begin Cross Module References
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
// End Cross Module References

// Begin ScriptStruct FMaterialHLSLInput
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MaterialHLSLInput;
class UScriptStruct* FMaterialHLSLInput::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLInput.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MaterialHLSLInput.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLInput, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLInput"));
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLInput.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FMaterialHLSLInput>()
{
	return FMaterialHLSLInput::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics
{
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
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Type;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Default;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Min;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Max;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLInput>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLInput.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MaterialHLSLInput.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLInput.InnerSingleton;
}
// End ScriptStruct FMaterialHLSLInput

// Begin ScriptStruct FMaterialHLSLTextureInput
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput;
class UScriptStruct* FMaterialHLSLTextureInput::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLTextureInput, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLTextureInput"));
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FMaterialHLSLTextureInput>()
{
	return FMaterialHLSLTextureInput::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics
{
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
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Usage;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLTextureInput>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLTextureInput, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Usage = { "Usage", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLTextureInput, Usage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Usage_MetaData), NewProp_Usage_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewProp_Usage,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::PropPointers) < 2048);
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
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput.InnerSingleton;
}
// End ScriptStruct FMaterialHLSLTextureInput

// Begin ScriptStruct FMaterialHLSLOutputs
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs;
class UScriptStruct* FMaterialHLSLOutputs::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLOutputs, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLOutputs"));
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FMaterialHLSLOutputs>()
{
	return FMaterialHLSLOutputs::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics
{
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
	static void NewProp_emissive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_emissive;
	static void NewProp_opacity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_opacity;
	static void NewProp_distortion_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_distortion;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLOutputs>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs.InnerSingleton;
}
// End ScriptStruct FMaterialHLSLOutputs

// Begin ScriptStruct FMaterialHLSLCustom
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MaterialHLSLCustom;
class UScriptStruct* FMaterialHLSLCustom::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLCustom.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MaterialHLSLCustom.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialHLSLCustom, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialHLSLCustom"));
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLCustom.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FMaterialHLSLCustom>()
{
	return FMaterialHLSLCustom::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics
{
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
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialHLSLCustom>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
void Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Enabled_SetBit(void* Obj)
{
	((FMaterialHLSLCustom*)Obj)->Enabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Enabled = { "Enabled", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialHLSLCustom), &Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Enabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Enabled_MetaData), NewProp_Enabled_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Code = { "Code", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, Code), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Code_MetaData), NewProp_Code_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Inputs_Inner = { "Inputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMaterialHLSLInput, METADATA_PARAMS(0, nullptr) }; // 2532429878
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Inputs = { "Inputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, Inputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Inputs_MetaData), NewProp_Inputs_MetaData) }; // 2532429878
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_TextureInputs_Inner = { "TextureInputs", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FMaterialHLSLTextureInput, METADATA_PARAMS(0, nullptr) }; // 958671619
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_TextureInputs = { "TextureInputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, TextureInputs), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextureInputs_MetaData), NewProp_TextureInputs_MetaData) }; // 958671619
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewProp_Outputs = { "Outputs", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialHLSLCustom, Outputs), Z_Construct_UScriptStruct_FMaterialHLSLOutputs, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Outputs_MetaData), NewProp_Outputs_MetaData) }; // 3128722158
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
	if (!Z_Registration_Info_UScriptStruct_MaterialHLSLCustom.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MaterialHLSLCustom.InnerSingleton, Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MaterialHLSLCustom.InnerSingleton;
}
// End ScriptStruct FMaterialHLSLCustom

// Begin ScriptStruct FMaterialSpecV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MaterialSpecV1;
class UScriptStruct* FMaterialSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MaterialSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MaterialSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_MaterialSpecV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FMaterialSpecV1>()
{
	return FMaterialSpecV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMaterialSpecV1_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Shading_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Blend_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// unlit|lit\n" },
#endif
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "unlit|lit" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Features_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// additive|translucent|masked|opaque\n" },
#endif
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "additive|translucent|masked|opaque" },
#endif
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
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewProp_HLSLCustom = { "HLSLCustom", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV1, HLSLCustom), Z_Construct_UScriptStruct_FMaterialHLSLCustom, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HLSLCustom_MetaData), NewProp_HLSLCustom_MetaData) }; // 1430061180
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
	if (!Z_Registration_Info_UScriptStruct_MaterialSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MaterialSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MaterialSpecV1.InnerSingleton;
}
// End ScriptStruct FMaterialSpecV1

// Begin ScriptStruct FLayerSpawnSpecV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1;
class UScriptStruct* FLayerSpawnSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerSpawnSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerSpawnSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FLayerSpawnSpecV1>()
{
	return FLayerSpawnSpecV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mode_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rate_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// rate|burst\n" },
#endif
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "rate|burst" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Duration_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Mode;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BurstCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Duration;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerSpawnSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
	if (!Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1.InnerSingleton;
}
// End ScriptStruct FLayerSpawnSpecV1

// Begin ScriptStruct FLayerInitSpecV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LayerInitSpecV1;
class UScriptStruct* FLayerInitSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LayerInitSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LayerInitSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerInitSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerInitSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_LayerInitSpecV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FLayerInitSpecV1>()
{
	return FLayerInitSpecV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics
{
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
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SizeRange;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DirectionMode;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerInitSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
	if (!Z_Registration_Info_UScriptStruct_LayerInitSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LayerInitSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_LayerInitSpecV1.InnerSingleton;
}
// End ScriptStruct FLayerInitSpecV1

// Begin ScriptStruct FLayerUpdateSpecV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1;
class UScriptStruct* FLayerUpdateSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerUpdateSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerUpdateSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FLayerUpdateSpecV1>()
{
	return FLayerUpdateSpecV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics
{
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
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Drag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurlNoiseStrength;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ColorOverLife;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AlphaOverLife;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerUpdateSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
	if (!Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1.InnerSingleton;
}
// End ScriptStruct FLayerUpdateSpecV1

// Begin ScriptStruct FTextureRequestV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_TextureRequestV1;
class UScriptStruct* FTextureRequestV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_TextureRequestV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_TextureRequestV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTextureRequestV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("TextureRequestV1"));
	}
	return Z_Registration_Info_UScriptStruct_TextureRequestV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FTextureRequestV1>()
{
	return FTextureRequestV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FTextureRequestV1_Statics
{
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
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Usage;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Width;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Height;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTextureRequestV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
	if (!Z_Registration_Info_UScriptStruct_TextureRequestV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_TextureRequestV1.InnerSingleton, Z_Construct_UScriptStruct_FTextureRequestV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_TextureRequestV1.InnerSingleton;
}
// End ScriptStruct FTextureRequestV1

// Begin ScriptStruct FModelRequestV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ModelRequestV1;
class UScriptStruct* FModelRequestV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ModelRequestV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ModelRequestV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FModelRequestV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("ModelRequestV1"));
	}
	return Z_Registration_Info_UScriptStruct_ModelRequestV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FModelRequestV1>()
{
	return FModelRequestV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FModelRequestV1_Statics
{
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
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Format;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FModelRequestV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModelRequestV1, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Format = { "Format", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FModelRequestV1, Format), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Format_MetaData), NewProp_Format_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FModelRequestV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewProp_Format,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FModelRequestV1_Statics::PropPointers) < 2048);
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
	if (!Z_Registration_Info_UScriptStruct_ModelRequestV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ModelRequestV1.InnerSingleton, Z_Construct_UScriptStruct_FModelRequestV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_ModelRequestV1.InnerSingleton;
}
// End ScriptStruct FModelRequestV1

// Begin ScriptStruct FMotionSpecV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_MotionSpecV1;
class UScriptStruct* FMotionSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_MotionSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_MotionSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMotionSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MotionSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_MotionSpecV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FMotionSpecV1>()
{
	return FMotionSpecV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FMotionSpecV1_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Semantic_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Semantic;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMotionSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMotionSpecV1_Statics::NewProp_Semantic = { "Semantic", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionSpecV1, Semantic), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Semantic_MetaData), NewProp_Semantic_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMotionSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionSpecV1_Statics::NewProp_Semantic,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMotionSpecV1_Statics::PropPointers) < 2048);
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
	if (!Z_Registration_Info_UScriptStruct_MotionSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_MotionSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FMotionSpecV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_MotionSpecV1.InnerSingleton;
}
// End ScriptStruct FMotionSpecV1

// Begin ScriptStruct FQualityBudgetV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_QualityBudgetV1;
class UScriptStruct* FQualityBudgetV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_QualityBudgetV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_QualityBudgetV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FQualityBudgetV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("QualityBudgetV1"));
	}
	return Z_Registration_Info_UScriptStruct_QualityBudgetV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FQualityBudgetV1>()
{
	return FQualityBudgetV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FQualityBudgetV1_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PerfCostHint_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxParticlesHint_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// low|mid|high\n" },
#endif
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "low|mid|high" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_PerfCostHint;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxParticlesHint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FQualityBudgetV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_PerfCostHint = { "PerfCostHint", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FQualityBudgetV1, PerfCostHint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PerfCostHint_MetaData), NewProp_PerfCostHint_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_MaxParticlesHint = { "MaxParticlesHint", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FQualityBudgetV1, MaxParticlesHint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxParticlesHint_MetaData), NewProp_MaxParticlesHint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_PerfCostHint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewProp_MaxParticlesHint,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::PropPointers) < 2048);
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
	if (!Z_Registration_Info_UScriptStruct_QualityBudgetV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_QualityBudgetV1.InnerSingleton, Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_QualityBudgetV1.InnerSingleton;
}
// End ScriptStruct FQualityBudgetV1

// Begin ScriptStruct FLayerSpecV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_LayerSpecV1;
class UScriptStruct* FLayerSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_LayerSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_LayerSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_LayerSpecV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FLayerSpecV1>()
{
	return FLayerSpecV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FLayerSpecV1_Statics
{
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
#if !UE_BUILD_SHIPPING
		{ "Comment", "// sprite|ribbon|mesh\n" },
#endif
		{ "ModuleRelativePath", "Public/EffectSpecV1.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "sprite|ribbon|mesh" },
#endif
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
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Id), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Id_MetaData), NewProp_Id_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Role), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, RendererType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Spawn = { "Spawn", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Spawn), Z_Construct_UScriptStruct_FLayerSpawnSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spawn_MetaData), NewProp_Spawn_MetaData) }; // 823277832
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Init = { "Init", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Init), Z_Construct_UScriptStruct_FLayerInitSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Init_MetaData), NewProp_Init_MetaData) }; // 2440158166
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Update = { "Update", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Update), Z_Construct_UScriptStruct_FLayerUpdateSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Update_MetaData), NewProp_Update_MetaData) }; // 1022951777
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Material), Z_Construct_UScriptStruct_FMaterialSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Material_MetaData), NewProp_Material_MetaData) }; // 4018682562
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_TexturesNeeded_Inner = { "TexturesNeeded", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FTextureRequestV1, METADATA_PARAMS(0, nullptr) }; // 1026213314
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_TexturesNeeded = { "TexturesNeeded", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, TexturesNeeded), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TexturesNeeded_MetaData), NewProp_TexturesNeeded_MetaData) }; // 1026213314
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_ModelNeeded = { "ModelNeeded", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, ModelNeeded), Z_Construct_UScriptStruct_FModelRequestV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ModelNeeded_MetaData), NewProp_ModelNeeded_MetaData) }; // 2121624231
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_Motion = { "Motion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, Motion), Z_Construct_UScriptStruct_FMotionSpecV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Motion_MetaData), NewProp_Motion_MetaData) }; // 1886923392
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewProp_QualityBudget = { "QualityBudget", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV1, QualityBudget), Z_Construct_UScriptStruct_FQualityBudgetV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_QualityBudget_MetaData), NewProp_QualityBudget_MetaData) }; // 2825893843
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
	if (!Z_Registration_Info_UScriptStruct_LayerSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_LayerSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FLayerSpecV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_LayerSpecV1.InnerSingleton;
}
// End ScriptStruct FLayerSpecV1

// Begin ScriptStruct FEffectStyleV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_EffectStyleV1;
class UScriptStruct* FEffectStyleV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_EffectStyleV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_EffectStyleV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEffectStyleV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EffectStyleV1"));
	}
	return Z_Registration_Info_UScriptStruct_EffectStyleV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FEffectStyleV1>()
{
	return FEffectStyleV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FEffectStyleV1_Statics
{
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
	static const UECodeGen_Private::FStrPropertyParams NewProp_Palette;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RealismToAnime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Brightness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Contrast;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NoiseStyle;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEffectStyleV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
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
	if (!Z_Registration_Info_UScriptStruct_EffectStyleV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_EffectStyleV1.InnerSingleton, Z_Construct_UScriptStruct_FEffectStyleV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_EffectStyleV1.InnerSingleton;
}
// End ScriptStruct FEffectStyleV1

// Begin ScriptStruct FExternalAssetsV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_ExternalAssetsV1;
class UScriptStruct* FExternalAssetsV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_ExternalAssetsV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_ExternalAssetsV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FExternalAssetsV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("ExternalAssetsV1"));
	}
	return Z_Registration_Info_UScriptStruct_ExternalAssetsV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FExternalAssetsV1>()
{
	return FExternalAssetsV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FExternalAssetsV1_Statics
{
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
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReferenceImage;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ElementImages_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ElementImages;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FExternalAssetsV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ReferenceImage = { "ReferenceImage", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExternalAssetsV1, ReferenceImage), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ReferenceImage_MetaData), NewProp_ReferenceImage_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages_Inner = { "ElementImages", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages = { "ElementImages", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FExternalAssetsV1, ElementImages), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ElementImages_MetaData), NewProp_ElementImages_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ReferenceImage,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewProp_ElementImages,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::PropPointers) < 2048);
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
	if (!Z_Registration_Info_UScriptStruct_ExternalAssetsV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_ExternalAssetsV1.InnerSingleton, Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_ExternalAssetsV1.InnerSingleton;
}
// End ScriptStruct FExternalAssetsV1

// Begin ScriptStruct FEffectSpecV1
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_EffectSpecV1;
class UScriptStruct* FEffectSpecV1::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_EffectSpecV1.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_EffectSpecV1.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEffectSpecV1, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EffectSpecV1"));
	}
	return Z_Registration_Info_UScriptStruct_EffectSpecV1.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FEffectSpecV1>()
{
	return FEffectSpecV1::StaticStruct();
}
struct Z_Construct_UScriptStruct_FEffectSpecV1_Statics
{
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
	static const UECodeGen_Private::FStrPropertyParams NewProp_EffectName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GlobalStyle;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Layers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Layers;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ExternalAssets;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEffectSpecV1>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_EffectName = { "EffectName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, EffectName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EffectName_MetaData), NewProp_EffectName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_GlobalStyle = { "GlobalStyle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, GlobalStyle), Z_Construct_UScriptStruct_FEffectStyleV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GlobalStyle_MetaData), NewProp_GlobalStyle_MetaData) }; // 2674523580
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers_Inner = { "Layers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FLayerSpecV1, METADATA_PARAMS(0, nullptr) }; // 704838237
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers = { "Layers", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, Layers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Layers_MetaData), NewProp_Layers_MetaData) }; // 704838237
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_ExternalAssets = { "ExternalAssets", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV1, ExternalAssets), Z_Construct_UScriptStruct_FExternalAssetsV1, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ExternalAssets_MetaData), NewProp_ExternalAssets_MetaData) }; // 2587979087
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEffectSpecV1_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_EffectName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_GlobalStyle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_Layers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewProp_ExternalAssets,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectSpecV1_Statics::PropPointers) < 2048);
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
	if (!Z_Registration_Info_UScriptStruct_EffectSpecV1.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_EffectSpecV1.InnerSingleton, Z_Construct_UScriptStruct_FEffectSpecV1_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_EffectSpecV1.InnerSingleton;
}
// End ScriptStruct FEffectSpecV1

// Begin Registration
struct Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FMaterialHLSLInput::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLInput_Statics::NewStructOps, TEXT("MaterialHLSLInput"), &Z_Registration_Info_UScriptStruct_MaterialHLSLInput, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLInput), 2532429878U) },
		{ FMaterialHLSLTextureInput::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLTextureInput_Statics::NewStructOps, TEXT("MaterialHLSLTextureInput"), &Z_Registration_Info_UScriptStruct_MaterialHLSLTextureInput, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLTextureInput), 958671619U) },
		{ FMaterialHLSLOutputs::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLOutputs_Statics::NewStructOps, TEXT("MaterialHLSLOutputs"), &Z_Registration_Info_UScriptStruct_MaterialHLSLOutputs, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLOutputs), 3128722158U) },
		{ FMaterialHLSLCustom::StaticStruct, Z_Construct_UScriptStruct_FMaterialHLSLCustom_Statics::NewStructOps, TEXT("MaterialHLSLCustom"), &Z_Registration_Info_UScriptStruct_MaterialHLSLCustom, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialHLSLCustom), 1430061180U) },
		{ FMaterialSpecV1::StaticStruct, Z_Construct_UScriptStruct_FMaterialSpecV1_Statics::NewStructOps, TEXT("MaterialSpecV1"), &Z_Registration_Info_UScriptStruct_MaterialSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialSpecV1), 4018682562U) },
		{ FLayerSpawnSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerSpawnSpecV1_Statics::NewStructOps, TEXT("LayerSpawnSpecV1"), &Z_Registration_Info_UScriptStruct_LayerSpawnSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerSpawnSpecV1), 823277832U) },
		{ FLayerInitSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerInitSpecV1_Statics::NewStructOps, TEXT("LayerInitSpecV1"), &Z_Registration_Info_UScriptStruct_LayerInitSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerInitSpecV1), 2440158166U) },
		{ FLayerUpdateSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerUpdateSpecV1_Statics::NewStructOps, TEXT("LayerUpdateSpecV1"), &Z_Registration_Info_UScriptStruct_LayerUpdateSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerUpdateSpecV1), 1022951777U) },
		{ FTextureRequestV1::StaticStruct, Z_Construct_UScriptStruct_FTextureRequestV1_Statics::NewStructOps, TEXT("TextureRequestV1"), &Z_Registration_Info_UScriptStruct_TextureRequestV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTextureRequestV1), 1026213314U) },
		{ FModelRequestV1::StaticStruct, Z_Construct_UScriptStruct_FModelRequestV1_Statics::NewStructOps, TEXT("ModelRequestV1"), &Z_Registration_Info_UScriptStruct_ModelRequestV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FModelRequestV1), 2121624231U) },
		{ FMotionSpecV1::StaticStruct, Z_Construct_UScriptStruct_FMotionSpecV1_Statics::NewStructOps, TEXT("MotionSpecV1"), &Z_Registration_Info_UScriptStruct_MotionSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMotionSpecV1), 1886923392U) },
		{ FQualityBudgetV1::StaticStruct, Z_Construct_UScriptStruct_FQualityBudgetV1_Statics::NewStructOps, TEXT("QualityBudgetV1"), &Z_Registration_Info_UScriptStruct_QualityBudgetV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FQualityBudgetV1), 2825893843U) },
		{ FLayerSpecV1::StaticStruct, Z_Construct_UScriptStruct_FLayerSpecV1_Statics::NewStructOps, TEXT("LayerSpecV1"), &Z_Registration_Info_UScriptStruct_LayerSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerSpecV1), 704838237U) },
		{ FEffectStyleV1::StaticStruct, Z_Construct_UScriptStruct_FEffectStyleV1_Statics::NewStructOps, TEXT("EffectStyleV1"), &Z_Registration_Info_UScriptStruct_EffectStyleV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEffectStyleV1), 2674523580U) },
		{ FExternalAssetsV1::StaticStruct, Z_Construct_UScriptStruct_FExternalAssetsV1_Statics::NewStructOps, TEXT("ExternalAssetsV1"), &Z_Registration_Info_UScriptStruct_ExternalAssetsV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FExternalAssetsV1), 2587979087U) },
		{ FEffectSpecV1::StaticStruct, Z_Construct_UScriptStruct_FEffectSpecV1_Statics::NewStructOps, TEXT("EffectSpecV1"), &Z_Registration_Info_UScriptStruct_EffectSpecV1, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEffectSpecV1), 2299935531U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h_635002656(TEXT("/Script/VFXAgentCore"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV1_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
