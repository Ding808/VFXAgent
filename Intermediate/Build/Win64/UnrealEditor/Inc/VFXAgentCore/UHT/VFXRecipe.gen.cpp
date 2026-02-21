// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXRecipe.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeVFXRecipe() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
UPackage* Z_Construct_UPackage__Script_VFXAgentCore();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXArchetype();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXEventType();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXForceType();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXRendererType();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXColorKey();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXCurveKey();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXCurveRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEffectSpec();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterSpec();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXEventRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXForceRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXIntent();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXLayerRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXMaterialRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXMotionBehavior();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXPatternAvoidance();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXPerSpawnInfo();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXRenderRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXRepairReport();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXTextureRecipe();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FVFXVisualHierarchy();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EVFXArchetype *************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXArchetype;
static UEnum* EVFXArchetype_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXArchetype.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXArchetype.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXArchetype, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXArchetype"));
	}
	return Z_Registration_Info_UEnum_EVFXArchetype.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXArchetype>()
{
	return EVFXArchetype_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Aura.DisplayName", "Aura" },
		{ "Aura.Name", "EVFXArchetype::Aura" },
		{ "Beam.DisplayName", "Beam" },
		{ "Beam.Name", "EVFXArchetype::Beam" },
		{ "BlueprintType", "true" },
		{ "Comment", "// ============================================================================\n// VFX INTENT LAYER - Director-level semantic understanding\n// ============================================================================\n" },
		{ "Custom.DisplayName", "Custom" },
		{ "Custom.Name", "EVFXArchetype::Custom" },
		{ "Dust.DisplayName", "Dust" },
		{ "Dust.Name", "EVFXArchetype::Dust" },
		{ "Explosion.DisplayName", "Explosion" },
		{ "Explosion.Name", "EVFXArchetype::Explosion" },
		{ "Fire.DisplayName", "Fire" },
		{ "Fire.Name", "EVFXArchetype::Fire" },
		{ "Fountain.DisplayName", "Fountain" },
		{ "Fountain.Name", "EVFXArchetype::Fountain" },
		{ "Impact.DisplayName", "Impact" },
		{ "Impact.Name", "EVFXArchetype::Impact" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "Smoke.DisplayName", "Smoke" },
		{ "Smoke.Name", "EVFXArchetype::Smoke" },
		{ "Sparks.DisplayName", "Sparks" },
		{ "Sparks.Name", "EVFXArchetype::Sparks" },
		{ "ToolTip", "VFX INTENT LAYER - Director-level semantic understanding" },
		{ "Tornado.DisplayName", "Tornado" },
		{ "Tornado.Name", "EVFXArchetype::Tornado" },
		{ "Trail.DisplayName", "Trail" },
		{ "Trail.Name", "EVFXArchetype::Trail" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXArchetype::Explosion", (int64)EVFXArchetype::Explosion },
		{ "EVFXArchetype::Tornado", (int64)EVFXArchetype::Tornado },
		{ "EVFXArchetype::Aura", (int64)EVFXArchetype::Aura },
		{ "EVFXArchetype::Trail", (int64)EVFXArchetype::Trail },
		{ "EVFXArchetype::Fountain", (int64)EVFXArchetype::Fountain },
		{ "EVFXArchetype::Beam", (int64)EVFXArchetype::Beam },
		{ "EVFXArchetype::Dust", (int64)EVFXArchetype::Dust },
		{ "EVFXArchetype::Smoke", (int64)EVFXArchetype::Smoke },
		{ "EVFXArchetype::Fire", (int64)EVFXArchetype::Fire },
		{ "EVFXArchetype::Sparks", (int64)EVFXArchetype::Sparks },
		{ "EVFXArchetype::Impact", (int64)EVFXArchetype::Impact },
		{ "EVFXArchetype::Custom", (int64)EVFXArchetype::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXArchetype",
	"EVFXArchetype",
	Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXArchetype()
{
	if (!Z_Registration_Info_UEnum_EVFXArchetype.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXArchetype.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXArchetype_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXArchetype.InnerSingleton;
}
// ********** End Enum EVFXArchetype ***************************************************************

// ********** Begin Enum EVFXMotionModel ***********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXMotionModel;
static UEnum* EVFXMotionModel_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXMotionModel.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXMotionModel.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXMotionModel"));
	}
	return Z_Registration_Info_UEnum_EVFXMotionModel.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXMotionModel>()
{
	return EVFXMotionModel_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Directional.DisplayName", "Directional (Cone/Beam)" },
		{ "Directional.Name", "EVFXMotionModel::Directional" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "Orbit.DisplayName", "Orbit (Circular Motion)" },
		{ "Orbit.Name", "EVFXMotionModel::Orbit" },
		{ "Radial.DisplayName", "Radial (Outward Explosion)" },
		{ "Radial.Name", "EVFXMotionModel::Radial" },
		{ "RadialInward.DisplayName", "Radial Inward (Vortex Attraction)" },
		{ "RadialInward.Name", "EVFXMotionModel::RadialInward" },
		{ "Static.DisplayName", "Static (Stationary)" },
		{ "Static.Name", "EVFXMotionModel::Static" },
		{ "Turbulent.DisplayName", "Turbulent (Chaotic)" },
		{ "Turbulent.Name", "EVFXMotionModel::Turbulent" },
		{ "Vertical.DisplayName", "Vertical (Upward/Downward)" },
		{ "Vertical.Name", "EVFXMotionModel::Vertical" },
		{ "Vortex.DisplayName", "Vortex (Swirling)" },
		{ "Vortex.Name", "EVFXMotionModel::Vortex" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXMotionModel::Radial", (int64)EVFXMotionModel::Radial },
		{ "EVFXMotionModel::RadialInward", (int64)EVFXMotionModel::RadialInward },
		{ "EVFXMotionModel::Orbit", (int64)EVFXMotionModel::Orbit },
		{ "EVFXMotionModel::Vortex", (int64)EVFXMotionModel::Vortex },
		{ "EVFXMotionModel::Directional", (int64)EVFXMotionModel::Directional },
		{ "EVFXMotionModel::Vertical", (int64)EVFXMotionModel::Vertical },
		{ "EVFXMotionModel::Turbulent", (int64)EVFXMotionModel::Turbulent },
		{ "EVFXMotionModel::Static", (int64)EVFXMotionModel::Static },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXMotionModel",
	"EVFXMotionModel",
	Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel()
{
	if (!Z_Registration_Info_UEnum_EVFXMotionModel.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXMotionModel.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXMotionModel.InnerSingleton;
}
// ********** End Enum EVFXMotionModel *************************************************************

// ********** Begin ScriptStruct FVFXPatternAvoidance **********************************************
struct Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXPatternAvoidance); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXPatternAvoidance); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// Behaviors that should NEVER be used for a given effect\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Behaviors that should NEVER be used for a given effect" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAvoidConeVelocity_MetaData[] = {
		{ "Category", "Avoidance" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAvoidRadialExplosion_MetaData[] = {
		{ "Category", "Avoidance" },
		{ "Comment", "// No outward cone spray\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "No outward cone spray" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAvoidUniformGravity_MetaData[] = {
		{ "Category", "Avoidance" },
		{ "Comment", "// No radial burst\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "No radial burst" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAvoidUniformRotation_MetaData[] = {
		{ "Category", "Avoidance" },
		{ "Comment", "// No downward gravity\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "No downward gravity" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAvoidHighSpread_MetaData[] = {
		{ "Category", "Avoidance" },
		{ "Comment", "// No simple spin\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "No simple spin" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXPatternAvoidance constinit property declarations **************
	static void NewProp_bAvoidConeVelocity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvoidConeVelocity;
	static void NewProp_bAvoidRadialExplosion_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvoidRadialExplosion;
	static void NewProp_bAvoidUniformGravity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvoidUniformGravity;
	static void NewProp_bAvoidUniformRotation_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvoidUniformRotation;
	static void NewProp_bAvoidHighSpread_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAvoidHighSpread;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXPatternAvoidance constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXPatternAvoidance>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance;
class UScriptStruct* FVFXPatternAvoidance::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXPatternAvoidance, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXPatternAvoidance"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXPatternAvoidance Property Definitions *************************
void Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidConeVelocity_SetBit(void* Obj)
{
	((FVFXPatternAvoidance*)Obj)->bAvoidConeVelocity = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidConeVelocity = { "bAvoidConeVelocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXPatternAvoidance), &Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidConeVelocity_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAvoidConeVelocity_MetaData), NewProp_bAvoidConeVelocity_MetaData) };
void Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidRadialExplosion_SetBit(void* Obj)
{
	((FVFXPatternAvoidance*)Obj)->bAvoidRadialExplosion = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidRadialExplosion = { "bAvoidRadialExplosion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXPatternAvoidance), &Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidRadialExplosion_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAvoidRadialExplosion_MetaData), NewProp_bAvoidRadialExplosion_MetaData) };
void Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformGravity_SetBit(void* Obj)
{
	((FVFXPatternAvoidance*)Obj)->bAvoidUniformGravity = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformGravity = { "bAvoidUniformGravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXPatternAvoidance), &Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformGravity_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAvoidUniformGravity_MetaData), NewProp_bAvoidUniformGravity_MetaData) };
void Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformRotation_SetBit(void* Obj)
{
	((FVFXPatternAvoidance*)Obj)->bAvoidUniformRotation = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformRotation = { "bAvoidUniformRotation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXPatternAvoidance), &Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformRotation_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAvoidUniformRotation_MetaData), NewProp_bAvoidUniformRotation_MetaData) };
void Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidHighSpread_SetBit(void* Obj)
{
	((FVFXPatternAvoidance*)Obj)->bAvoidHighSpread = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidHighSpread = { "bAvoidHighSpread", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXPatternAvoidance), &Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidHighSpread_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAvoidHighSpread_MetaData), NewProp_bAvoidHighSpread_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidConeVelocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidRadialExplosion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformGravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidUniformRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewProp_bAvoidHighSpread,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXPatternAvoidance Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXPatternAvoidance",
	Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::PropPointers),
	sizeof(FVFXPatternAvoidance),
	alignof(FVFXPatternAvoidance),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXPatternAvoidance()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance.InnerSingleton, Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance.InnerSingleton);
}
// ********** End ScriptStruct FVFXPatternAvoidance ************************************************

// ********** Begin ScriptStruct FVFXMotionBehavior ************************************************
struct Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXMotionBehavior); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXMotionBehavior); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// Motion behavior definition for directing Niagara composition\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Motion behavior definition for directing Niagara composition" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryModel_MetaData[] = {
		{ "Category", "Motion" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MotionAxis_MetaData[] = {
		{ "Category", "Motion" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRadiusDependsOnHeight_MetaData[] = {
		{ "Category", "Motion" },
		{ "Comment", "// For orbit/vortex\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "For orbit/vortex" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bAngularVelocityIncreases_MetaData[] = {
		{ "Category", "Motion" },
		{ "Comment", "// Funnel effect\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Funnel effect" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCentripetal_MetaData[] = {
		{ "Category", "Motion" },
		{ "Comment", "// Faster at top\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Faster at top" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CentripetalStrength_MetaData[] = {
		{ "Category", "Motion" },
		{ "Comment", "// Attract to center\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Attract to center" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHeightDriven_MetaData[] = {
		{ "Category", "Motion" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXMotionBehavior constinit property declarations ****************
	static const UECodeGen_Private::FBytePropertyParams NewProp_PrimaryModel_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_PrimaryModel;
	static const UECodeGen_Private::FStructPropertyParams NewProp_MotionAxis;
	static void NewProp_bRadiusDependsOnHeight_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRadiusDependsOnHeight;
	static void NewProp_bAngularVelocityIncreases_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bAngularVelocityIncreases;
	static void NewProp_bCentripetal_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCentripetal;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CentripetalStrength;
	static void NewProp_bHeightDriven_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHeightDriven;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXMotionBehavior constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXMotionBehavior>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXMotionBehavior;
class UScriptStruct* FVFXMotionBehavior::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXMotionBehavior.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXMotionBehavior.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXMotionBehavior, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXMotionBehavior"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXMotionBehavior.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXMotionBehavior Property Definitions ***************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_PrimaryModel_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_PrimaryModel = { "PrimaryModel", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMotionBehavior, PrimaryModel), Z_Construct_UEnum_VFXAgentCore_EVFXMotionModel, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrimaryModel_MetaData), NewProp_PrimaryModel_MetaData) }; // 3479131074
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_MotionAxis = { "MotionAxis", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMotionBehavior, MotionAxis), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MotionAxis_MetaData), NewProp_MotionAxis_MetaData) };
void Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bRadiusDependsOnHeight_SetBit(void* Obj)
{
	((FVFXMotionBehavior*)Obj)->bRadiusDependsOnHeight = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bRadiusDependsOnHeight = { "bRadiusDependsOnHeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXMotionBehavior), &Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bRadiusDependsOnHeight_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRadiusDependsOnHeight_MetaData), NewProp_bRadiusDependsOnHeight_MetaData) };
void Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bAngularVelocityIncreases_SetBit(void* Obj)
{
	((FVFXMotionBehavior*)Obj)->bAngularVelocityIncreases = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bAngularVelocityIncreases = { "bAngularVelocityIncreases", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXMotionBehavior), &Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bAngularVelocityIncreases_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bAngularVelocityIncreases_MetaData), NewProp_bAngularVelocityIncreases_MetaData) };
void Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bCentripetal_SetBit(void* Obj)
{
	((FVFXMotionBehavior*)Obj)->bCentripetal = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bCentripetal = { "bCentripetal", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXMotionBehavior), &Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bCentripetal_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCentripetal_MetaData), NewProp_bCentripetal_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_CentripetalStrength = { "CentripetalStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMotionBehavior, CentripetalStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CentripetalStrength_MetaData), NewProp_CentripetalStrength_MetaData) };
void Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bHeightDriven_SetBit(void* Obj)
{
	((FVFXMotionBehavior*)Obj)->bHeightDriven = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bHeightDriven = { "bHeightDriven", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXMotionBehavior), &Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bHeightDriven_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHeightDriven_MetaData), NewProp_bHeightDriven_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_PrimaryModel_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_PrimaryModel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_MotionAxis,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bRadiusDependsOnHeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bAngularVelocityIncreases,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bCentripetal,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_CentripetalStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewProp_bHeightDriven,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXMotionBehavior Property Definitions *****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXMotionBehavior",
	Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::PropPointers),
	sizeof(FVFXMotionBehavior),
	alignof(FVFXMotionBehavior),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXMotionBehavior()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXMotionBehavior.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXMotionBehavior.InnerSingleton, Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXMotionBehavior.InnerSingleton);
}
// ********** End ScriptStruct FVFXMotionBehavior **************************************************

// ********** Begin ScriptStruct FVFXVisualHierarchy ***********************************************
struct Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXVisualHierarchy); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXVisualHierarchy); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// Visual hierarchy - what is dominant and secondary\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Visual hierarchy - what is dominant and secondary" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DominantElement_MetaData[] = {
		{ "Category", "Hierarchy" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DominantWeight_MetaData[] = {
		{ "Category", "Hierarchy" },
		{ "Comment", "// Main visual (e.g., \"core_funnel\")\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Main visual (e.g., \"core_funnel\")" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SecondaryElements_MetaData[] = {
		{ "Category", "Hierarchy" },
		{ "Comment", "// Visual priority (0-1)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Visual priority (0-1)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SecondaryWeights_MetaData[] = {
		{ "Category", "Hierarchy" },
		{ "Comment", "// Supporting visuals\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Supporting visuals" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXVisualHierarchy constinit property declarations ***************
	static const UECodeGen_Private::FStrPropertyParams NewProp_DominantElement;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DominantWeight;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SecondaryElements_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SecondaryElements;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SecondaryWeights_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SecondaryWeights;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXVisualHierarchy constinit property declarations *****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXVisualHierarchy>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy;
class UScriptStruct* FVFXVisualHierarchy::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXVisualHierarchy, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXVisualHierarchy"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXVisualHierarchy Property Definitions **************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_DominantElement = { "DominantElement", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXVisualHierarchy, DominantElement), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DominantElement_MetaData), NewProp_DominantElement_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_DominantWeight = { "DominantWeight", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXVisualHierarchy, DominantWeight), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DominantWeight_MetaData), NewProp_DominantWeight_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryElements_Inner = { "SecondaryElements", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryElements = { "SecondaryElements", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXVisualHierarchy, SecondaryElements), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SecondaryElements_MetaData), NewProp_SecondaryElements_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryWeights_Inner = { "SecondaryWeights", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryWeights = { "SecondaryWeights", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXVisualHierarchy, SecondaryWeights), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SecondaryWeights_MetaData), NewProp_SecondaryWeights_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_DominantElement,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_DominantWeight,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryElements_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryElements,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryWeights_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewProp_SecondaryWeights,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXVisualHierarchy Property Definitions ****************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXVisualHierarchy",
	Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::PropPointers),
	sizeof(FVFXVisualHierarchy),
	alignof(FVFXVisualHierarchy),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXVisualHierarchy()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy.InnerSingleton, Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy.InnerSingleton);
}
// ********** End ScriptStruct FVFXVisualHierarchy *************************************************

// ********** Begin ScriptStruct FVFXIntent ********************************************************
struct Z_Construct_UScriptStruct_FVFXIntent_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXIntent); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXIntent); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// The VFX Intent - Director's understanding BEFORE generating Niagara\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "The VFX Intent - Director's understanding BEFORE generating Niagara" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Archetype_MetaData[] = {
		{ "Category", "Intent" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Motion_MetaData[] = {
		{ "Category", "Intent" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Hierarchy_MetaData[] = {
		{ "Category", "Intent" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Avoidance_MetaData[] = {
		{ "Category", "Intent" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequiredLayers_MetaData[] = {
		{ "Category", "Intent" },
		{ "Comment", "// Required effect layers (names like \"core_funnel\", \"debris\", \"dust\")\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Required effect layers (names like \"core_funnel\", \"debris\", \"dust\")" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RequiredForces_MetaData[] = {
		{ "Category", "Intent" },
		{ "Comment", "// Key physics behaviors needed\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Key physics behaviors needed" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SuggestedEmitterCount_MetaData[] = {
		{ "Category", "Intent" },
		{ "Comment", "// How many emitters needed\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "How many emitters needed" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Intent" },
		{ "Comment", "// Semantic description for logging\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Semantic description for logging" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXIntent constinit property declarations ************************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Archetype_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Archetype;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Motion;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Hierarchy;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Avoidance;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RequiredLayers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RequiredLayers;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RequiredForces_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_RequiredForces;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SuggestedEmitterCount;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXIntent constinit property declarations **************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXIntent>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXIntent_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXIntent;
class UScriptStruct* FVFXIntent::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXIntent.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXIntent.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXIntent, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXIntent"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXIntent.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXIntent Property Definitions ***********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Archetype_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Archetype = { "Archetype", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, Archetype), Z_Construct_UEnum_VFXAgentCore_EVFXArchetype, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Archetype_MetaData), NewProp_Archetype_MetaData) }; // 1239467032
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Motion = { "Motion", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, Motion), Z_Construct_UScriptStruct_FVFXMotionBehavior, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Motion_MetaData), NewProp_Motion_MetaData) }; // 2776603170
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Hierarchy = { "Hierarchy", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, Hierarchy), Z_Construct_UScriptStruct_FVFXVisualHierarchy, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Hierarchy_MetaData), NewProp_Hierarchy_MetaData) }; // 2224825837
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Avoidance = { "Avoidance", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, Avoidance), Z_Construct_UScriptStruct_FVFXPatternAvoidance, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Avoidance_MetaData), NewProp_Avoidance_MetaData) }; // 3180674912
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredLayers_Inner = { "RequiredLayers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredLayers = { "RequiredLayers", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, RequiredLayers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequiredLayers_MetaData), NewProp_RequiredLayers_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredForces_Inner = { "RequiredForces", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredForces = { "RequiredForces", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, RequiredForces), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RequiredForces_MetaData), NewProp_RequiredForces_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_SuggestedEmitterCount = { "SuggestedEmitterCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, SuggestedEmitterCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SuggestedEmitterCount_MetaData), NewProp_SuggestedEmitterCount_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXIntent, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXIntent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Archetype_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Archetype,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Motion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Hierarchy,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Avoidance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredLayers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredLayers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredForces_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_RequiredForces,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_SuggestedEmitterCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXIntent_Statics::NewProp_Description,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXIntent_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXIntent Property Definitions *************************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXIntent_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXIntent",
	Z_Construct_UScriptStruct_FVFXIntent_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXIntent_Statics::PropPointers),
	sizeof(FVFXIntent),
	alignof(FVFXIntent),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXIntent_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXIntent_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXIntent()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXIntent.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXIntent.InnerSingleton, Z_Construct_UScriptStruct_FVFXIntent_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXIntent.InnerSingleton);
}
// ********** End ScriptStruct FVFXIntent **********************************************************

// ********** Begin ScriptStruct FVFXEmitterRecipe *************************************************
struct Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXEmitterRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXEmitterRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// ============================================================================\n// RECIPE STRUCTURES (Niagara-level compilation targets)\n// ============================================================================\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "RECIPE STRUCTURES (Niagara-level compilation targets)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "Emitter" },
		{ "Comment", "// Optional human-readable layer name/purpose (e.g. \"CoreBurst\", \"Sparks\", \"Smoke\", \"Shockwave\").\n// Used for naming within the generated Niagara System.\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Optional human-readable layer name/purpose (e.g. \"CoreBurst\", \"Sparks\", \"Smoke\", \"Shockwave\").\nUsed for naming within the generated Niagara System." },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnRate_MetaData[] = {
		{ "Category", "Spawn" },
		{ "Comment", "// === Spawn Parameters ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Spawn Parameters ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstCount_MetaData[] = {
		{ "Category", "Spawn" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstTime_MetaData[] = {
		{ "Category", "Spawn" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RendererType_MetaData[] = {
		{ "Category", "Renderer" },
		{ "Comment", "// === Renderer ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Renderer ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TemplateName_MetaData[] = {
		{ "Category", "Emitter" },
		{ "Comment", "// New: Specify a preferred Niagara template to base this emitter on.\n// Examples: \"Fountain\", \"DirectionalBurst\", \"HangingParticulates\", \"OmnidirectionalBurst\", \"UpwardMeshBurst\", \"Beam\"\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "New: Specify a preferred Niagara template to base this emitter on.\nExamples: \"Fountain\", \"DirectionalBurst\", \"HangingParticulates\", \"OmnidirectionalBurst\", \"UpwardMeshBurst\", \"Beam\"" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "Color" },
		{ "Comment", "// === Color & Appearance ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Color & Appearance ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorEnd_MetaData[] = {
		{ "Category", "Color" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseColorGradient_MetaData[] = {
		{ "Category", "Color" },
		{ "Comment", "// Color at end of lifetime (for gradient)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Color at end of lifetime (for gradient)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "Category", "Lifetime" },
		{ "Comment", "// === Lifetime & Size ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Lifetime & Size ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifetimeVariation_MetaData[] = {
		{ "Category", "Lifetime" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Size_MetaData[] = {
		{ "Category", "Size" },
		{ "Comment", "// Random variation (0-1, multiplier)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Random variation (0-1, multiplier)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeEnd_MetaData[] = {
		{ "Category", "Size" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseSizeOverLife_MetaData[] = {
		{ "Category", "Size" },
		{ "Comment", "// Size at end of lifetime\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Size at end of lifetime" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeVariation_MetaData[] = {
		{ "Category", "Size" },
		{ "Comment", "// Scale from Size to SizeEnd\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Scale from Size to SizeEnd" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "Category", "Velocity" },
		{ "Comment", "// === Velocity & Movement ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Velocity & Movement ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VelocityVariation_MetaData[] = {
		{ "Category", "Velocity" },
		{ "Comment", "// Initial velocity\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Initial velocity" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Acceleration_MetaData[] = {
		{ "Category", "Velocity" },
		{ "Comment", "// Random velocity variation (0-1, multiplier)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Random velocity variation (0-1, multiplier)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Drag_MetaData[] = {
		{ "Category", "Velocity" },
		{ "Comment", "// Gravity or constant acceleration\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Gravity or constant acceleration" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialRotation_MetaData[] = {
		{ "Category", "Rotation" },
		{ "Comment", "// === Rotation ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Rotation ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotationRate_MetaData[] = {
		{ "Category", "Rotation" },
		{ "Comment", "// Initial rotation in degrees\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Initial rotation in degrees" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotationRateVariation_MetaData[] = {
		{ "Category", "Rotation" },
		{ "Comment", "// Rotation speed in degrees/second\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Rotation speed in degrees/second" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseGravity_MetaData[] = {
		{ "Category", "Physics" },
		{ "Comment", "// === Physics & Forces ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Physics & Forces ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mass_MetaData[] = {
		{ "Category", "Physics" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmitShape_MetaData[] = {
		{ "Category", "Shape" },
		{ "Comment", "// === Emitter Shape ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Emitter Shape ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShapeSize_MetaData[] = {
		{ "Category", "Shape" },
		{ "Comment", "// Point, Sphere, Box, Cone, Cylinder\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Point, Sphere, Box, Cone, Cylinder" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaterialIndex_MetaData[] = {
		{ "Category", "Material" },
		{ "Comment", "// === Material Assignment ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Material Assignment ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SortOrder_MetaData[] = {
		{ "Category", "Rendering" },
		{ "Comment", "// === Sorting & Rendering ===\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "=== Sorting & Rendering ===" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLocalSpace_MetaData[] = {
		{ "Category", "Rendering" },
		{ "Comment", "// Higher values render later (on top)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Higher values render later (on top)" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXEmitterRecipe constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpawnRate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BurstCount;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BurstTime;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TemplateName;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ColorEnd;
	static void NewProp_bUseColorGradient_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseColorGradient;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LifetimeVariation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Size;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SizeEnd;
	static void NewProp_bUseSizeOverLife_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseSizeOverLife;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SizeVariation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VelocityVariation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Acceleration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Drag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RotationRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RotationRateVariation;
	static void NewProp_bUseGravity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseGravity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Mass;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EmitShape;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ShapeSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaterialIndex;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SortOrder;
	static void NewProp_bLocalSpace_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLocalSpace;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXEmitterRecipe constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEmitterRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe;
class UScriptStruct* FVFXEmitterRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXEmitterRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXEmitterRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXEmitterRecipe Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SpawnRate = { "SpawnRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, SpawnRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnRate_MetaData), NewProp_SpawnRate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstCount = { "BurstCount", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, BurstCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstCount_MetaData), NewProp_BurstCount_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstTime = { "BurstTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, BurstTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstTime_MetaData), NewProp_BurstTime_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, RendererType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_TemplateName = { "TemplateName", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, TemplateName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemplateName_MetaData), NewProp_TemplateName_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_ColorEnd = { "ColorEnd", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, ColorEnd), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorEnd_MetaData), NewProp_ColorEnd_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseColorGradient_SetBit(void* Obj)
{
	((FVFXEmitterRecipe*)Obj)->bUseColorGradient = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseColorGradient = { "bUseColorGradient", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterRecipe), &Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseColorGradient_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseColorGradient_MetaData), NewProp_bUseColorGradient_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_LifetimeVariation = { "LifetimeVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, LifetimeVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifetimeVariation_MetaData), NewProp_LifetimeVariation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Size), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Size_MetaData), NewProp_Size_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SizeEnd = { "SizeEnd", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, SizeEnd), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeEnd_MetaData), NewProp_SizeEnd_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseSizeOverLife_SetBit(void* Obj)
{
	((FVFXEmitterRecipe*)Obj)->bUseSizeOverLife = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseSizeOverLife = { "bUseSizeOverLife", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterRecipe), &Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseSizeOverLife_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseSizeOverLife_MetaData), NewProp_bUseSizeOverLife_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SizeVariation = { "SizeVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, SizeVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeVariation_MetaData), NewProp_SizeVariation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_VelocityVariation = { "VelocityVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, VelocityVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VelocityVariation_MetaData), NewProp_VelocityVariation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Acceleration = { "Acceleration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Acceleration), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Acceleration_MetaData), NewProp_Acceleration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Drag = { "Drag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Drag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Drag_MetaData), NewProp_Drag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_InitialRotation = { "InitialRotation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, InitialRotation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialRotation_MetaData), NewProp_InitialRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RotationRate = { "RotationRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, RotationRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotationRate_MetaData), NewProp_RotationRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RotationRateVariation = { "RotationRateVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, RotationRateVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotationRateVariation_MetaData), NewProp_RotationRateVariation_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseGravity_SetBit(void* Obj)
{
	((FVFXEmitterRecipe*)Obj)->bUseGravity = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseGravity = { "bUseGravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterRecipe), &Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseGravity_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseGravity_MetaData), NewProp_bUseGravity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Mass = { "Mass", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, Mass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mass_MetaData), NewProp_Mass_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_EmitShape = { "EmitShape", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, EmitShape), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmitShape_MetaData), NewProp_EmitShape_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_ShapeSize = { "ShapeSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, ShapeSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShapeSize_MetaData), NewProp_ShapeSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_MaterialIndex = { "MaterialIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, MaterialIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaterialIndex_MetaData), NewProp_MaterialIndex_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SortOrder = { "SortOrder", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterRecipe, SortOrder), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SortOrder_MetaData), NewProp_SortOrder_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bLocalSpace_SetBit(void* Obj)
{
	((FVFXEmitterRecipe*)Obj)->bLocalSpace = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bLocalSpace = { "bLocalSpace", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterRecipe), &Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bLocalSpace_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLocalSpace_MetaData), NewProp_bLocalSpace_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SpawnRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstCount,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_BurstTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_TemplateName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_ColorEnd,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseColorGradient,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Lifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_LifetimeVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Size,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SizeEnd,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseSizeOverLife,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SizeVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_VelocityVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Acceleration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Drag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_InitialRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RotationRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_RotationRateVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bUseGravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_Mass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_EmitShape,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_ShapeSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_MaterialIndex,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_SortOrder,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewProp_bLocalSpace,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXEmitterRecipe Property Definitions ******************************
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
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXEmitterRecipe ***************************************************

// ********** Begin ScriptStruct FVFXTextureRecipe *************************************************
struct Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXTextureRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXTextureRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "Texture" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "Category", "Texture" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryColor_MetaData[] = {
		{ "Category", "Texture" },
		{ "Comment", "// Gradient, Noise, Perlin, Voronoi, Custom\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Gradient, Noise, Perlin, Voronoi, Custom" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SecondaryColor_MetaData[] = {
		{ "Category", "Texture" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Resolution_MetaData[] = {
		{ "Category", "Texture" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseScale_MetaData[] = {
		{ "Category", "Texture" },
		{ "Comment", "// Texture resolution (256, 512, 1024, etc.)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Texture resolution (256, 512, 1024, etc.)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Octaves_MetaData[] = {
		{ "Category", "Texture" },
		{ "Comment", "// For noise-based textures\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "For noise-based textures" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Category", "Texture" },
		{ "Comment", "// For fractal noise\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "For fractal noise" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXTextureRecipe constinit property declarations *****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Type;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PrimaryColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SecondaryColor;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Resolution;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseScale;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Octaves;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXTextureRecipe constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXTextureRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXTextureRecipe;
class UScriptStruct* FVFXTextureRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXTextureRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXTextureRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXTextureRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXTextureRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXTextureRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXTextureRecipe Property Definitions ****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, Type), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_PrimaryColor = { "PrimaryColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, PrimaryColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrimaryColor_MetaData), NewProp_PrimaryColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_SecondaryColor = { "SecondaryColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, SecondaryColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SecondaryColor_MetaData), NewProp_SecondaryColor_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Resolution = { "Resolution", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, Resolution), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Resolution_MetaData), NewProp_Resolution_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_NoiseScale = { "NoiseScale", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, NoiseScale), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseScale_MetaData), NewProp_NoiseScale_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Octaves = { "Octaves", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, Octaves), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Octaves_MetaData), NewProp_Octaves_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXTextureRecipe, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_PrimaryColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_SecondaryColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Resolution,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_NoiseScale,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Octaves,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewProp_Description,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXTextureRecipe Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXTextureRecipe",
	Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::PropPointers),
	sizeof(FVFXTextureRecipe),
	alignof(FVFXTextureRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXTextureRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXTextureRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXTextureRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXTextureRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXTextureRecipe ***************************************************

// ********** Begin ScriptStruct FVFXMaterialRecipe ************************************************
struct Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXMaterialRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXMaterialRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "Material" },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bIsUnlit_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseMaterialPath_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseColor_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmissiveColor_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmissiveStrength_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Opacity_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Roughness_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Metallic_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseColorTexture_MetaData[] = {
		{ "Category", "Material" },
		{ "Comment", "// Textures to use (can reference generated textures)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Textures to use (can reference generated textures)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmissiveTexture_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OpacityTexture_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NormalTexture_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GeneratedTextures_MetaData[] = {
		{ "Category", "Material" },
		{ "Comment", "// Auto-generate textures based on these recipes\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Auto-generate textures based on these recipes" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXMaterialRecipe constinit property declarations ****************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static void NewProp_bIsAdditive_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsAdditive;
	static void NewProp_bIsUnlit_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsUnlit;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BaseMaterialPath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BaseColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_EmissiveColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EmissiveStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Opacity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Roughness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Metallic;
	static const UECodeGen_Private::FStrPropertyParams NewProp_BaseColorTexture;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EmissiveTexture;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OpacityTexture;
	static const UECodeGen_Private::FStrPropertyParams NewProp_NormalTexture;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GeneratedTextures_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_GeneratedTextures;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXMaterialRecipe constinit property declarations ******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXMaterialRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe;
class UScriptStruct* FVFXMaterialRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXMaterialRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXMaterialRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXMaterialRecipe Property Definitions ***************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
void Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive_SetBit(void* Obj)
{
	((FVFXMaterialRecipe*)Obj)->bIsAdditive = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive = { "bIsAdditive", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXMaterialRecipe), &Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsAdditive_MetaData), NewProp_bIsAdditive_MetaData) };
void Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsUnlit_SetBit(void* Obj)
{
	((FVFXMaterialRecipe*)Obj)->bIsUnlit = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsUnlit = { "bIsUnlit", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXMaterialRecipe), &Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsUnlit_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bIsUnlit_MetaData), NewProp_bIsUnlit_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseMaterialPath = { "BaseMaterialPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, BaseMaterialPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseMaterialPath_MetaData), NewProp_BaseMaterialPath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseColor = { "BaseColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, BaseColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseColor_MetaData), NewProp_BaseColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_EmissiveColor = { "EmissiveColor", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, EmissiveColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmissiveColor_MetaData), NewProp_EmissiveColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_EmissiveStrength = { "EmissiveStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, EmissiveStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmissiveStrength_MetaData), NewProp_EmissiveStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Opacity = { "Opacity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, Opacity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Opacity_MetaData), NewProp_Opacity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Roughness = { "Roughness", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, Roughness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Roughness_MetaData), NewProp_Roughness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Metallic = { "Metallic", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, Metallic), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Metallic_MetaData), NewProp_Metallic_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseColorTexture = { "BaseColorTexture", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, BaseColorTexture), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseColorTexture_MetaData), NewProp_BaseColorTexture_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_EmissiveTexture = { "EmissiveTexture", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, EmissiveTexture), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmissiveTexture_MetaData), NewProp_EmissiveTexture_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_OpacityTexture = { "OpacityTexture", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, OpacityTexture), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OpacityTexture_MetaData), NewProp_OpacityTexture_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_NormalTexture = { "NormalTexture", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, NormalTexture), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NormalTexture_MetaData), NewProp_NormalTexture_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_GeneratedTextures_Inner = { "GeneratedTextures", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXTextureRecipe, METADATA_PARAMS(0, nullptr) }; // 1708579409
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_GeneratedTextures = { "GeneratedTextures", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXMaterialRecipe, GeneratedTextures), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GeneratedTextures_MetaData), NewProp_GeneratedTextures_MetaData) }; // 1708579409
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Description,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsAdditive,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_bIsUnlit,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseMaterialPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_EmissiveColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_EmissiveStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Opacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Roughness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_Metallic,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_BaseColorTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_EmissiveTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_OpacityTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_NormalTexture,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_GeneratedTextures_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewProp_GeneratedTextures,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXMaterialRecipe Property Definitions *****************************
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
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXMaterialRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXMaterialRecipe **************************************************

// ********** Begin Enum EVFXRendererType **********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXRendererType;
static UEnum* EVFXRendererType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXRendererType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXRendererType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXRendererType, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXRendererType"));
	}
	return Z_Registration_Info_UEnum_EVFXRendererType.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXRendererType>()
{
	return EVFXRendererType_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "// --- New Schema for Niagara Spec ---\n" },
		{ "Light.DisplayName", "Light" },
		{ "Light.Name", "EVFXRendererType::Light" },
		{ "Mesh.DisplayName", "Mesh" },
		{ "Mesh.Name", "EVFXRendererType::Mesh" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "Ribbon.DisplayName", "Ribbon" },
		{ "Ribbon.Name", "EVFXRendererType::Ribbon" },
		{ "Sprite.DisplayName", "Sprite" },
		{ "Sprite.Name", "EVFXRendererType::Sprite" },
		{ "ToolTip", "--- New Schema for Niagara Spec ---" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXRendererType::Sprite", (int64)EVFXRendererType::Sprite },
		{ "EVFXRendererType::Ribbon", (int64)EVFXRendererType::Ribbon },
		{ "EVFXRendererType::Mesh", (int64)EVFXRendererType::Mesh },
		{ "EVFXRendererType::Light", (int64)EVFXRendererType::Light },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXRendererType_Statics 
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
// ********** End Enum EVFXRendererType ************************************************************

// ********** Begin ScriptStruct FVFXPerSpawnInfo **************************************************
struct Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXPerSpawnInfo); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXPerSpawnInfo); }
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
		{ "Comment", "// If > 0, use SpawnRate\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "If > 0, use SpawnRate" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstTime_MetaData[] = {
		{ "Category", "Spawn" },
		{ "Comment", "// If > 0, use Burst\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "If > 0, use Burst" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXPerSpawnInfo constinit property declarations ******************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Burst;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BurstTime;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXPerSpawnInfo constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXPerSpawnInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo;
class UScriptStruct* FVFXPerSpawnInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXPerSpawnInfo, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXPerSpawnInfo"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXPerSpawnInfo Property Definitions *****************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Rate = { "Rate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPerSpawnInfo, Rate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rate_MetaData), NewProp_Rate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Burst = { "Burst", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPerSpawnInfo, Burst), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Burst_MetaData), NewProp_Burst_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_BurstTime = { "BurstTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXPerSpawnInfo, BurstTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstTime_MetaData), NewProp_BurstTime_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Rate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_Burst,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewProp_BurstTime,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXPerSpawnInfo Property Definitions *******************************
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
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXPerSpawnInfo()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo.InnerSingleton, Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo.InnerSingleton);
}
// ********** End ScriptStruct FVFXPerSpawnInfo ****************************************************

// ********** Begin Enum EVFXForceType *************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXForceType;
static UEnum* EVFXForceType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXForceType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXForceType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXForceType, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXForceType"));
	}
	return Z_Registration_Info_UEnum_EVFXForceType.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXForceType>()
{
	return EVFXForceType_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "CurlNoise.DisplayName", "CurlNoise" },
		{ "CurlNoise.Name", "EVFXForceType::CurlNoise" },
		{ "Drag.DisplayName", "Drag" },
		{ "Drag.Name", "EVFXForceType::Drag" },
		{ "Gravity.DisplayName", "Gravity" },
		{ "Gravity.Name", "EVFXForceType::Gravity" },
		{ "Lift.DisplayName", "Lift" },
		{ "Lift.Name", "EVFXForceType::Lift" },
		{ "LimitVelocity.DisplayName", "LimitVelocity" },
		{ "LimitVelocity.Name", "EVFXForceType::LimitVelocity" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "Noise.DisplayName", "Noise" },
		{ "Noise.Name", "EVFXForceType::Noise" },
		{ "Vortex.DisplayName", "Vortex" },
		{ "Vortex.Name", "EVFXForceType::Vortex" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXForceType::CurlNoise", (int64)EVFXForceType::CurlNoise },
		{ "EVFXForceType::Noise", (int64)EVFXForceType::Noise },
		{ "EVFXForceType::Drag", (int64)EVFXForceType::Drag },
		{ "EVFXForceType::Gravity", (int64)EVFXForceType::Gravity },
		{ "EVFXForceType::Vortex", (int64)EVFXForceType::Vortex },
		{ "EVFXForceType::Lift", (int64)EVFXForceType::Lift },
		{ "EVFXForceType::LimitVelocity", (int64)EVFXForceType::LimitVelocity },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXForceType",
	"EVFXForceType",
	Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXForceType()
{
	if (!Z_Registration_Info_UEnum_EVFXForceType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXForceType.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXForceType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXForceType.InnerSingleton;
}
// ********** End Enum EVFXForceType ***************************************************************

// ********** Begin ScriptStruct FVFXCurveKey ******************************************************
struct Z_Construct_UScriptStruct_FVFXCurveKey_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXCurveKey); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXCurveKey); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[] = {
		{ "Category", "Curve" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Value_MetaData[] = {
		{ "Category", "Curve" },
		{ "Comment", "// 0-1\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "0-1" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXCurveKey constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Value;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXCurveKey constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXCurveKey>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXCurveKey_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXCurveKey;
class UScriptStruct* FVFXCurveKey::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXCurveKey.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXCurveKey.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXCurveKey, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXCurveKey"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXCurveKey.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXCurveKey Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXCurveKey_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurveKey, Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Time_MetaData), NewProp_Time_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXCurveKey_Statics::NewProp_Value = { "Value", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurveKey, Value), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Value_MetaData), NewProp_Value_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXCurveKey_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveKey_Statics::NewProp_Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveKey_Statics::NewProp_Value,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurveKey_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXCurveKey Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXCurveKey_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXCurveKey",
	Z_Construct_UScriptStruct_FVFXCurveKey_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurveKey_Statics::PropPointers),
	sizeof(FVFXCurveKey),
	alignof(FVFXCurveKey),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurveKey_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXCurveKey_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXCurveKey()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXCurveKey.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXCurveKey.InnerSingleton, Z_Construct_UScriptStruct_FVFXCurveKey_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXCurveKey.InnerSingleton);
}
// ********** End ScriptStruct FVFXCurveKey ********************************************************

// ********** Begin ScriptStruct FVFXColorKey ******************************************************
struct Z_Construct_UScriptStruct_FVFXColorKey_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXColorKey); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXColorKey); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Time_MetaData[] = {
		{ "Category", "Curve" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "Curve" },
		{ "Comment", "// 0-1\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "0-1" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXColorKey constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Time;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXColorKey constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXColorKey>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXColorKey_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXColorKey;
class UScriptStruct* FVFXColorKey::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXColorKey.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXColorKey.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXColorKey, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXColorKey"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXColorKey.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXColorKey Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXColorKey_Statics::NewProp_Time = { "Time", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXColorKey, Time), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Time_MetaData), NewProp_Time_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXColorKey_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXColorKey, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXColorKey_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXColorKey_Statics::NewProp_Time,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXColorKey_Statics::NewProp_Color,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXColorKey_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXColorKey Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXColorKey_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXColorKey",
	Z_Construct_UScriptStruct_FVFXColorKey_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXColorKey_Statics::PropPointers),
	sizeof(FVFXColorKey),
	alignof(FVFXColorKey),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXColorKey_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXColorKey_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXColorKey()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXColorKey.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXColorKey.InnerSingleton, Z_Construct_UScriptStruct_FVFXColorKey_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXColorKey.InnerSingleton);
}
// ********** End ScriptStruct FVFXColorKey ********************************************************

// ********** Begin ScriptStruct FVFXCurveRecipe ***************************************************
struct Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXCurveRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXCurveRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Size_MetaData[] = {
		{ "Category", "Curve" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Alpha_MetaData[] = {
		{ "Category", "Curve" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "Curve" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXCurveRecipe constinit property declarations *******************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Size_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Size;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Alpha_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Alpha;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Color;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXCurveRecipe constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXCurveRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXCurveRecipe;
class UScriptStruct* FVFXCurveRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXCurveRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXCurveRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXCurveRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXCurveRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXCurveRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXCurveRecipe Property Definitions ******************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Size_Inner = { "Size", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXCurveKey, METADATA_PARAMS(0, nullptr) }; // 2538690331
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurveRecipe, Size), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Size_MetaData), NewProp_Size_MetaData) }; // 2538690331
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Alpha_Inner = { "Alpha", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXCurveKey, METADATA_PARAMS(0, nullptr) }; // 2538690331
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Alpha = { "Alpha", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurveRecipe, Alpha), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Alpha_MetaData), NewProp_Alpha_MetaData) }; // 2538690331
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Color_Inner = { "Color", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXColorKey, METADATA_PARAMS(0, nullptr) }; // 1576140641
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXCurveRecipe, Color), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) }; // 1576140641
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Size_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Size,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Alpha_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Alpha,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Color_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewProp_Color,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXCurveRecipe Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXCurveRecipe",
	Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::PropPointers),
	sizeof(FVFXCurveRecipe),
	alignof(FVFXCurveRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXCurveRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXCurveRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXCurveRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXCurveRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXCurveRecipe *****************************************************

// ********** Begin ScriptStruct FVFXForceRecipe ***************************************************
struct Z_Construct_UScriptStruct_FVFXForceRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXForceRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXForceRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "Category", "Force" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Strength_MetaData[] = {
		{ "Category", "Force" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Frequency_MetaData[] = {
		{ "Category", "Force" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Direction_MetaData[] = {
		{ "Category", "Force" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Radius_MetaData[] = {
		{ "Category", "Force" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxVelocity_MetaData[] = {
		{ "Category", "Force" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bEnabled_MetaData[] = {
		{ "Category", "Force" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXForceRecipe constinit property declarations *******************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Strength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Frequency;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Direction;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Radius;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MaxVelocity;
	static void NewProp_bEnabled_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bEnabled;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXForceRecipe constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXForceRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXForceRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXForceRecipe;
class UScriptStruct* FVFXForceRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXForceRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXForceRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXForceRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXForceRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXForceRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXForceRecipe Property Definitions ******************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXForceRecipe, Type), Z_Construct_UEnum_VFXAgentCore_EVFXForceType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 644312078
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Strength = { "Strength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXForceRecipe, Strength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Strength_MetaData), NewProp_Strength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Frequency = { "Frequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXForceRecipe, Frequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Frequency_MetaData), NewProp_Frequency_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Direction = { "Direction", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXForceRecipe, Direction), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Direction_MetaData), NewProp_Direction_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Radius = { "Radius", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXForceRecipe, Radius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Radius_MetaData), NewProp_Radius_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_MaxVelocity = { "MaxVelocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXForceRecipe, MaxVelocity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxVelocity_MetaData), NewProp_MaxVelocity_MetaData) };
void Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_bEnabled_SetBit(void* Obj)
{
	((FVFXForceRecipe*)Obj)->bEnabled = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_bEnabled = { "bEnabled", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXForceRecipe), &Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_bEnabled_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bEnabled_MetaData), NewProp_bEnabled_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Strength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Frequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Direction,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_Radius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_MaxVelocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewProp_bEnabled,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXForceRecipe Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXForceRecipe",
	Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::PropPointers),
	sizeof(FVFXForceRecipe),
	alignof(FVFXForceRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXForceRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXForceRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXForceRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXForceRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXForceRecipe *****************************************************

// ********** Begin ScriptStruct FVFXRenderRecipe **************************************************
struct Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXRenderRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXRenderRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RendererType_MetaData[] = {
		{ "Category", "Render" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FacingMode_MetaData[] = {
		{ "Category", "Render" },
		{ "Comment", "// Sprite, Mesh, Ribbon, Light\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Sprite, Mesh, Ribbon, Light" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Alignment_MetaData[] = {
		{ "Category", "Render" },
		{ "Comment", "// Camera, Velocity, Custom\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Camera, Velocity, Custom" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bSoftParticles_MetaData[] = {
		{ "Category", "Render" },
		{ "Comment", "// Unaligned, VelocityAligned, Custom\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Unaligned, VelocityAligned, Custom" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bVelocityAligned_MetaData[] = {
		{ "Category", "Render" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MotionStretch_MetaData[] = {
		{ "Category", "Render" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXRenderRecipe constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FacingMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Alignment;
	static void NewProp_bSoftParticles_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSoftParticles;
	static void NewProp_bVelocityAligned_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVelocityAligned;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MotionStretch;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXRenderRecipe constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXRenderRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXRenderRecipe;
class UScriptStruct* FVFXRenderRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXRenderRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXRenderRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXRenderRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXRenderRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXRenderRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXRenderRecipe Property Definitions *****************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRenderRecipe, RendererType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_FacingMode = { "FacingMode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRenderRecipe, FacingMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FacingMode_MetaData), NewProp_FacingMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_Alignment = { "Alignment", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRenderRecipe, Alignment), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Alignment_MetaData), NewProp_Alignment_MetaData) };
void Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bSoftParticles_SetBit(void* Obj)
{
	((FVFXRenderRecipe*)Obj)->bSoftParticles = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bSoftParticles = { "bSoftParticles", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXRenderRecipe), &Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bSoftParticles_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bSoftParticles_MetaData), NewProp_bSoftParticles_MetaData) };
void Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bVelocityAligned_SetBit(void* Obj)
{
	((FVFXRenderRecipe*)Obj)->bVelocityAligned = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bVelocityAligned = { "bVelocityAligned", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXRenderRecipe), &Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bVelocityAligned_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bVelocityAligned_MetaData), NewProp_bVelocityAligned_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_MotionStretch = { "MotionStretch", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRenderRecipe, MotionStretch), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MotionStretch_MetaData), NewProp_MotionStretch_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_FacingMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_Alignment,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bSoftParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_bVelocityAligned,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewProp_MotionStretch,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXRenderRecipe Property Definitions *******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXRenderRecipe",
	Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::PropPointers),
	sizeof(FVFXRenderRecipe),
	alignof(FVFXRenderRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXRenderRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXRenderRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXRenderRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXRenderRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXRenderRecipe ****************************************************

// ********** Begin ScriptStruct FVFXLayerRecipe ***************************************************
struct Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXLayerRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXLayerRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "Layer" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "Category", "Layer" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Spawn_MetaData[] = {
		{ "Category", "Spawn" },
		{ "Comment", "// core/smoke/sparks/trail/etc\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "core/smoke/sparks/trail/etc" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "Category", "Lifetime" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifetimeVariation_MetaData[] = {
		{ "Category", "Lifetime" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Size_MetaData[] = {
		{ "Category", "Size" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Color_MetaData[] = {
		{ "Category", "Color" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialVelocity_MetaData[] = {
		{ "Category", "Velocity" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VelocityVariation_MetaData[] = {
		{ "Category", "Velocity" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Forces_MetaData[] = {
		{ "Category", "Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Curves_MetaData[] = {
		{ "Category", "Curves" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Render_MetaData[] = {
		{ "Category", "Render" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmitShape_MetaData[] = {
		{ "Category", "Shape" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShapeSize_MetaData[] = {
		{ "Category", "Shape" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SortOrder_MetaData[] = {
		{ "Category", "Rendering" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLocalSpace_MetaData[] = {
		{ "Category", "Rendering" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaterialIndex_MetaData[] = {
		{ "Category", "Material" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXLayerRecipe constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Role;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Spawn;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LifetimeVariation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Size;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FStructPropertyParams NewProp_InitialVelocity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VelocityVariation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Forces_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Forces;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Curves;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Render;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EmitShape;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ShapeSize;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SortOrder;
	static void NewProp_bLocalSpace_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLocalSpace;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaterialIndex;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXLayerRecipe constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXLayerRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXLayerRecipe;
class UScriptStruct* FVFXLayerRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXLayerRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXLayerRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXLayerRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXLayerRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXLayerRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXLayerRecipe Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Role), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Spawn = { "Spawn", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Spawn), Z_Construct_UScriptStruct_FVFXPerSpawnInfo, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spawn_MetaData), NewProp_Spawn_MetaData) }; // 3076027827
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_LifetimeVariation = { "LifetimeVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, LifetimeVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifetimeVariation_MetaData), NewProp_LifetimeVariation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Size), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Size_MetaData), NewProp_Size_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_InitialVelocity = { "InitialVelocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, InitialVelocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialVelocity_MetaData), NewProp_InitialVelocity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_VelocityVariation = { "VelocityVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, VelocityVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VelocityVariation_MetaData), NewProp_VelocityVariation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Forces_Inner = { "Forces", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXForceRecipe, METADATA_PARAMS(0, nullptr) }; // 1428190472
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Forces = { "Forces", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Forces), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Forces_MetaData), NewProp_Forces_MetaData) }; // 1428190472
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Curves = { "Curves", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Curves), Z_Construct_UScriptStruct_FVFXCurveRecipe, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Curves_MetaData), NewProp_Curves_MetaData) }; // 241530474
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Render = { "Render", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, Render), Z_Construct_UScriptStruct_FVFXRenderRecipe, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Render_MetaData), NewProp_Render_MetaData) }; // 114851593
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_EmitShape = { "EmitShape", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, EmitShape), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmitShape_MetaData), NewProp_EmitShape_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_ShapeSize = { "ShapeSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, ShapeSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShapeSize_MetaData), NewProp_ShapeSize_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_SortOrder = { "SortOrder", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, SortOrder), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SortOrder_MetaData), NewProp_SortOrder_MetaData) };
void Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_bLocalSpace_SetBit(void* Obj)
{
	((FVFXLayerRecipe*)Obj)->bLocalSpace = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_bLocalSpace = { "bLocalSpace", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXLayerRecipe), &Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_bLocalSpace_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLocalSpace_MetaData), NewProp_bLocalSpace_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_MaterialIndex = { "MaterialIndex", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXLayerRecipe, MaterialIndex), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaterialIndex_MetaData), NewProp_MaterialIndex_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Spawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Lifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_LifetimeVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Size,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_InitialVelocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_VelocityVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Forces_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Forces,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Curves,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_Render,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_EmitShape,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_ShapeSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_SortOrder,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_bLocalSpace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewProp_MaterialIndex,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXLayerRecipe Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXLayerRecipe",
	Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::PropPointers),
	sizeof(FVFXLayerRecipe),
	alignof(FVFXLayerRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXLayerRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXLayerRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXLayerRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXLayerRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXLayerRecipe *****************************************************

// ********** Begin Enum EVFXEventType *************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXEventType;
static UEnum* EVFXEventType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXEventType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXEventType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXEventType, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXEventType"));
	}
	return Z_Registration_Info_UEnum_EVFXEventType.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXEventType>()
{
	return EVFXEventType_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "OnEmitterBurst.DisplayName", "OnEmitterBurst" },
		{ "OnEmitterBurst.Name", "EVFXEventType::OnEmitterBurst" },
		{ "OnEmitterCollision.DisplayName", "OnEmitterCollision" },
		{ "OnEmitterCollision.Name", "EVFXEventType::OnEmitterCollision" },
		{ "OnEmitterDeath.DisplayName", "OnEmitterDeath" },
		{ "OnEmitterDeath.Name", "EVFXEventType::OnEmitterDeath" },
		{ "OnEmitterStart.DisplayName", "OnEmitterStart" },
		{ "OnEmitterStart.Name", "EVFXEventType::OnEmitterStart" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXEventType::OnEmitterStart", (int64)EVFXEventType::OnEmitterStart },
		{ "EVFXEventType::OnEmitterBurst", (int64)EVFXEventType::OnEmitterBurst },
		{ "EVFXEventType::OnEmitterDeath", (int64)EVFXEventType::OnEmitterDeath },
		{ "EVFXEventType::OnEmitterCollision", (int64)EVFXEventType::OnEmitterCollision },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXEventType",
	"EVFXEventType",
	Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXEventType()
{
	if (!Z_Registration_Info_UEnum_EVFXEventType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXEventType.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXEventType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXEventType.InnerSingleton;
}
// ********** End Enum EVFXEventType ***************************************************************

// ********** Begin ScriptStruct FVFXEventRecipe ***************************************************
struct Z_Construct_UScriptStruct_FVFXEventRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXEventRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXEventRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceLayer_MetaData[] = {
		{ "Category", "Event" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetLayer_MetaData[] = {
		{ "Category", "Event" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "Category", "Event" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Delay_MetaData[] = {
		{ "Category", "Event" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstMultiplier_MetaData[] = {
		{ "Category", "Event" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RateMultiplier_MetaData[] = {
		{ "Category", "Event" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstOverride_MetaData[] = {
		{ "Category", "Event" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXEventRecipe constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SourceLayer;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TargetLayer;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Delay;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BurstMultiplier;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RateMultiplier;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BurstOverride;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXEventRecipe constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEventRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXEventRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXEventRecipe;
class UScriptStruct* FVFXEventRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEventRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXEventRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXEventRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXEventRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXEventRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXEventRecipe Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_SourceLayer = { "SourceLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEventRecipe, SourceLayer), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceLayer_MetaData), NewProp_SourceLayer_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_TargetLayer = { "TargetLayer", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEventRecipe, TargetLayer), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetLayer_MetaData), NewProp_TargetLayer_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEventRecipe, Type), Z_Construct_UEnum_VFXAgentCore_EVFXEventType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 251924240
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_Delay = { "Delay", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEventRecipe, Delay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Delay_MetaData), NewProp_Delay_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_BurstMultiplier = { "BurstMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEventRecipe, BurstMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstMultiplier_MetaData), NewProp_BurstMultiplier_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_RateMultiplier = { "RateMultiplier", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEventRecipe, RateMultiplier), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RateMultiplier_MetaData), NewProp_RateMultiplier_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_BurstOverride = { "BurstOverride", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEventRecipe, BurstOverride), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstOverride_MetaData), NewProp_BurstOverride_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_SourceLayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_TargetLayer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_Delay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_BurstMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_RateMultiplier,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewProp_BurstOverride,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXEventRecipe Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"VFXEventRecipe",
	Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::PropPointers),
	sizeof(FVFXEventRecipe),
	alignof(FVFXEventRecipe),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXEventRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEventRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXEventRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXEventRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXEventRecipe *****************************************************

// ********** Begin ScriptStruct FVFXEmitterSpec ***************************************************
struct Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXEmitterSpec); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXEmitterSpec); }
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
		{ "Comment", "// Path to a Niagara System or Emitter asset to use as template\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Path to a Niagara System or Emitter asset to use as template" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TemplateId_MetaData[] = {
		{ "Category", "Emitter" },
		{ "Comment", "// Or a known ID like \"Fountain\", \"Beam\" if we support mapping\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Or a known ID like \"Fountain\", \"Beam\" if we support mapping" },
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
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorEnd_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseColorGradient_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifetimeVariation_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Size_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeEnd_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseSizeOverLife_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeVariation_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VelocityVariation_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurlNoiseStrength_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "Comment", "// Forces (module-driven)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Forces (module-driven)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurlNoiseFrequency_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseStrength_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseFrequency_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LimitVelocity_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VortexStrength_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_VortexAxis_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LiftStrength_MetaData[] = {
		{ "Category", "Emitter|Forces" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Drag_MetaData[] = {
		{ "Category", "Emitter|Physics" },
		{ "Comment", "// Physics\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Physics" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Acceleration_MetaData[] = {
		{ "Category", "Emitter|Physics" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseGravity_MetaData[] = {
		{ "Category", "Emitter|Physics" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mass_MetaData[] = {
		{ "Category", "Emitter|Physics" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotationRate_MetaData[] = {
		{ "Category", "Emitter|Rotation" },
		{ "Comment", "// Rotation\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Rotation" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InitialRotation_MetaData[] = {
		{ "Category", "Emitter|Rotation" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RotationRateVariation_MetaData[] = {
		{ "Category", "Emitter|Rotation" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Alpha_MetaData[] = {
		{ "Category", "Emitter|Color" },
		{ "Comment", "// Alpha over life\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Alpha over life" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlphaEnd_MetaData[] = {
		{ "Category", "Emitter|Color" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUseAlphaOverLife_MetaData[] = {
		{ "Category", "Emitter|Color" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FacingMode_MetaData[] = {
		{ "Category", "Emitter|Rendering" },
		{ "Comment", "// Render options\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Render options" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Alignment_MetaData[] = {
		{ "Category", "Emitter|Rendering" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bVelocityAligned_MetaData[] = {
		{ "Category", "Emitter|Rendering" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MotionStretch_MetaData[] = {
		{ "Category", "Emitter|Rendering" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SortOrder_MetaData[] = {
		{ "Category", "Emitter|Rendering" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLocalSpace_MetaData[] = {
		{ "Category", "Emitter|Rendering" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmitShape_MetaData[] = {
		{ "Category", "Emitter|Shape" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ShapeSize_MetaData[] = {
		{ "Category", "Emitter|Shape" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Notes_MetaData[] = {
		{ "Category", "Emitter" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXEmitterSpec constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TemplatePath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TemplateId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_RendererType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Spawn;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Color;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ColorEnd;
	static void NewProp_bUseColorGradient_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseColorGradient;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LifetimeVariation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Size;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SizeEnd;
	static void NewProp_bUseSizeOverLife_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseSizeOverLife;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SizeVariation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VelocityVariation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurlNoiseStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurlNoiseFrequency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseFrequency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LimitVelocity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_VortexStrength;
	static const UECodeGen_Private::FStructPropertyParams NewProp_VortexAxis;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LiftStrength;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Drag;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Acceleration;
	static void NewProp_bUseGravity_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseGravity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Mass;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RotationRate;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InitialRotation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RotationRateVariation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Alpha;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AlphaEnd;
	static void NewProp_bUseAlphaOverLife_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUseAlphaOverLife;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FacingMode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Alignment;
	static void NewProp_bVelocityAligned_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bVelocityAligned;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_MotionStretch;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SortOrder;
	static void NewProp_bLocalSpace_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLocalSpace;
	static const UECodeGen_Private::FStrPropertyParams NewProp_EmitShape;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ShapeSize;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Notes;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXEmitterSpec constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEmitterSpec>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXEmitterSpec;
class UScriptStruct* FVFXEmitterSpec::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEmitterSpec.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXEmitterSpec.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXEmitterSpec, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXEmitterSpec"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXEmitterSpec.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXEmitterSpec Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplatePath = { "TemplatePath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, TemplatePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemplatePath_MetaData), NewProp_TemplatePath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplateId = { "TemplateId", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, TemplateId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemplateId_MetaData), NewProp_TemplateId_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, RendererType), Z_Construct_UEnum_VFXAgentCore_EVFXRendererType, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) }; // 624130330
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Spawn = { "Spawn", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Spawn), Z_Construct_UScriptStruct_FVFXPerSpawnInfo, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spawn_MetaData), NewProp_Spawn_MetaData) }; // 3076027827
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Color = { "Color", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Color), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Color_MetaData), NewProp_Color_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_ColorEnd = { "ColorEnd", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, ColorEnd), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorEnd_MetaData), NewProp_ColorEnd_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseColorGradient_SetBit(void* Obj)
{
	((FVFXEmitterSpec*)Obj)->bUseColorGradient = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseColorGradient = { "bUseColorGradient", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterSpec), &Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseColorGradient_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseColorGradient_MetaData), NewProp_bUseColorGradient_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_LifetimeVariation = { "LifetimeVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, LifetimeVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifetimeVariation_MetaData), NewProp_LifetimeVariation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Size = { "Size", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Size), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Size_MetaData), NewProp_Size_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_SizeEnd = { "SizeEnd", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, SizeEnd), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeEnd_MetaData), NewProp_SizeEnd_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseSizeOverLife_SetBit(void* Obj)
{
	((FVFXEmitterSpec*)Obj)->bUseSizeOverLife = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseSizeOverLife = { "bUseSizeOverLife", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterSpec), &Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseSizeOverLife_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseSizeOverLife_MetaData), NewProp_bUseSizeOverLife_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_SizeVariation = { "SizeVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, SizeVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeVariation_MetaData), NewProp_SizeVariation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_VelocityVariation = { "VelocityVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, VelocityVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VelocityVariation_MetaData), NewProp_VelocityVariation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_CurlNoiseStrength = { "CurlNoiseStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, CurlNoiseStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurlNoiseStrength_MetaData), NewProp_CurlNoiseStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_CurlNoiseFrequency = { "CurlNoiseFrequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, CurlNoiseFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurlNoiseFrequency_MetaData), NewProp_CurlNoiseFrequency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_NoiseStrength = { "NoiseStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, NoiseStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseStrength_MetaData), NewProp_NoiseStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_NoiseFrequency = { "NoiseFrequency", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, NoiseFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseFrequency_MetaData), NewProp_NoiseFrequency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_LimitVelocity = { "LimitVelocity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, LimitVelocity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LimitVelocity_MetaData), NewProp_LimitVelocity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_VortexStrength = { "VortexStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, VortexStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VortexStrength_MetaData), NewProp_VortexStrength_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_VortexAxis = { "VortexAxis", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, VortexAxis), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_VortexAxis_MetaData), NewProp_VortexAxis_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_LiftStrength = { "LiftStrength", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, LiftStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LiftStrength_MetaData), NewProp_LiftStrength_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Drag = { "Drag", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Drag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Drag_MetaData), NewProp_Drag_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Acceleration = { "Acceleration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Acceleration), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Acceleration_MetaData), NewProp_Acceleration_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseGravity_SetBit(void* Obj)
{
	((FVFXEmitterSpec*)Obj)->bUseGravity = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseGravity = { "bUseGravity", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterSpec), &Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseGravity_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseGravity_MetaData), NewProp_bUseGravity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Mass = { "Mass", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Mass), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mass_MetaData), NewProp_Mass_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RotationRate = { "RotationRate", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, RotationRate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotationRate_MetaData), NewProp_RotationRate_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_InitialRotation = { "InitialRotation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, InitialRotation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InitialRotation_MetaData), NewProp_InitialRotation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RotationRateVariation = { "RotationRateVariation", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, RotationRateVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RotationRateVariation_MetaData), NewProp_RotationRateVariation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Alpha = { "Alpha", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Alpha), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Alpha_MetaData), NewProp_Alpha_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_AlphaEnd = { "AlphaEnd", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, AlphaEnd), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlphaEnd_MetaData), NewProp_AlphaEnd_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseAlphaOverLife_SetBit(void* Obj)
{
	((FVFXEmitterSpec*)Obj)->bUseAlphaOverLife = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseAlphaOverLife = { "bUseAlphaOverLife", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterSpec), &Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseAlphaOverLife_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUseAlphaOverLife_MetaData), NewProp_bUseAlphaOverLife_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_FacingMode = { "FacingMode", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, FacingMode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FacingMode_MetaData), NewProp_FacingMode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Alignment = { "Alignment", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Alignment), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Alignment_MetaData), NewProp_Alignment_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bVelocityAligned_SetBit(void* Obj)
{
	((FVFXEmitterSpec*)Obj)->bVelocityAligned = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bVelocityAligned = { "bVelocityAligned", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterSpec), &Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bVelocityAligned_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bVelocityAligned_MetaData), NewProp_bVelocityAligned_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_MotionStretch = { "MotionStretch", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, MotionStretch), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MotionStretch_MetaData), NewProp_MotionStretch_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_SortOrder = { "SortOrder", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, SortOrder), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SortOrder_MetaData), NewProp_SortOrder_MetaData) };
void Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bLocalSpace_SetBit(void* Obj)
{
	((FVFXEmitterSpec*)Obj)->bLocalSpace = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bLocalSpace = { "bLocalSpace", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEmitterSpec), &Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bLocalSpace_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLocalSpace_MetaData), NewProp_bLocalSpace_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_EmitShape = { "EmitShape", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, EmitShape), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmitShape_MetaData), NewProp_EmitShape_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_ShapeSize = { "ShapeSize", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, ShapeSize), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ShapeSize_MetaData), NewProp_ShapeSize_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Notes = { "Notes", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEmitterSpec, Notes), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Notes_MetaData), NewProp_Notes_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplatePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_TemplateId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Spawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Color,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_ColorEnd,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseColorGradient,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Lifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_LifetimeVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Size,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_SizeEnd,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseSizeOverLife,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_SizeVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Velocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_VelocityVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_CurlNoiseStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_CurlNoiseFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_NoiseStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_NoiseFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_LimitVelocity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_VortexStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_VortexAxis,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_LiftStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Drag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Acceleration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseGravity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Mass,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RotationRate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_InitialRotation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_RotationRateVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Alpha,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_AlphaEnd,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bUseAlphaOverLife,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_FacingMode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Alignment,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bVelocityAligned,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_MotionStretch,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_SortOrder,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_bLocalSpace,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_EmitShape,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_ShapeSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewProp_Notes,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXEmitterSpec Property Definitions ********************************
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
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXEmitterSpec()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEmitterSpec.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXEmitterSpec.InnerSingleton, Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXEmitterSpec.InnerSingleton);
}
// ********** End ScriptStruct FVFXEmitterSpec *****************************************************

// ********** Begin ScriptStruct FVFXEffectSpec ****************************************************
struct Z_Construct_UScriptStruct_FVFXEffectSpec_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXEffectSpec); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXEffectSpec); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OutputPath_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Emitters_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Materials_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intent_MetaData[] = {
		{ "Category", "Effect" },
		{ "Comment", "// NEW: Intent for constraint-aware generation (non-optional for simplicity)\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "NEW: Intent for constraint-aware generation (non-optional for simplicity)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bHasIntent_MetaData[] = {
		{ "Category", "Effect" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXEffectSpec constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutputPath;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Emitters_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Emitters;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Materials_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Materials;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Intent;
	static void NewProp_bHasIntent_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasIntent;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXEffectSpec constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXEffectSpec>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXEffectSpec_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXEffectSpec;
class UScriptStruct* FVFXEffectSpec::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEffectSpec.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXEffectSpec.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXEffectSpec, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXEffectSpec"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXEffectSpec.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXEffectSpec Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_OutputPath = { "OutputPath", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, OutputPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OutputPath_MetaData), NewProp_OutputPath_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters_Inner = { "Emitters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXEmitterSpec, METADATA_PARAMS(0, nullptr) }; // 3234902414
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters = { "Emitters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, Emitters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Emitters_MetaData), NewProp_Emitters_MetaData) }; // 3234902414
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Materials_Inner = { "Materials", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXMaterialRecipe, METADATA_PARAMS(0, nullptr) }; // 3281737724
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Materials = { "Materials", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, Materials), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Materials_MetaData), NewProp_Materials_MetaData) }; // 3281737724
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Intent = { "Intent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXEffectSpec, Intent), Z_Construct_UScriptStruct_FVFXIntent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intent_MetaData), NewProp_Intent_MetaData) }; // 3289489561
void Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_bHasIntent_SetBit(void* Obj)
{
	((FVFXEffectSpec*)Obj)->bHasIntent = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_bHasIntent = { "bHasIntent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXEffectSpec), &Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_bHasIntent_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bHasIntent_MetaData), NewProp_bHasIntent_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_OutputPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Emitters,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Materials_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Materials,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_Intent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewProp_bHasIntent,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FVFXEffectSpec Property Definitions *********************************
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
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXEffectSpec()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXEffectSpec.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXEffectSpec.InnerSingleton, Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXEffectSpec.InnerSingleton);
}
// ********** End ScriptStruct FVFXEffectSpec ******************************************************

// ********** Begin ScriptStruct FVFXRepairReport **************************************************
struct Z_Construct_UScriptStruct_FVFXRepairReport_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXRepairReport); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXRepairReport); }
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

// ********** Begin ScriptStruct FVFXRepairReport constinit property declarations ******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SystemPath;
	static void NewProp_bCompileSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCompileSuccess;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Errors_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Errors;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Warnings_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Warnings;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXRepairReport constinit property declarations ********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXRepairReport>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXRepairReport_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXRepairReport;
class UScriptStruct* FVFXRepairReport::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXRepairReport.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXRepairReport.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXRepairReport, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXRepairReport"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXRepairReport.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXRepairReport Property Definitions *****************************
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
// ********** End ScriptStruct FVFXRepairReport Property Definitions *******************************
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
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRepairReport_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXRepairReport_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXRepairReport()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXRepairReport.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXRepairReport.InnerSingleton, Z_Construct_UScriptStruct_FVFXRepairReport_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXRepairReport.InnerSingleton);
}
// ********** End ScriptStruct FVFXRepairReport ****************************************************

// ********** Begin ScriptStruct FVFXRecipe ********************************************************
struct Z_Construct_UScriptStruct_FVFXRecipe_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FVFXRecipe); }
	static inline consteval int16 GetStructAlignment() { return alignof(FVFXRecipe); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Intent_MetaData[] = {
		{ "Category", "Intent" },
		{ "Comment", "// ========== NEW: VFX Intent Layer (Director's Understanding) ==========\n// This is the semantic understanding of WHAT the effect is, BEFORE Niagara modules\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "========== NEW: VFX Intent Layer (Director's Understanding) ==========\nThis is the semantic understanding of WHAT the effect is, BEFORE Niagara modules" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Spec_MetaData[] = {
		{ "Category", "Spec" },
		{ "Comment", "// ========== NEW: Niagara Spec (Constraint-aware compilation target) ==========\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "========== NEW: Niagara Spec (Constraint-aware compilation target) ==========" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLoop_MetaData[] = {
		{ "Category", "System" },
		{ "Comment", "// ========== System-level properties ==========\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "========== System-level properties ==========" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Duration_MetaData[] = {
		{ "Category", "System" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WarmupTime_MetaData[] = {
		{ "Category", "System" },
		{ "Comment", "// 0 for infinite\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "0 for infinite" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Bounds_MetaData[] = {
		{ "Category", "System" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Emitters_MetaData[] = {
		{ "Category", "Emitters" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Layers_MetaData[] = {
		{ "Category", "Layers" },
		{ "Comment", "// New layered recipe format\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "New layered recipe format" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Events_MetaData[] = {
		{ "Category", "Events" },
		{ "Comment", "// Event chain between layers\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Event chain between layers" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Parameters_MetaData[] = {
		{ "Category", "Parameters" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Materials_MetaData[] = {
		{ "Category", "Materials" },
		{ "Comment", "// User parameters like color, intensity\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "User parameters like color, intensity" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Dependencies_MetaData[] = {
		{ "Category", "Dependencies" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Version_MetaData[] = {
		{ "Category", "Version" },
		{ "Comment", "// Texture/Model paths\n" },
		{ "ModuleRelativePath", "Public/VFXRecipe.h" },
		{ "ToolTip", "Texture/Model paths" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FVFXRecipe constinit property declarations ************************
	static const UECodeGen_Private::FStructPropertyParams NewProp_Intent;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Spec;
	static void NewProp_bLoop_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLoop;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Duration;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_WarmupTime;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Bounds;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Emitters_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Emitters;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Layers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Layers;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Events_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Events;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Parameters_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Parameters_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_Parameters;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Materials_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Materials;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Dependencies_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Dependencies;
	static const UECodeGen_Private::FIntPropertyParams NewProp_Version;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FVFXRecipe constinit property declarations **************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FVFXRecipe>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FVFXRecipe_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FVFXRecipe;
class UScriptStruct* FVFXRecipe::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXRecipe.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FVFXRecipe.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FVFXRecipe, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("VFXRecipe"));
	}
	return Z_Registration_Info_UScriptStruct_FVFXRecipe.OuterSingleton;
	}

// ********** Begin ScriptStruct FVFXRecipe Property Definitions ***********************************
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Intent = { "Intent", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Intent), Z_Construct_UScriptStruct_FVFXIntent, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Intent_MetaData), NewProp_Intent_MetaData) }; // 3289489561
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Spec = { "Spec", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Spec), Z_Construct_UScriptStruct_FVFXEffectSpec, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spec_MetaData), NewProp_Spec_MetaData) }; // 1773197136
void Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop_SetBit(void* Obj)
{
	((FVFXRecipe*)Obj)->bLoop = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop = { "bLoop", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FVFXRecipe), &Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLoop_MetaData), NewProp_bLoop_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Duration = { "Duration", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Duration), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Duration_MetaData), NewProp_Duration_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_WarmupTime = { "WarmupTime", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, WarmupTime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WarmupTime_MetaData), NewProp_WarmupTime_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Bounds = { "Bounds", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Bounds), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Bounds_MetaData), NewProp_Bounds_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters_Inner = { "Emitters", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXEmitterRecipe, METADATA_PARAMS(0, nullptr) }; // 3145495049
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters = { "Emitters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Emitters), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Emitters_MetaData), NewProp_Emitters_MetaData) }; // 3145495049
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Layers_Inner = { "Layers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXLayerRecipe, METADATA_PARAMS(0, nullptr) }; // 1464274648
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Layers = { "Layers", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Layers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Layers_MetaData), NewProp_Layers_MetaData) }; // 1464274648
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Events_Inner = { "Events", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXEventRecipe, METADATA_PARAMS(0, nullptr) }; // 4187006034
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Events = { "Events", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Events), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Events_MetaData), NewProp_Events_MetaData) }; // 4187006034
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters_ValueProp = { "Parameters", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters_Key_KeyProp = { "Parameters_Key", nullptr, (EPropertyFlags)0x0000000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Parameters = { "Parameters", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Parameters), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Parameters_MetaData), NewProp_Parameters_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Materials_Inner = { "Materials", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FVFXMaterialRecipe, METADATA_PARAMS(0, nullptr) }; // 3281737724
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Materials = { "Materials", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Materials), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Materials_MetaData), NewProp_Materials_MetaData) }; // 3281737724
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Dependencies_Inner = { "Dependencies", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Dependencies = { "Dependencies", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Dependencies), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Dependencies_MetaData), NewProp_Dependencies_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Version = { "Version", nullptr, (EPropertyFlags)0x0010000000000005, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FVFXRecipe, Version), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Version_MetaData), NewProp_Version_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FVFXRecipe_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Intent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Spec,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_bLoop,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Duration,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_WarmupTime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Bounds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Emitters,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Layers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Layers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Events_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewProp_Events,
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
// ********** End ScriptStruct FVFXRecipe Property Definitions *************************************
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
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FVFXRecipe_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FVFXRecipe_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FVFXRecipe()
{
	if (!Z_Registration_Info_UScriptStruct_FVFXRecipe.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FVFXRecipe.InnerSingleton, Z_Construct_UScriptStruct_FVFXRecipe_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FVFXRecipe.InnerSingleton);
}
// ********** End ScriptStruct FVFXRecipe **********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h__Script_VFXAgentCore_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EVFXArchetype_StaticEnum, TEXT("EVFXArchetype"), &Z_Registration_Info_UEnum_EVFXArchetype, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1239467032U) },
		{ EVFXMotionModel_StaticEnum, TEXT("EVFXMotionModel"), &Z_Registration_Info_UEnum_EVFXMotionModel, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3479131074U) },
		{ EVFXRendererType_StaticEnum, TEXT("EVFXRendererType"), &Z_Registration_Info_UEnum_EVFXRendererType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 624130330U) },
		{ EVFXForceType_StaticEnum, TEXT("EVFXForceType"), &Z_Registration_Info_UEnum_EVFXForceType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 644312078U) },
		{ EVFXEventType_StaticEnum, TEXT("EVFXEventType"), &Z_Registration_Info_UEnum_EVFXEventType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 251924240U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FVFXPatternAvoidance::StaticStruct, Z_Construct_UScriptStruct_FVFXPatternAvoidance_Statics::NewStructOps, TEXT("VFXPatternAvoidance"),&Z_Registration_Info_UScriptStruct_FVFXPatternAvoidance, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXPatternAvoidance), 3180674912U) },
		{ FVFXMotionBehavior::StaticStruct, Z_Construct_UScriptStruct_FVFXMotionBehavior_Statics::NewStructOps, TEXT("VFXMotionBehavior"),&Z_Registration_Info_UScriptStruct_FVFXMotionBehavior, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXMotionBehavior), 2776603170U) },
		{ FVFXVisualHierarchy::StaticStruct, Z_Construct_UScriptStruct_FVFXVisualHierarchy_Statics::NewStructOps, TEXT("VFXVisualHierarchy"),&Z_Registration_Info_UScriptStruct_FVFXVisualHierarchy, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXVisualHierarchy), 2224825837U) },
		{ FVFXIntent::StaticStruct, Z_Construct_UScriptStruct_FVFXIntent_Statics::NewStructOps, TEXT("VFXIntent"),&Z_Registration_Info_UScriptStruct_FVFXIntent, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXIntent), 3289489561U) },
		{ FVFXEmitterRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics::NewStructOps, TEXT("VFXEmitterRecipe"),&Z_Registration_Info_UScriptStruct_FVFXEmitterRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEmitterRecipe), 3145495049U) },
		{ FVFXTextureRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXTextureRecipe_Statics::NewStructOps, TEXT("VFXTextureRecipe"),&Z_Registration_Info_UScriptStruct_FVFXTextureRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXTextureRecipe), 1708579409U) },
		{ FVFXMaterialRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics::NewStructOps, TEXT("VFXMaterialRecipe"),&Z_Registration_Info_UScriptStruct_FVFXMaterialRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXMaterialRecipe), 3281737724U) },
		{ FVFXPerSpawnInfo::StaticStruct, Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics::NewStructOps, TEXT("VFXPerSpawnInfo"),&Z_Registration_Info_UScriptStruct_FVFXPerSpawnInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXPerSpawnInfo), 3076027827U) },
		{ FVFXCurveKey::StaticStruct, Z_Construct_UScriptStruct_FVFXCurveKey_Statics::NewStructOps, TEXT("VFXCurveKey"),&Z_Registration_Info_UScriptStruct_FVFXCurveKey, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXCurveKey), 2538690331U) },
		{ FVFXColorKey::StaticStruct, Z_Construct_UScriptStruct_FVFXColorKey_Statics::NewStructOps, TEXT("VFXColorKey"),&Z_Registration_Info_UScriptStruct_FVFXColorKey, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXColorKey), 1576140641U) },
		{ FVFXCurveRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXCurveRecipe_Statics::NewStructOps, TEXT("VFXCurveRecipe"),&Z_Registration_Info_UScriptStruct_FVFXCurveRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXCurveRecipe), 241530474U) },
		{ FVFXForceRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXForceRecipe_Statics::NewStructOps, TEXT("VFXForceRecipe"),&Z_Registration_Info_UScriptStruct_FVFXForceRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXForceRecipe), 1428190472U) },
		{ FVFXRenderRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXRenderRecipe_Statics::NewStructOps, TEXT("VFXRenderRecipe"),&Z_Registration_Info_UScriptStruct_FVFXRenderRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXRenderRecipe), 114851593U) },
		{ FVFXLayerRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXLayerRecipe_Statics::NewStructOps, TEXT("VFXLayerRecipe"),&Z_Registration_Info_UScriptStruct_FVFXLayerRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXLayerRecipe), 1464274648U) },
		{ FVFXEventRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXEventRecipe_Statics::NewStructOps, TEXT("VFXEventRecipe"),&Z_Registration_Info_UScriptStruct_FVFXEventRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEventRecipe), 4187006034U) },
		{ FVFXEmitterSpec::StaticStruct, Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics::NewStructOps, TEXT("VFXEmitterSpec"),&Z_Registration_Info_UScriptStruct_FVFXEmitterSpec, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEmitterSpec), 3234902414U) },
		{ FVFXEffectSpec::StaticStruct, Z_Construct_UScriptStruct_FVFXEffectSpec_Statics::NewStructOps, TEXT("VFXEffectSpec"),&Z_Registration_Info_UScriptStruct_FVFXEffectSpec, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXEffectSpec), 1773197136U) },
		{ FVFXRepairReport::StaticStruct, Z_Construct_UScriptStruct_FVFXRepairReport_Statics::NewStructOps, TEXT("VFXRepairReport"),&Z_Registration_Info_UScriptStruct_FVFXRepairReport, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXRepairReport), 2943550343U) },
		{ FVFXRecipe::StaticStruct, Z_Construct_UScriptStruct_FVFXRecipe_Statics::NewStructOps, TEXT("VFXRecipe"),&Z_Registration_Info_UScriptStruct_FVFXRecipe, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FVFXRecipe), 2212918003U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h__Script_VFXAgentCore_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h__Script_VFXAgentCore_924880361{
	TEXT("/Script/VFXAgentCore"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h__Script_VFXAgentCore_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h__Script_VFXAgentCore_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h__Script_VFXAgentCore_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h__Script_VFXAgentCore_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
