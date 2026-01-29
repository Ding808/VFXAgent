// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentCore/Public/VFXRecipe.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVFXRecipe() {}

// Begin Cross Module References
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
UPackage* Z_Construct_UPackage__Script_VFXAgentCore();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXRendererType();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEffectSpec();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterSpec();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXMaterialRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXPerSpawnInfo();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXRepairReport();
// End Cross Module References

// Begin ScriptStruct FVFXEmitterRecipe
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXEmitterRecipe;
class UScriptStruct* FVFXEmitterRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXEmitterRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXEmitterRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXEmitterRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXEmitterRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_VFXEmitterRecipe.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FVFXEmitterRecipe>()
{
	return FVFXEmitterRecipe::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "Emitter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Optional human-readable layer name/purpose (e.g. \"CoreBurst\", \"Sparks\", \"Smoke\", \"Shockwave\").\n// Used for naming within the generated Niagara System.\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional human-readable layer name/purpose (e.g. \"CoreBurst\", \"Sparks\", \"Smoke\", \"Shockwave\").\nUsed for naming within the generated Niagara System." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnRate_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstCount_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RendererType_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TemplateName_MetaData[] = {
		{ "Category", "Emitter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// New: Specify a preferred Niagara template to base this emitter on.\n// Examples: \"Fountain\", \"DirectionalBurst\", \"HangingParticulates\", \"OmnidirectionalBurst\", \"UpwardMeshBurst\", \"Beam\"\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "New: Specify a preferred Niagara template to base this emitter on.\nExamples: \"Fountain\", \"DirectionalBurst\", \"HangingParticulates\", \"OmnidirectionalBurst\", \"UpwardMeshBurst\", \"Beam\"" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Size_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "Category", "Emitter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Initial velocity direction and magnitude for particles\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initial velocity direction and magnitude for particles" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpawnRate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BurstCount;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TemplateName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Size;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEmitterRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SpawnRate = { "SpawnRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, SpawnRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnRate_MetaData), NewProp_SpawnRate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstCount = { "BurstCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, BurstCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstCount_MetaData), NewProp_BurstCount_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, RendererType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_TemplateName = { "TemplateName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, TemplateName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemplateName_MetaData), NewProp_TemplateName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Size), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Size_MetaData), NewProp_Size_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SpawnRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_TemplateName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Lifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Size,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Velocity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXEmitterRecipe",
	Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::PropPointers),
	sizeof(FVFXEmitterRecipe),
	alignof(FVFXEmitterRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_VFXEmitterRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXEmitterRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXEmitterRecipe.InnerSingleton;
}
// End ScriptStruct FVFXEmitterRecipe

// Begin ScriptStruct FVFXMaterialRecipe
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXMaterialRecipe;
class UScriptStruct* FVFXMaterialRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXMaterialRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXMaterialRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXMaterialRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXMaterialRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_VFXMaterialRecipe.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FVFXMaterialRecipe>()
{
	return FVFXMaterialRecipe::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsAdditive_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseMaterialPath_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static void NewProp_bIsAdditive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsAdditive;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BaseMaterialPath;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXMaterialRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
void Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive_SetBit(void* Obj)
{
	((FVFXMaterialRecipe*)Obj)->bIsAdditive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive = { "bIsAdditive", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXMaterialRecipe), &Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsAdditive_MetaData), NewProp_bIsAdditive_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseMaterialPath = { "BaseMaterialPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, BaseMaterialPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseMaterialPath_MetaData), NewProp_BaseMaterialPath_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseMaterialPath,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXMaterialRecipe",
	Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::PropPointers),
	sizeof(FVFXMaterialRecipe),
	alignof(FVFXMaterialRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXMaterialRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_VFXMaterialRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXMaterialRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXMaterialRecipe.InnerSingleton;
}
// End ScriptStruct FVFXMaterialRecipe

// Begin Enum EVFXRendererType
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXRendererType;
static UEnum* EVFXRendererType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXRendererType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXRendererType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXRendererType, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXRendererType"));
	}
	return Z_Registration_Info_UEnum_EVFXRendererType.OuterSingleton;
}
template<> VFXAGENTCORE_API UEnum* StaticEnum<EVFXRendererType>()
{
	return EVFXRendererType_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// --- New Schema for Niagara Spec ---\n" },
#endif
		{ "Light.DisplayName", "Light" },
		{ "Light.Name", "EVFXRendererType::Light" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "Ribbon.DisplayName", "Ribbon" },
		{ "Ribbon.Name", "EVFXRendererType::Ribbon" },
		{ "Sprite.DisplayName", "Sprite" },
		{ "Sprite.Name", "EVFXRendererType::Sprite" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "--- New Schema for Niagara Spec ---" },
#endif
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXRendererType::Sprite", (int64)EVFXRendererType::Sprite },
		{ "EVFXRendererType::Ribbon", (int64)EVFXRendererType::Ribbon },
		{ "EVFXRendererType::Light", (int64)EVFXRendererType::Light },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXRendererType",
	"EVFXRendererType",
	Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXRendererType()
{
	if (!Z_Registration_Info_UEnum_EVFXRendererType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXRendererType.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXRendererType.InnerSingleton;
}
// End Enum EVFXRendererType

// Begin ScriptStruct FVFXPerSpawnInfo
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo;
class UScriptStruct* FVFXPerSpawnInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXPerSpawnInfo, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXPerSpawnInfo"));
	}
	return Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FVFXPerSpawnInfo>()
{
	return FVFXPerSpawnInfo::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rate_MetaData[] = {
		{ "Category", "Spawn" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Burst_MetaData[] = {
		{ "Category", "Spawn" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// If > 0, use SpawnRate\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "If > 0, use SpawnRate" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Burst;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXPerSpawnInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Rate = { "Rate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPerSpawnInfo, Rate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rate_MetaData), NewProp_Rate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Burst = { "Burst", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPerSpawnInfo, Burst), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Burst_MetaData), NewProp_Burst_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Rate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Burst,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXPerSpawnInfo",
	Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::PropPointers),
	sizeof(FVFXPerSpawnInfo),
	alignof(FVFXPerSpawnInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXPerSpawnInfo()
{
	if (!Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo.InnerSingleton, Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo.InnerSingleton;
}
// End ScriptStruct FVFXPerSpawnInfo

// Begin ScriptStruct FVFXEmitterSpec
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXEmitterSpec;
class UScriptStruct* FVFXEmitterSpec::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXEmitterSpec.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXEmitterSpec.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXEmitterSpec, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXEmitterSpec"));
	}
	return Z_Registration_Info_UScriptStruct_VFXEmitterSpec.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FVFXEmitterSpec>()
{
	return FVFXEmitterSpec::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TemplatePath_MetaData[] = {
		{ "Category", "Emitter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Path to a Niagara System or Emitter asset to use as template\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Path to a Niagara System or Emitter asset to use as template" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TemplateId_MetaData[] = {
		{ "Category", "Emitter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Or a known ID like \"Fountain\", \"Beam\" if we support mapping\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Or a known ID like \"Fountain\", \"Beam\" if we support mapping" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RendererType_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Spawn_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Size_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Notes_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TemplatePath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TemplateId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_RendererType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Spawn;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Size;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Notes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEmitterSpec>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplatePath = { "TemplatePath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, TemplatePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemplatePath_MetaData), NewProp_TemplatePath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplateId = { "TemplateId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, TemplateId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemplateId_MetaData), NewProp_TemplateId_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, RendererType), Z_Construct_UEnum_VFXAgentCore_EVFXRendererType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) }; // 2327286842
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Spawn = { "Spawn", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Spawn), Z_Construct_UScriptStruct_FVFXPerSpawnInfo, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spawn_MetaData), NewProp_Spawn_MetaData) }; // 1959196622
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Size), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Size_MetaData), NewProp_Size_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Notes = { "Notes", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Notes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Notes_MetaData), NewProp_Notes_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplatePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplateId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Spawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Lifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Size,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Notes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXEmitterSpec",
	Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::PropPointers),
	sizeof(FVFXEmitterSpec),
	alignof(FVFXEmitterSpec),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterSpec()
{
	if (!Z_Registration_Info_UScriptStruct_VFXEmitterSpec.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXEmitterSpec.InnerSingleton, Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXEmitterSpec.InnerSingleton;
}
// End ScriptStruct FVFXEmitterSpec

// Begin ScriptStruct FVFXEffectSpec
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXEffectSpec;
class UScriptStruct* FVFXEffectSpec::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXEffectSpec.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXEffectSpec.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXEffectSpec, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXEffectSpec"));
	}
	return Z_Registration_Info_UScriptStruct_VFXEffectSpec.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FVFXEffectSpec>()
{
	return FVFXEffectSpec::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXEffectSpec_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SystemName_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetPath_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Emitters_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SystemName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TargetPath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Emitters_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Emitters;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEffectSpec>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_SystemName = { "SystemName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, SystemName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SystemName_MetaData), NewProp_SystemName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_TargetPath = { "TargetPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, TargetPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetPath_MetaData), NewProp_TargetPath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters_Inner = { "Emitters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXEmitterSpec, METADATA_PARAMS(0, nullptr) }; // 2722188073
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters = { "Emitters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, Emitters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Emitters_MetaData), NewProp_Emitters_MetaData) }; // 2722188073
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_SystemName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_TargetPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXEffectSpec",
	Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::PropPointers),
	sizeof(FVFXEffectSpec),
	alignof(FVFXEffectSpec),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXEffectSpec()
{
	if (!Z_Registration_Info_UScriptStruct_VFXEffectSpec.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXEffectSpec.InnerSingleton, Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXEffectSpec.InnerSingleton;
}
// End ScriptStruct FVFXEffectSpec

// Begin ScriptStruct FVFXRepairReport
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXRepairReport;
class UScriptStruct* FVFXRepairReport::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXRepairReport.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXRepairReport.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXRepairReport, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXRepairReport"));
	}
	return Z_Registration_Info_UScriptStruct_VFXRepairReport.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FVFXRepairReport>()
{
	return FVFXRepairReport::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXRepairReport_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SystemPath_MetaData[] = {
		{ "Category", "Report" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCompileSuccess_MetaData[] = {
		{ "Category", "Report" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Errors_MetaData[] = {
		{ "Category", "Report" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Warnings_MetaData[] = {
		{ "Category", "Report" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SystemPath;
	static void NewProp_bCompileSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCompileSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Errors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Errors;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Warnings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Warnings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXRepairReport>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_SystemPath = { "SystemPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRepairReport, SystemPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SystemPath_MetaData), NewProp_SystemPath_MetaData) };
void Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_bCompileSuccess_SetBit(void* Obj)
{
	((FVFXRepairReport*)Obj)->bCompileSuccess = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_bCompileSuccess = { "bCompileSuccess", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXRepairReport), &Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_bCompileSuccess_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCompileSuccess_MetaData), NewProp_bCompileSuccess_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Errors_Inner = { "Errors", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Errors = { "Errors", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRepairReport, Errors), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Errors_MetaData), NewProp_Errors_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Warnings_Inner = { "Warnings", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Warnings = { "Warnings", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRepairReport, Warnings), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Warnings_MetaData), NewProp_Warnings_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXRepairReport_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_SystemPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_bCompileSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Errors_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Errors,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Warnings_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewProp_Warnings,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRepairReport_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXRepairReport_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXRepairReport",
	Z_Construct_UScriptStruct_FVFXRepairReport_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRepairReport_Statics::PropPointers),
	sizeof(FVFXRepairReport),
	alignof(FVFXRepairReport),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRepairReport_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXRepairReport_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXRepairReport()
{
	if (!Z_Registration_Info_UScriptStruct_VFXRepairReport.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXRepairReport.InnerSingleton, Z_Construct_UScriptStruct_FVFXRepairReport_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXRepairReport.InnerSingleton;
}
// End ScriptStruct FVFXRepairReport

// Begin ScriptStruct FVFXRecipe
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_VFXRecipe;
class UScriptStruct* FVFXRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_VFXRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_VFXRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_VFXRecipe.OuterSingleton;
}
template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<FVFXRecipe>()
{
	return FVFXRecipe::StaticStruct();
}
struct Z_Construct_UScriptStruct_FVFXRecipe_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLoop_MetaData[] = {
		{ "Category", "System" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Duration_MetaData[] = {
		{ "Category", "System" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarmupTime_MetaData[] = {
		{ "Category", "System" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// 0 for infinite\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "0 for infinite" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bounds_MetaData[] = {
		{ "Category", "System" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Emitters_MetaData[] = {
		{ "Category", "Emitters" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Parameters_MetaData[] = {
		{ "Category", "Parameters" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Materials_MetaData[] = {
		{ "Category", "Materials" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// User parameters like color, intensity\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "User parameters like color, intensity" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dependencies_MetaData[] = {
		{ "Category", "Dependencies" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "Category", "Version" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Texture/Model paths\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Texture/Model paths" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_bLoop_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLoop;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WarmupTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bounds;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Emitters_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Emitters;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Parameters_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Parameters_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Parameters;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Materials_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Materials;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Dependencies_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Dependencies;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Version;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
void Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop_SetBit(void* Obj)
{
	((FVFXRecipe*)Obj)->bLoop = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop = { "bLoop", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXRecipe), &Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLoop_MetaData), NewProp_bLoop_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Duration = { "Duration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Duration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Duration_MetaData), NewProp_Duration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_WarmupTime = { "WarmupTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, WarmupTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarmupTime_MetaData), NewProp_WarmupTime_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Bounds = { "Bounds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Bounds), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bounds_MetaData), NewProp_Bounds_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters_Inner = { "Emitters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXEmitterRecipe, METADATA_PARAMS(0, nullptr) }; // 2534319025
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters = { "Emitters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Emitters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Emitters_MetaData), NewProp_Emitters_MetaData) }; // 2534319025
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters_ValueProp = { "Parameters", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters_Key_KeyProp = { "Parameters_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters = { "Parameters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Parameters), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Parameters_MetaData), NewProp_Parameters_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Materials_Inner = { "Materials", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXMaterialRecipe, METADATA_PARAMS(0, nullptr) }; // 115514806
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Materials = { "Materials", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Materials), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Materials_MetaData), NewProp_Materials_MetaData) }; // 115514806
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Dependencies_Inner = { "Dependencies", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Dependencies = { "Dependencies", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Dependencies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dependencies_MetaData), NewProp_Dependencies_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_WarmupTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Bounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Materials_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Materials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Dependencies_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Dependencies,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Version,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRecipe_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXRecipe",
	Z_Construct_UScriptStruct_FVFXRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRecipe_Statics::PropPointers),
	sizeof(FVFXRecipe),
	alignof(FVFXRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_VFXRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_VFXRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXRecipe_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_VFXRecipe.InnerSingleton;
}
// End ScriptStruct FVFXRecipe

// Begin Registration
struct Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EVFXRendererType_StaticEnum, TEXT("EVFXRendererType"), &Z_Registration_Info_UEnum_EVFXRendererType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2327286842U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FVFXEmitterRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewStructOps, TEXT("VFXEmitterRecipe"), &Z_Registration_Info_UScriptStruct_VFXEmitterRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEmitterRecipe), 2534319025U) },
		{ FVFXMaterialRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewStructOps, TEXT("VFXMaterialRecipe"), &Z_Registration_Info_UScriptStruct_VFXMaterialRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXMaterialRecipe), 115514806U) },
		{ FVFXPerSpawnInfo::StaticStruct, Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewStructOps, TEXT("VFXPerSpawnInfo"), &Z_Registration_Info_UScriptStruct_VFXPerSpawnInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXPerSpawnInfo), 1959196622U) },
		{ FVFXEmitterSpec::StaticStruct, Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewStructOps, TEXT("VFXEmitterSpec"), &Z_Registration_Info_UScriptStruct_VFXEmitterSpec, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEmitterSpec), 2722188073U) },
		{ FVFXEffectSpec::StaticStruct, Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewStructOps, TEXT("VFXEffectSpec"), &Z_Registration_Info_UScriptStruct_VFXEffectSpec, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEffectSpec), 3957558363U) },
		{ FVFXRepairReport::StaticStruct, Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewStructOps, TEXT("VFXRepairReport"), &Z_Registration_Info_UScriptStruct_VFXRepairReport, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXRepairReport), 1445951879U) },
		{ FVFXRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewStructOps, TEXT("VFXRecipe"), &Z_Registration_Info_UScriptStruct_VFXRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXRecipe), 2794885106U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_1404116158(TEXT("/Script/VFXAgentCore"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
