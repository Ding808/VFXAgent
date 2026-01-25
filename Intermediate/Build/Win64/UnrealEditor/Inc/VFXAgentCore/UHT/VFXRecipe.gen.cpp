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
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXMaterialRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXRecipe();
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "Emitter" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Sprite, Mesh, Ribbon\n" },
#endif
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Sprite, Mesh, Ribbon" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpawnRate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BurstCount;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEmitterRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SpawnRate = { "SpawnRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, SpawnRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnRate_MetaData), NewProp_SpawnRate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstCount = { "BurstCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, BurstCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstCount_MetaData), NewProp_BurstCount_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, RendererType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SpawnRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Lifetime,
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
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters_Inner = { "Emitters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXEmitterRecipe, METADATA_PARAMS(0, nullptr) }; // 1162450287
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters = { "Emitters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Emitters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Emitters_MetaData), NewProp_Emitters_MetaData) }; // 1162450287
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
struct Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics
{
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FVFXEmitterRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewStructOps, TEXT("VFXEmitterRecipe"), &Z_Registration_Info_UScriptStruct_VFXEmitterRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEmitterRecipe), 1162450287U) },
		{ FVFXMaterialRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewStructOps, TEXT("VFXMaterialRecipe"), &Z_Registration_Info_UScriptStruct_VFXMaterialRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXMaterialRecipe), 115514806U) },
		{ FVFXRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewStructOps, TEXT("VFXRecipe"), &Z_Registration_Info_UScriptStruct_VFXRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXRecipe), 2144302707U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_1820785834(TEXT("/Script/VFXAgentCore"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_Statics::ScriptStructInfo),
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
