// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "EffectSpecV2.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeEffectSpecV2() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FLinearColor();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector2D();
UPackage* Z_Construct_UPackage__Script_VFXAgentCore();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EEventTypeV2();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FCameraReadabilityV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FEffectSpecV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FEffectStyleV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FEventBindingV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerInitV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerSpawnV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerSpecV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FLayerUpdateV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialFeatureSetV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMaterialSpecV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FMotionDescV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2();
VFXAGENTCORE_API UScriptStruct* Z_Construct_UScriptStruct_FTimingEnvelopeV2();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum EVFXBehaviorArchetype *****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXBehaviorArchetype;
static UEnum* EVFXBehaviorArchetype_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXBehaviorArchetype.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXBehaviorArchetype.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXBehaviorArchetype"));
	}
	return Z_Registration_Info_UEnum_EVFXBehaviorArchetype.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EVFXBehaviorArchetype>()
{
	return EVFXBehaviorArchetype_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Behavior Archetype Tag \xe2\x80\x94 canonical effect families\n// ---------------------------------------------------------------------------\n" },
		{ "Custom.DisplayName", "Custom" },
		{ "Custom.Name", "EVFXBehaviorArchetype::Custom" },
		{ "Electric.DisplayName", "Electric / Arc / Lightning" },
		{ "Electric.Name", "EVFXBehaviorArchetype::Electric" },
		{ "Explosion.DisplayName", "Explosion / Impact" },
		{ "Explosion.Name", "EVFXBehaviorArchetype::Explosion" },
		{ "Fire.DisplayName", "Fire / Combustion" },
		{ "Fire.Name", "EVFXBehaviorArchetype::Fire" },
		{ "Magic.DisplayName", "Magic / Aura / Healing" },
		{ "Magic.Name", "EVFXBehaviorArchetype::Magic" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "Smoke.DisplayName", "Smoke / Fog / Dust" },
		{ "Smoke.Name", "EVFXBehaviorArchetype::Smoke" },
		{ "Teleport.DisplayName", "Teleport / Portal / Warp" },
		{ "Teleport.Name", "EVFXBehaviorArchetype::Teleport" },
		{ "ToolTip", "Behavior Archetype Tag \xe2\x80\x94 canonical effect families" },
		{ "Water.DisplayName", "Water / Splash / Rain" },
		{ "Water.Name", "EVFXBehaviorArchetype::Water" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXBehaviorArchetype::Explosion", (int64)EVFXBehaviorArchetype::Explosion },
		{ "EVFXBehaviorArchetype::Magic", (int64)EVFXBehaviorArchetype::Magic },
		{ "EVFXBehaviorArchetype::Electric", (int64)EVFXBehaviorArchetype::Electric },
		{ "EVFXBehaviorArchetype::Teleport", (int64)EVFXBehaviorArchetype::Teleport },
		{ "EVFXBehaviorArchetype::Fire", (int64)EVFXBehaviorArchetype::Fire },
		{ "EVFXBehaviorArchetype::Smoke", (int64)EVFXBehaviorArchetype::Smoke },
		{ "EVFXBehaviorArchetype::Water", (int64)EVFXBehaviorArchetype::Water },
		{ "EVFXBehaviorArchetype::Custom", (int64)EVFXBehaviorArchetype::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXBehaviorArchetype",
	"EVFXBehaviorArchetype",
	Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype()
{
	if (!Z_Registration_Info_UEnum_EVFXBehaviorArchetype.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXBehaviorArchetype.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXBehaviorArchetype.InnerSingleton;
}
// ********** End Enum EVFXBehaviorArchetype *******************************************************

// ********** Begin ScriptStruct FTimingEnvelopeV2 *************************************************
struct Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FTimingEnvelopeV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FTimingEnvelopeV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Timing Envelope \xe2\x80\x94 when a layer starts, peaks, and ends\n// ---------------------------------------------------------------------------\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Timing Envelope \xe2\x80\x94 when a layer starts, peaks, and ends" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DelaySeconds_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AttackSeconds_MetaData[] = {
		{ "Comment", "// Delay before layer starts\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Delay before layer starts" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SustainSeconds_MetaData[] = {
		{ "Comment", "// Ramp-up to full intensity\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Ramp-up to full intensity" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DecaySeconds_MetaData[] = {
		{ "Comment", "// Full-intensity hold\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Full-intensity hold" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TotalLifetime_MetaData[] = {
		{ "Comment", "// Fade-out\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Fade-out" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bLoop_MetaData[] = {
		{ "Comment", "// Particle lifetime\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Particle lifetime" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FTimingEnvelopeV2 constinit property declarations *****************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DelaySeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_AttackSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SustainSeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DecaySeconds;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TotalLifetime;
	static void NewProp_bLoop_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bLoop;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FTimingEnvelopeV2 constinit property declarations *******************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FTimingEnvelopeV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2;
class UScriptStruct* FTimingEnvelopeV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FTimingEnvelopeV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("TimingEnvelopeV2"));
	}
	return Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FTimingEnvelopeV2 Property Definitions ****************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_DelaySeconds = { "DelaySeconds", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTimingEnvelopeV2, DelaySeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DelaySeconds_MetaData), NewProp_DelaySeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_AttackSeconds = { "AttackSeconds", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTimingEnvelopeV2, AttackSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AttackSeconds_MetaData), NewProp_AttackSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_SustainSeconds = { "SustainSeconds", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTimingEnvelopeV2, SustainSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SustainSeconds_MetaData), NewProp_SustainSeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_DecaySeconds = { "DecaySeconds", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTimingEnvelopeV2, DecaySeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DecaySeconds_MetaData), NewProp_DecaySeconds_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_TotalLifetime = { "TotalLifetime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FTimingEnvelopeV2, TotalLifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TotalLifetime_MetaData), NewProp_TotalLifetime_MetaData) };
void Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_bLoop_SetBit(void* Obj)
{
	((FTimingEnvelopeV2*)Obj)->bLoop = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_bLoop = { "bLoop", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FTimingEnvelopeV2), &Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_bLoop_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bLoop_MetaData), NewProp_bLoop_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_DelaySeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_AttackSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_SustainSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_DecaySeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_TotalLifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewProp_bLoop,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FTimingEnvelopeV2 Property Definitions ******************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"TimingEnvelopeV2",
	Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::PropPointers),
	sizeof(FTimingEnvelopeV2),
	alignof(FTimingEnvelopeV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FTimingEnvelopeV2()
{
	if (!Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2.InnerSingleton, Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2.InnerSingleton);
}
// ********** End ScriptStruct FTimingEnvelopeV2 ***************************************************

// ********** Begin Enum EMotionVerbV2 *************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EMotionVerbV2;
static UEnum* EMotionVerbV2_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EMotionVerbV2.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EMotionVerbV2.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EMotionVerbV2"));
	}
	return Z_Registration_Info_UEnum_EMotionVerbV2.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EMotionVerbV2>()
{
	return EMotionVerbV2_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Motion Language \xe2\x80\x94 semantic motion description per layer\n// ---------------------------------------------------------------------------\n" },
		{ "Drift.DisplayName", "Drift (slow wander)" },
		{ "Drift.Name", "EMotionVerbV2::Drift" },
		{ "Explode.DisplayName", "Explode (radial outward)" },
		{ "Explode.Name", "EMotionVerbV2::Explode" },
		{ "Fall.DisplayName", "Fall (gravity pull)" },
		{ "Fall.Name", "EMotionVerbV2::Fall" },
		{ "Flutter.DisplayName", "Flutter (chaotic light)" },
		{ "Flutter.Name", "EMotionVerbV2::Flutter" },
		{ "Implode.DisplayName", "Implode (radial inward)" },
		{ "Implode.Name", "EMotionVerbV2::Implode" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "Orbit.DisplayName", "Orbit (circular)" },
		{ "Orbit.Name", "EMotionVerbV2::Orbit" },
		{ "Pulse.DisplayName", "Pulse (expand/contract)" },
		{ "Pulse.Name", "EMotionVerbV2::Pulse" },
		{ "Rise.DisplayName", "Rise (upward column)" },
		{ "Rise.Name", "EMotionVerbV2::Rise" },
		{ "Snap.DisplayName", "Snap (instant teleport)" },
		{ "Snap.Name", "EMotionVerbV2::Snap" },
		{ "Spiral.DisplayName", "Spiral (helical)" },
		{ "Spiral.Name", "EMotionVerbV2::Spiral" },
		{ "Static.DisplayName", "Static (stationary)" },
		{ "Static.Name", "EMotionVerbV2::Static" },
		{ "Stream.DisplayName", "Stream (directional flow)" },
		{ "Stream.Name", "EMotionVerbV2::Stream" },
		{ "ToolTip", "Motion Language \xe2\x80\x94 semantic motion description per layer" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EMotionVerbV2::Explode", (int64)EMotionVerbV2::Explode },
		{ "EMotionVerbV2::Implode", (int64)EMotionVerbV2::Implode },
		{ "EMotionVerbV2::Rise", (int64)EMotionVerbV2::Rise },
		{ "EMotionVerbV2::Fall", (int64)EMotionVerbV2::Fall },
		{ "EMotionVerbV2::Orbit", (int64)EMotionVerbV2::Orbit },
		{ "EMotionVerbV2::Spiral", (int64)EMotionVerbV2::Spiral },
		{ "EMotionVerbV2::Drift", (int64)EMotionVerbV2::Drift },
		{ "EMotionVerbV2::Snap", (int64)EMotionVerbV2::Snap },
		{ "EMotionVerbV2::Pulse", (int64)EMotionVerbV2::Pulse },
		{ "EMotionVerbV2::Stream", (int64)EMotionVerbV2::Stream },
		{ "EMotionVerbV2::Flutter", (int64)EMotionVerbV2::Flutter },
		{ "EMotionVerbV2::Static", (int64)EMotionVerbV2::Static },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EMotionVerbV2",
	"EMotionVerbV2",
	Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2()
{
	if (!Z_Registration_Info_UEnum_EMotionVerbV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EMotionVerbV2.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EMotionVerbV2.InnerSingleton;
}
// ********** End Enum EMotionVerbV2 ***************************************************************

// ********** Begin ScriptStruct FMotionDescV2 *****************************************************
struct Z_Construct_UScriptStruct_FMotionDescV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMotionDescV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMotionDescV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Verb_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Axis_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Speed_MetaData[] = {
		{ "Comment", "// Primary motion axis\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Primary motion axis" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpeedVariation_MetaData[] = {
		{ "Comment", "// Base speed (cm/s)\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Base speed (cm/s)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurlNoiseIntensity_MetaData[] = {
		{ "Comment", "// 0-1 random variation\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "0-1 random variation" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurlNoiseFrequency_MetaData[] = {
		{ "Comment", "// Turbulence overlay\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Turbulence overlay" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DragCoefficient_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SemanticNote_MetaData[] = {
		{ "Comment", "// Air resistance\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Air resistance" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMotionDescV2 constinit property declarations *********************
	static const UECodeGen_Private::FBytePropertyParams NewProp_Verb_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Verb;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Axis;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Speed;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_SpeedVariation;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurlNoiseIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurlNoiseFrequency;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DragCoefficient;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SemanticNote;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMotionDescV2 constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMotionDescV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMotionDescV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMotionDescV2;
class UScriptStruct* FMotionDescV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMotionDescV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMotionDescV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMotionDescV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MotionDescV2"));
	}
	return Z_Registration_Info_UScriptStruct_FMotionDescV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FMotionDescV2 Property Definitions ********************************
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Verb_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Verb = { "Verb", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, Verb), Z_Construct_UEnum_VFXAgentCore_EMotionVerbV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Verb_MetaData), NewProp_Verb_MetaData) }; // 4286348070
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Axis = { "Axis", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, Axis), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Axis_MetaData), NewProp_Axis_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Speed = { "Speed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, Speed), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Speed_MetaData), NewProp_Speed_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_SpeedVariation = { "SpeedVariation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, SpeedVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpeedVariation_MetaData), NewProp_SpeedVariation_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_CurlNoiseIntensity = { "CurlNoiseIntensity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, CurlNoiseIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurlNoiseIntensity_MetaData), NewProp_CurlNoiseIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_CurlNoiseFrequency = { "CurlNoiseFrequency", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, CurlNoiseFrequency), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurlNoiseFrequency_MetaData), NewProp_CurlNoiseFrequency_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_DragCoefficient = { "DragCoefficient", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, DragCoefficient), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DragCoefficient_MetaData), NewProp_DragCoefficient_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_SemanticNote = { "SemanticNote", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMotionDescV2, SemanticNote), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SemanticNote_MetaData), NewProp_SemanticNote_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMotionDescV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Verb_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Verb,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Axis,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_Speed,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_SpeedVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_CurlNoiseIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_CurlNoiseFrequency,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_DragCoefficient,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewProp_SemanticNote,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMotionDescV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMotionDescV2 Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMotionDescV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MotionDescV2",
	Z_Construct_UScriptStruct_FMotionDescV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMotionDescV2_Statics::PropPointers),
	sizeof(FMotionDescV2),
	alignof(FMotionDescV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMotionDescV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMotionDescV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMotionDescV2()
{
	if (!Z_Registration_Info_UScriptStruct_FMotionDescV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMotionDescV2.InnerSingleton, Z_Construct_UScriptStruct_FMotionDescV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMotionDescV2.InnerSingleton);
}
// ********** End ScriptStruct FMotionDescV2 *******************************************************

// ********** Begin ScriptStruct FMaterialFeatureSetV2 *********************************************
struct Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMaterialFeatureSetV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMaterialFeatureSetV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Material Skeleton \xe2\x80\x94 fixed building blocks that compose a VFX material\n// ---------------------------------------------------------------------------\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Material Skeleton \xe2\x80\x94 fixed building blocks that compose a VFX material" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bFresnel_MetaData[] = {
		{ "Comment", "// Core features (the \"skeleton\")\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Core features (the \"skeleton\")" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_FresnelExponent_MetaData[] = {
		{ "Comment", "// Rim-lighting / edge glow\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Rim-lighting / edge glow" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bDepthFade_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DepthFadeDistance_MetaData[] = {
		{ "Comment", "// Soft particle blending\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Soft particle blending" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bUVDistortion_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DistortionStrength_MetaData[] = {
		{ "Comment", "// UV distortion for heat haze\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "UV distortion for heat haze" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bNoiseMask_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseTiling_MetaData[] = {
		{ "Comment", "// Procedural noise masking\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Procedural noise masking" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_NoiseContrast_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bErodeMask_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ErodeThreshold_MetaData[] = {
		{ "Comment", "// Dissolve / erode effect\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Dissolve / erode effect" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bPanUV_MetaData[] = {
		{ "Comment", "// 0=fully visible, 1=fully eroded\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "0=fully visible, 1=fully eroded" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PanSpeed_MetaData[] = {
		{ "Comment", "// Scrolling UV\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Scrolling UV" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMaterialFeatureSetV2 constinit property declarations *************
	static void NewProp_bFresnel_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bFresnel;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_FresnelExponent;
	static void NewProp_bDepthFade_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bDepthFade;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DepthFadeDistance;
	static void NewProp_bUVDistortion_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bUVDistortion;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_DistortionStrength;
	static void NewProp_bNoiseMask_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bNoiseMask;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseTiling;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_NoiseContrast;
	static void NewProp_bErodeMask_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bErodeMask;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ErodeThreshold;
	static void NewProp_bPanUV_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bPanUV;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PanSpeed;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMaterialFeatureSetV2 constinit property declarations ***************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialFeatureSetV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2;
class UScriptStruct* FMaterialFeatureSetV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialFeatureSetV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialFeatureSetV2"));
	}
	return Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FMaterialFeatureSetV2 Property Definitions ************************
void Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bFresnel_SetBit(void* Obj)
{
	((FMaterialFeatureSetV2*)Obj)->bFresnel = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bFresnel = { "bFresnel", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialFeatureSetV2), &Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bFresnel_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bFresnel_MetaData), NewProp_bFresnel_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_FresnelExponent = { "FresnelExponent", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialFeatureSetV2, FresnelExponent), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_FresnelExponent_MetaData), NewProp_FresnelExponent_MetaData) };
void Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bDepthFade_SetBit(void* Obj)
{
	((FMaterialFeatureSetV2*)Obj)->bDepthFade = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bDepthFade = { "bDepthFade", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialFeatureSetV2), &Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bDepthFade_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bDepthFade_MetaData), NewProp_bDepthFade_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_DepthFadeDistance = { "DepthFadeDistance", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialFeatureSetV2, DepthFadeDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DepthFadeDistance_MetaData), NewProp_DepthFadeDistance_MetaData) };
void Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bUVDistortion_SetBit(void* Obj)
{
	((FMaterialFeatureSetV2*)Obj)->bUVDistortion = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bUVDistortion = { "bUVDistortion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialFeatureSetV2), &Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bUVDistortion_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bUVDistortion_MetaData), NewProp_bUVDistortion_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_DistortionStrength = { "DistortionStrength", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialFeatureSetV2, DistortionStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DistortionStrength_MetaData), NewProp_DistortionStrength_MetaData) };
void Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bNoiseMask_SetBit(void* Obj)
{
	((FMaterialFeatureSetV2*)Obj)->bNoiseMask = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bNoiseMask = { "bNoiseMask", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialFeatureSetV2), &Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bNoiseMask_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bNoiseMask_MetaData), NewProp_bNoiseMask_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_NoiseTiling = { "NoiseTiling", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialFeatureSetV2, NoiseTiling), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseTiling_MetaData), NewProp_NoiseTiling_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_NoiseContrast = { "NoiseContrast", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialFeatureSetV2, NoiseContrast), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_NoiseContrast_MetaData), NewProp_NoiseContrast_MetaData) };
void Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bErodeMask_SetBit(void* Obj)
{
	((FMaterialFeatureSetV2*)Obj)->bErodeMask = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bErodeMask = { "bErodeMask", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialFeatureSetV2), &Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bErodeMask_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bErodeMask_MetaData), NewProp_bErodeMask_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_ErodeThreshold = { "ErodeThreshold", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialFeatureSetV2, ErodeThreshold), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ErodeThreshold_MetaData), NewProp_ErodeThreshold_MetaData) };
void Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bPanUV_SetBit(void* Obj)
{
	((FMaterialFeatureSetV2*)Obj)->bPanUV = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bPanUV = { "bPanUV", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialFeatureSetV2), &Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bPanUV_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bPanUV_MetaData), NewProp_bPanUV_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_PanSpeed = { "PanSpeed", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialFeatureSetV2, PanSpeed), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PanSpeed_MetaData), NewProp_PanSpeed_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bFresnel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_FresnelExponent,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bDepthFade,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_DepthFadeDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bUVDistortion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_DistortionStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bNoiseMask,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_NoiseTiling,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_NoiseContrast,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bErodeMask,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_ErodeThreshold,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_bPanUV,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewProp_PanSpeed,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMaterialFeatureSetV2 Property Definitions **************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MaterialFeatureSetV2",
	Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::PropPointers),
	sizeof(FMaterialFeatureSetV2),
	alignof(FMaterialFeatureSetV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMaterialFeatureSetV2()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2.InnerSingleton, Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2.InnerSingleton);
}
// ********** End ScriptStruct FMaterialFeatureSetV2 ***********************************************

// ********** Begin ScriptStruct FMaterialSpecV2 ***************************************************
struct Z_Construct_UScriptStruct_FMaterialSpecV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FMaterialSpecV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FMaterialSpecV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Shading_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Blend_MetaData[] = {
		{ "Comment", "// unlit | lit\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "unlit | lit" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BaseColor_MetaData[] = {
		{ "Comment", "// additive | translucent | masked | opaque\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "additive | translucent | masked | opaque" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmissiveColor_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EmissiveIntensity_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Opacity_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Features_MetaData[] = {
		{ "Comment", "// Feature set (the composable skeleton)\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Feature set (the composable skeleton)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextureSlots_MetaData[] = {
		{ "Comment", "// Texture slots (name \xe2\x86\x92 usage hint)\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Texture slots (name \xe2\x86\x92 usage hint)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bCustomHLSL_MetaData[] = {
		{ "Comment", "// HLSL Custom Node (optional)\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "HLSL Custom Node (optional)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HLSLCode_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_HLSLContract_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FMaterialSpecV2 constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Shading;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Blend;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BaseColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_EmissiveColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_EmissiveIntensity;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Opacity;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Features;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TextureSlots_ValueProp;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TextureSlots_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_TextureSlots;
	static void NewProp_bCustomHLSL_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bCustomHLSL;
	static const UECodeGen_Private::FStrPropertyParams NewProp_HLSLCode;
	static const UECodeGen_Private::FStrPropertyParams NewProp_HLSLContract;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FMaterialSpecV2 constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FMaterialSpecV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FMaterialSpecV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FMaterialSpecV2;
class UScriptStruct* FMaterialSpecV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialSpecV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FMaterialSpecV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FMaterialSpecV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("MaterialSpecV2"));
	}
	return Z_Registration_Info_UScriptStruct_FMaterialSpecV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FMaterialSpecV2 Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Shading = { "Shading", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, Shading), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Shading_MetaData), NewProp_Shading_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Blend = { "Blend", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, Blend), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Blend_MetaData), NewProp_Blend_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_BaseColor = { "BaseColor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, BaseColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BaseColor_MetaData), NewProp_BaseColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_EmissiveColor = { "EmissiveColor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, EmissiveColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmissiveColor_MetaData), NewProp_EmissiveColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_EmissiveIntensity = { "EmissiveIntensity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, EmissiveIntensity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EmissiveIntensity_MetaData), NewProp_EmissiveIntensity_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Opacity = { "Opacity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, Opacity), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Opacity_MetaData), NewProp_Opacity_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Features = { "Features", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, Features), Z_Construct_UScriptStruct_FMaterialFeatureSetV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Features_MetaData), NewProp_Features_MetaData) }; // 1328717963
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_TextureSlots_ValueProp = { "TextureSlots", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_TextureSlots_Key_KeyProp = { "TextureSlots_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FMapPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_TextureSlots = { "TextureSlots", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, TextureSlots), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextureSlots_MetaData), NewProp_TextureSlots_MetaData) };
void Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_bCustomHLSL_SetBit(void* Obj)
{
	((FMaterialSpecV2*)Obj)->bCustomHLSL = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_bCustomHLSL = { "bCustomHLSL", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FMaterialSpecV2), &Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_bCustomHLSL_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bCustomHLSL_MetaData), NewProp_bCustomHLSL_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_HLSLCode = { "HLSLCode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, HLSLCode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HLSLCode_MetaData), NewProp_HLSLCode_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_HLSLContract = { "HLSLContract", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FMaterialSpecV2, HLSLContract), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_HLSLContract_MetaData), NewProp_HLSLContract_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Shading,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Blend,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_BaseColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_EmissiveColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_EmissiveIntensity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Opacity,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_Features,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_TextureSlots_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_TextureSlots_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_TextureSlots,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_bCustomHLSL,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_HLSLCode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewProp_HLSLContract,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FMaterialSpecV2 Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"MaterialSpecV2",
	Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::PropPointers),
	sizeof(FMaterialSpecV2),
	alignof(FMaterialSpecV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FMaterialSpecV2()
{
	if (!Z_Registration_Info_UScriptStruct_FMaterialSpecV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FMaterialSpecV2.InnerSingleton, Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FMaterialSpecV2.InnerSingleton);
}
// ********** End ScriptStruct FMaterialSpecV2 *****************************************************

// ********** Begin Enum ELayerRoleV2 **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ELayerRoleV2;
static UEnum* ELayerRoleV2_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ELayerRoleV2.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ELayerRoleV2.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("ELayerRoleV2"));
	}
	return Z_Registration_Info_UEnum_ELayerRoleV2.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<ELayerRoleV2>()
{
	return ELayerRoleV2_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Layer Spec v2 \xe2\x80\x94 a single effect layer (maps to one Niagara emitter)\n// ---------------------------------------------------------------------------\n" },
		{ "CoreBlast.DisplayName", "Core Blast" },
		{ "CoreBlast.Name", "ELayerRoleV2::CoreBlast" },
		{ "Custom.DisplayName", "Custom" },
		{ "Custom.Name", "ELayerRoleV2::Custom" },
		{ "Distortion.DisplayName", "Distortion / Shockwave" },
		{ "Distortion.Name", "ELayerRoleV2::Distortion" },
		{ "Glow.DisplayName", "Glow / Light" },
		{ "Glow.Name", "ELayerRoleV2::Glow" },
		{ "Ground.DisplayName", "Ground Scorch / Decal" },
		{ "Ground.Name", "ELayerRoleV2::Ground" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "SecondaryFill.DisplayName", "Secondary Fill" },
		{ "SecondaryFill.Name", "ELayerRoleV2::SecondaryFill" },
		{ "Smoke.DisplayName", "Smoke / Atmosphere" },
		{ "Smoke.Name", "ELayerRoleV2::Smoke" },
		{ "Sparks.DisplayName", "Sparks / Debris" },
		{ "Sparks.Name", "ELayerRoleV2::Sparks" },
		{ "ToolTip", "Layer Spec v2 \xe2\x80\x94 a single effect layer (maps to one Niagara emitter)" },
		{ "Trail.DisplayName", "Trail / Ribbon" },
		{ "Trail.Name", "ELayerRoleV2::Trail" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ELayerRoleV2::CoreBlast", (int64)ELayerRoleV2::CoreBlast },
		{ "ELayerRoleV2::SecondaryFill", (int64)ELayerRoleV2::SecondaryFill },
		{ "ELayerRoleV2::Sparks", (int64)ELayerRoleV2::Sparks },
		{ "ELayerRoleV2::Trail", (int64)ELayerRoleV2::Trail },
		{ "ELayerRoleV2::Smoke", (int64)ELayerRoleV2::Smoke },
		{ "ELayerRoleV2::Glow", (int64)ELayerRoleV2::Glow },
		{ "ELayerRoleV2::Distortion", (int64)ELayerRoleV2::Distortion },
		{ "ELayerRoleV2::Ground", (int64)ELayerRoleV2::Ground },
		{ "ELayerRoleV2::Custom", (int64)ELayerRoleV2::Custom },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"ELayerRoleV2",
	"ELayerRoleV2",
	Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2()
{
	if (!Z_Registration_Info_UEnum_ELayerRoleV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ELayerRoleV2.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ELayerRoleV2.InnerSingleton;
}
// ********** End Enum ELayerRoleV2 ****************************************************************

// ********** Begin ScriptStruct FLayerSpawnV2 *****************************************************
struct Z_Construct_UScriptStruct_FLayerSpawnV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerSpawnV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerSpawnV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Mode_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Rate_MetaData[] = {
		{ "Comment", "// burst | rate | event\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "burst | rate | event" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BurstCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerSpawnV2 constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Mode;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Rate;
	static const UECodeGen_Private::FIntPropertyParams NewProp_BurstCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerSpawnV2 constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerSpawnV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerSpawnV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerSpawnV2;
class UScriptStruct* FLayerSpawnV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpawnV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerSpawnV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerSpawnV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerSpawnV2"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerSpawnV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerSpawnV2 Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::NewProp_Mode = { "Mode", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpawnV2, Mode), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Mode_MetaData), NewProp_Mode_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::NewProp_Rate = { "Rate", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpawnV2, Rate), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Rate_MetaData), NewProp_Rate_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::NewProp_BurstCount = { "BurstCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpawnV2, BurstCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BurstCount_MetaData), NewProp_BurstCount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::NewProp_Mode,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::NewProp_Rate,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::NewProp_BurstCount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerSpawnV2 Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerSpawnV2",
	Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::PropPointers),
	sizeof(FLayerSpawnV2),
	alignof(FLayerSpawnV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerSpawnV2()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpawnV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerSpawnV2.InnerSingleton, Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerSpawnV2.InnerSingleton);
}
// ********** End ScriptStruct FLayerSpawnV2 *******************************************************

// ********** Begin ScriptStruct FLayerInitV2 ******************************************************
struct Z_Construct_UScriptStruct_FLayerInitV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerInitV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerInitV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Lifetime_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LifetimeVariation_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeRange_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Velocity_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerInitV2 constinit property declarations **********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Lifetime;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_LifetimeVariation;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SizeRange;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Velocity;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerInitV2 constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerInitV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerInitV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerInitV2;
class UScriptStruct* FLayerInitV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerInitV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerInitV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerInitV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerInitV2"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerInitV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerInitV2 Property Definitions *********************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_Lifetime = { "Lifetime", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitV2, Lifetime), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Lifetime_MetaData), NewProp_Lifetime_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_LifetimeVariation = { "LifetimeVariation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitV2, LifetimeVariation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LifetimeVariation_MetaData), NewProp_LifetimeVariation_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_SizeRange = { "SizeRange", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitV2, SizeRange), Z_Construct_UScriptStruct_FVector2D, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeRange_MetaData), NewProp_SizeRange_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_Velocity = { "Velocity", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerInitV2, Velocity), Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Velocity_MetaData), NewProp_Velocity_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerInitV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_Lifetime,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_LifetimeVariation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_SizeRange,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewProp_Velocity,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerInitV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerInitV2 Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerInitV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerInitV2",
	Z_Construct_UScriptStruct_FLayerInitV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerInitV2_Statics::PropPointers),
	sizeof(FLayerInitV2),
	alignof(FLayerInitV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerInitV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerInitV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerInitV2()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerInitV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerInitV2.InnerSingleton, Z_Construct_UScriptStruct_FLayerInitV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerInitV2.InnerSingleton);
}
// ********** End ScriptStruct FLayerInitV2 ********************************************************

// ********** Begin ScriptStruct FLayerUpdateV2 ****************************************************
struct Z_Construct_UScriptStruct_FLayerUpdateV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerUpdateV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerUpdateV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Drag_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CurlNoiseStrength_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ColorOverLife_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AlphaOverLife_MetaData[] = {
		{ "Comment", "// e.g., \"warm_to_cool\" semantic\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "e.g., \"warm_to_cool\" semantic" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SizeOverLife_MetaData[] = {
		{ "Comment", "// e.g., \"fade_out_smooth\"\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "e.g., \"fade_out_smooth\"" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerUpdateV2 constinit property declarations ********************
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Drag;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_CurlNoiseStrength;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ColorOverLife;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AlphaOverLife;
	static const UECodeGen_Private::FStrPropertyParams NewProp_SizeOverLife;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerUpdateV2 constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerUpdateV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerUpdateV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerUpdateV2;
class UScriptStruct* FLayerUpdateV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerUpdateV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerUpdateV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerUpdateV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerUpdateV2"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerUpdateV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerUpdateV2 Property Definitions *******************************
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_Drag = { "Drag", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateV2, Drag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Drag_MetaData), NewProp_Drag_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_CurlNoiseStrength = { "CurlNoiseStrength", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateV2, CurlNoiseStrength), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CurlNoiseStrength_MetaData), NewProp_CurlNoiseStrength_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_ColorOverLife = { "ColorOverLife", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateV2, ColorOverLife), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ColorOverLife_MetaData), NewProp_ColorOverLife_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_AlphaOverLife = { "AlphaOverLife", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateV2, AlphaOverLife), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AlphaOverLife_MetaData), NewProp_AlphaOverLife_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_SizeOverLife = { "SizeOverLife", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerUpdateV2, SizeOverLife), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SizeOverLife_MetaData), NewProp_SizeOverLife_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_Drag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_CurlNoiseStrength,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_ColorOverLife,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_AlphaOverLife,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewProp_SizeOverLife,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerUpdateV2 Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerUpdateV2",
	Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::PropPointers),
	sizeof(FLayerUpdateV2),
	alignof(FLayerUpdateV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerUpdateV2()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerUpdateV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerUpdateV2.InnerSingleton, Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerUpdateV2.InnerSingleton);
}
// ********** End ScriptStruct FLayerUpdateV2 ******************************************************

// ********** Begin ScriptStruct FLayerSpecV2 ******************************************************
struct Z_Construct_UScriptStruct_FLayerSpecV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FLayerSpecV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FLayerSpecV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Role_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RendererType_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SortOrder_MetaData[] = {
		{ "Comment", "// sprite | ribbon | mesh | light\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "sprite | ribbon | mesh | light" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Timing_MetaData[] = {
		{ "Comment", "// Timing & rhythm\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Timing & rhythm" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Spawn_MetaData[] = {
		{ "Comment", "// Spawn\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Spawn" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Init_MetaData[] = {
		{ "Comment", "// Init / Update\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Init / Update" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Update_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Motion_MetaData[] = {
		{ "Comment", "// Motion\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Motion" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Material_MetaData[] = {
		{ "Comment", "// Material\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Material" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MaxParticles_MetaData[] = {
		{ "Comment", "// Quality budget\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Quality budget" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PerfHint_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FLayerSpecV2 constinit property declarations **********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Id;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Role_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Role;
	static const UECodeGen_Private::FStrPropertyParams NewProp_RendererType;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SortOrder;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Timing;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Spawn;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Init;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Update;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Motion;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Material;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MaxParticles;
	static const UECodeGen_Private::FStrPropertyParams NewProp_PerfHint;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FLayerSpecV2 constinit property declarations ************************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FLayerSpecV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FLayerSpecV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FLayerSpecV2;
class UScriptStruct* FLayerSpecV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpecV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FLayerSpecV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FLayerSpecV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("LayerSpecV2"));
	}
	return Z_Registration_Info_UScriptStruct_FLayerSpecV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FLayerSpecV2 Property Definitions *********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Id), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Id_MetaData), NewProp_Id_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Name), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Name_MetaData), NewProp_Name_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Role_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Role = { "Role", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Role), Z_Construct_UEnum_VFXAgentCore_ELayerRoleV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Role_MetaData), NewProp_Role_MetaData) }; // 2261688879
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_RendererType = { "RendererType", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, RendererType), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RendererType_MetaData), NewProp_RendererType_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_SortOrder = { "SortOrder", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, SortOrder), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SortOrder_MetaData), NewProp_SortOrder_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Timing = { "Timing", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Timing), Z_Construct_UScriptStruct_FTimingEnvelopeV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Timing_MetaData), NewProp_Timing_MetaData) }; // 2670399457
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Spawn = { "Spawn", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Spawn), Z_Construct_UScriptStruct_FLayerSpawnV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Spawn_MetaData), NewProp_Spawn_MetaData) }; // 3592808436
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Init = { "Init", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Init), Z_Construct_UScriptStruct_FLayerInitV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Init_MetaData), NewProp_Init_MetaData) }; // 2205199612
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Update = { "Update", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Update), Z_Construct_UScriptStruct_FLayerUpdateV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Update_MetaData), NewProp_Update_MetaData) }; // 1866875672
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Motion = { "Motion", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Motion), Z_Construct_UScriptStruct_FMotionDescV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Motion_MetaData), NewProp_Motion_MetaData) }; // 357105703
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, Material), Z_Construct_UScriptStruct_FMaterialSpecV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Material_MetaData), NewProp_Material_MetaData) }; // 2297257739
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_MaxParticles = { "MaxParticles", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, MaxParticles), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MaxParticles_MetaData), NewProp_MaxParticles_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_PerfHint = { "PerfHint", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FLayerSpecV2, PerfHint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PerfHint_MetaData), NewProp_PerfHint_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FLayerSpecV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Id,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Name,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Role_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Role,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_RendererType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_SortOrder,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Timing,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Spawn,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Init,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Update,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Motion,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_Material,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_MaxParticles,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewProp_PerfHint,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpecV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FLayerSpecV2 Property Definitions ***********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FLayerSpecV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"LayerSpecV2",
	Z_Construct_UScriptStruct_FLayerSpecV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpecV2_Statics::PropPointers),
	sizeof(FLayerSpecV2),
	alignof(FLayerSpecV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FLayerSpecV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FLayerSpecV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FLayerSpecV2()
{
	if (!Z_Registration_Info_UScriptStruct_FLayerSpecV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FLayerSpecV2.InnerSingleton, Z_Construct_UScriptStruct_FLayerSpecV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FLayerSpecV2.InnerSingleton);
}
// ********** End ScriptStruct FLayerSpecV2 ********************************************************

// ********** Begin Enum EEventTypeV2 **************************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EEventTypeV2;
static UEnum* EEventTypeV2_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EEventTypeV2.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EEventTypeV2.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EEventTypeV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EEventTypeV2"));
	}
	return Z_Registration_Info_UEnum_EEventTypeV2.OuterSingleton;
}
template<> VFXAGENTCORE_NON_ATTRIBUTED_API UEnum* StaticEnum<EEventTypeV2>()
{
	return EEventTypeV2_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Event Binding v2 \xe2\x80\x94 inter-layer event chains\n// ---------------------------------------------------------------------------\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "OnCollision.DisplayName", "On Collision" },
		{ "OnCollision.Name", "EEventTypeV2::OnCollision" },
		{ "OnDeath.DisplayName", "On Death" },
		{ "OnDeath.Name", "EEventTypeV2::OnDeath" },
		{ "OnLifetimeExpire.DisplayName", "On Lifetime Expire" },
		{ "OnLifetimeExpire.Name", "EEventTypeV2::OnLifetimeExpire" },
		{ "OnSpawn.DisplayName", "On Spawn" },
		{ "OnSpawn.Name", "EEventTypeV2::OnSpawn" },
		{ "Timed.DisplayName", "Timed Trigger" },
		{ "Timed.Name", "EEventTypeV2::Timed" },
		{ "ToolTip", "Event Binding v2 \xe2\x80\x94 inter-layer event chains" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EEventTypeV2::OnDeath", (int64)EEventTypeV2::OnDeath },
		{ "EEventTypeV2::OnCollision", (int64)EEventTypeV2::OnCollision },
		{ "EEventTypeV2::OnSpawn", (int64)EEventTypeV2::OnSpawn },
		{ "EEventTypeV2::OnLifetimeExpire", (int64)EEventTypeV2::OnLifetimeExpire },
		{ "EEventTypeV2::Timed", (int64)EEventTypeV2::Timed },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
}; // struct Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics 
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EEventTypeV2",
	"EEventTypeV2",
	Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EEventTypeV2()
{
	if (!Z_Registration_Info_UEnum_EEventTypeV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EEventTypeV2.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EEventTypeV2_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EEventTypeV2.InnerSingleton;
}
// ********** End Enum EEventTypeV2 ****************************************************************

// ********** Begin ScriptStruct FEventBindingV2 ***************************************************
struct Z_Construct_UScriptStruct_FEventBindingV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEventBindingV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEventBindingV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SourceLayerId_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TargetLayerId_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Type_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Delay_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SpawnCount_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEventBindingV2 constinit property declarations *******************
	static const UECodeGen_Private::FStrPropertyParams NewProp_SourceLayerId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_TargetLayerId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Type_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Type;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Delay;
	static const UECodeGen_Private::FIntPropertyParams NewProp_SpawnCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEventBindingV2 constinit property declarations *********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEventBindingV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEventBindingV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEventBindingV2;
class UScriptStruct* FEventBindingV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEventBindingV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEventBindingV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEventBindingV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EventBindingV2"));
	}
	return Z_Registration_Info_UScriptStruct_FEventBindingV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FEventBindingV2 Property Definitions ******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_SourceLayerId = { "SourceLayerId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEventBindingV2, SourceLayerId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SourceLayerId_MetaData), NewProp_SourceLayerId_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_TargetLayerId = { "TargetLayerId", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEventBindingV2, TargetLayerId), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TargetLayerId_MetaData), NewProp_TargetLayerId_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_Type_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_Type = { "Type", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEventBindingV2, Type), Z_Construct_UEnum_VFXAgentCore_EEventTypeV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Type_MetaData), NewProp_Type_MetaData) }; // 15509164
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_Delay = { "Delay", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEventBindingV2, Delay), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Delay_MetaData), NewProp_Delay_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_SpawnCount = { "SpawnCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEventBindingV2, SpawnCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SpawnCount_MetaData), NewProp_SpawnCount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEventBindingV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_SourceLayerId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_TargetLayerId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_Type_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_Type,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_Delay,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewProp_SpawnCount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEventBindingV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEventBindingV2 Property Definitions ********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEventBindingV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"EventBindingV2",
	Z_Construct_UScriptStruct_FEventBindingV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEventBindingV2_Statics::PropPointers),
	sizeof(FEventBindingV2),
	alignof(FEventBindingV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEventBindingV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEventBindingV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEventBindingV2()
{
	if (!Z_Registration_Info_UScriptStruct_FEventBindingV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEventBindingV2.InnerSingleton, Z_Construct_UScriptStruct_FEventBindingV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEventBindingV2.InnerSingleton);
}
// ********** End ScriptStruct FEventBindingV2 *****************************************************

// ********** Begin ScriptStruct FNiagaraFeatureRequirementsV2 *************************************
struct Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FNiagaraFeatureRequirementsV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FNiagaraFeatureRequirementsV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Niagara Feature Requirements \xe2\x80\x94 hard constraints\n// ---------------------------------------------------------------------------\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Niagara Feature Requirements \xe2\x80\x94 hard constraints" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequiresEvents_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequiresForces_MetaData[] = {
		{ "Comment", "// At least one event binding\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "At least one event binding" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequiresCollision_MetaData[] = {
		{ "Comment", "// At least one force module (drag/noise/vortex)\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "At least one force module (drag/noise/vortex)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequiresLightRenderer_MetaData[] = {
		{ "Comment", "// Collision detection\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Collision detection" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bRequiresRibbonRenderer_MetaData[] = {
		{ "Comment", "// Light renderer for illumination\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Light renderer for illumination" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MinFeatureCount_MetaData[] = {
		{ "Comment", "// How many of the above must be satisfied (min 2 by default)\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "How many of the above must be satisfied (min 2 by default)" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FNiagaraFeatureRequirementsV2 constinit property declarations *****
	static void NewProp_bRequiresEvents_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequiresEvents;
	static void NewProp_bRequiresForces_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequiresForces;
	static void NewProp_bRequiresCollision_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequiresCollision;
	static void NewProp_bRequiresLightRenderer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequiresLightRenderer;
	static void NewProp_bRequiresRibbonRenderer_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequiresRibbonRenderer;
	static const UECodeGen_Private::FIntPropertyParams NewProp_MinFeatureCount;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FNiagaraFeatureRequirementsV2 constinit property declarations *******
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FNiagaraFeatureRequirementsV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2;
class UScriptStruct* FNiagaraFeatureRequirementsV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("NiagaraFeatureRequirementsV2"));
	}
	return Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FNiagaraFeatureRequirementsV2 Property Definitions ****************
void Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresEvents_SetBit(void* Obj)
{
	((FNiagaraFeatureRequirementsV2*)Obj)->bRequiresEvents = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresEvents = { "bRequiresEvents", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FNiagaraFeatureRequirementsV2), &Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresEvents_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequiresEvents_MetaData), NewProp_bRequiresEvents_MetaData) };
void Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresForces_SetBit(void* Obj)
{
	((FNiagaraFeatureRequirementsV2*)Obj)->bRequiresForces = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresForces = { "bRequiresForces", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FNiagaraFeatureRequirementsV2), &Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresForces_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequiresForces_MetaData), NewProp_bRequiresForces_MetaData) };
void Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresCollision_SetBit(void* Obj)
{
	((FNiagaraFeatureRequirementsV2*)Obj)->bRequiresCollision = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresCollision = { "bRequiresCollision", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FNiagaraFeatureRequirementsV2), &Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresCollision_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequiresCollision_MetaData), NewProp_bRequiresCollision_MetaData) };
void Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresLightRenderer_SetBit(void* Obj)
{
	((FNiagaraFeatureRequirementsV2*)Obj)->bRequiresLightRenderer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresLightRenderer = { "bRequiresLightRenderer", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FNiagaraFeatureRequirementsV2), &Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresLightRenderer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequiresLightRenderer_MetaData), NewProp_bRequiresLightRenderer_MetaData) };
void Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresRibbonRenderer_SetBit(void* Obj)
{
	((FNiagaraFeatureRequirementsV2*)Obj)->bRequiresRibbonRenderer = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresRibbonRenderer = { "bRequiresRibbonRenderer", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FNiagaraFeatureRequirementsV2), &Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresRibbonRenderer_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bRequiresRibbonRenderer_MetaData), NewProp_bRequiresRibbonRenderer_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_MinFeatureCount = { "MinFeatureCount", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FNiagaraFeatureRequirementsV2, MinFeatureCount), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MinFeatureCount_MetaData), NewProp_MinFeatureCount_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresEvents,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresForces,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresCollision,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresLightRenderer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_bRequiresRibbonRenderer,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewProp_MinFeatureCount,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FNiagaraFeatureRequirementsV2 Property Definitions ******************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"NiagaraFeatureRequirementsV2",
	Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::PropPointers),
	sizeof(FNiagaraFeatureRequirementsV2),
	alignof(FNiagaraFeatureRequirementsV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2()
{
	if (!Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2.InnerSingleton, Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2.InnerSingleton);
}
// ********** End ScriptStruct FNiagaraFeatureRequirementsV2 ***************************************

// ********** Begin ScriptStruct FCameraReadabilityV2 **********************************************
struct Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FCameraReadabilityV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FCameraReadabilityV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Camera Readability Hints\n// ---------------------------------------------------------------------------\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Camera Readability Hints" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PreferredDistance_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BoundsRadius_MetaData[] = {
		{ "Comment", "// close | medium | far\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "close | medium | far" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_bNeedsSilhouette_MetaData[] = {
		{ "Comment", "// Expected visual radius (cm)\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Expected visual radius (cm)" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ContrastTarget_MetaData[] = {
		{ "Comment", "// Should have clear silhouette\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Should have clear silhouette" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FCameraReadabilityV2 constinit property declarations **************
	static const UECodeGen_Private::FStrPropertyParams NewProp_PreferredDistance;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_BoundsRadius;
	static void NewProp_bNeedsSilhouette_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bNeedsSilhouette;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_ContrastTarget;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FCameraReadabilityV2 constinit property declarations ****************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FCameraReadabilityV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FCameraReadabilityV2;
class UScriptStruct* FCameraReadabilityV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FCameraReadabilityV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FCameraReadabilityV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FCameraReadabilityV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("CameraReadabilityV2"));
	}
	return Z_Registration_Info_UScriptStruct_FCameraReadabilityV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FCameraReadabilityV2 Property Definitions *************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_PreferredDistance = { "PreferredDistance", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCameraReadabilityV2, PreferredDistance), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PreferredDistance_MetaData), NewProp_PreferredDistance_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_BoundsRadius = { "BoundsRadius", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCameraReadabilityV2, BoundsRadius), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BoundsRadius_MetaData), NewProp_BoundsRadius_MetaData) };
void Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_bNeedsSilhouette_SetBit(void* Obj)
{
	((FCameraReadabilityV2*)Obj)->bNeedsSilhouette = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_bNeedsSilhouette = { "bNeedsSilhouette", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(FCameraReadabilityV2), &Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_bNeedsSilhouette_SetBit, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_bNeedsSilhouette_MetaData), NewProp_bNeedsSilhouette_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_ContrastTarget = { "ContrastTarget", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FCameraReadabilityV2, ContrastTarget), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ContrastTarget_MetaData), NewProp_ContrastTarget_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_PreferredDistance,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_BoundsRadius,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_bNeedsSilhouette,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewProp_ContrastTarget,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FCameraReadabilityV2 Property Definitions ***************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"CameraReadabilityV2",
	Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::PropPointers),
	sizeof(FCameraReadabilityV2),
	alignof(FCameraReadabilityV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FCameraReadabilityV2()
{
	if (!Z_Registration_Info_UScriptStruct_FCameraReadabilityV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FCameraReadabilityV2.InnerSingleton, Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FCameraReadabilityV2.InnerSingleton);
}
// ********** End ScriptStruct FCameraReadabilityV2 ************************************************

// ********** Begin ScriptStruct FEffectStyleV2 ****************************************************
struct Z_Construct_UScriptStruct_FEffectStyleV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEffectStyleV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEffectStyleV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Global Style v2 \xe2\x80\x94 palette, feel, reference\n// ---------------------------------------------------------------------------\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Global Style v2 \xe2\x80\x94 palette, feel, reference" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Palette_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_PrimaryColor_MetaData[] = {
		{ "Comment", "// e.g., \"cool_electric\", \"warm_fire\"\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "e.g., \"cool_electric\", \"warm_fire\"" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SecondaryColor_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AccentColor_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_RealismToStylized_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Brightness_MetaData[] = {
		{ "Comment", "// 0=photorealistic, 1=stylized/anime\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "0=photorealistic, 1=stylized/anime" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Saturation_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_MoodTag_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEffectStyleV2 constinit property declarations ********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_Palette;
	static const UECodeGen_Private::FStructPropertyParams NewProp_PrimaryColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_SecondaryColor;
	static const UECodeGen_Private::FStructPropertyParams NewProp_AccentColor;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_RealismToStylized;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Brightness;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_Saturation;
	static const UECodeGen_Private::FStrPropertyParams NewProp_MoodTag;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEffectStyleV2 constinit property declarations **********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEffectStyleV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEffectStyleV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEffectStyleV2;
class UScriptStruct* FEffectStyleV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectStyleV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEffectStyleV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEffectStyleV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EffectStyleV2"));
	}
	return Z_Registration_Info_UScriptStruct_FEffectStyleV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FEffectStyleV2 Property Definitions *******************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_Palette = { "Palette", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, Palette), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Palette_MetaData), NewProp_Palette_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_PrimaryColor = { "PrimaryColor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, PrimaryColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_PrimaryColor_MetaData), NewProp_PrimaryColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_SecondaryColor = { "SecondaryColor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, SecondaryColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SecondaryColor_MetaData), NewProp_SecondaryColor_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_AccentColor = { "AccentColor", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, AccentColor), Z_Construct_UScriptStruct_FLinearColor, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AccentColor_MetaData), NewProp_AccentColor_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_RealismToStylized = { "RealismToStylized", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, RealismToStylized), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_RealismToStylized_MetaData), NewProp_RealismToStylized_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_Brightness = { "Brightness", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, Brightness), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Brightness_MetaData), NewProp_Brightness_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_Saturation = { "Saturation", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, Saturation), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Saturation_MetaData), NewProp_Saturation_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_MoodTag = { "MoodTag", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectStyleV2, MoodTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_MoodTag_MetaData), NewProp_MoodTag_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEffectStyleV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_Palette,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_PrimaryColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_SecondaryColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_AccentColor,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_RealismToStylized,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_Brightness,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_Saturation,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewProp_MoodTag,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectStyleV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEffectStyleV2 Property Definitions *********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEffectStyleV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"EffectStyleV2",
	Z_Construct_UScriptStruct_FEffectStyleV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectStyleV2_Statics::PropPointers),
	sizeof(FEffectStyleV2),
	alignof(FEffectStyleV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectStyleV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEffectStyleV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEffectStyleV2()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectStyleV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEffectStyleV2.InnerSingleton, Z_Construct_UScriptStruct_FEffectStyleV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEffectStyleV2.InnerSingleton);
}
// ********** End ScriptStruct FEffectStyleV2 ******************************************************

// ********** Begin ScriptStruct FEffectSpecV2 *****************************************************
struct Z_Construct_UScriptStruct_FEffectSpecV2_Statics
{
	static inline consteval int32 GetStructSize() { return sizeof(FEffectSpecV2); }
	static inline consteval int16 GetStructAlignment() { return alignof(FEffectSpecV2); }
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "Comment", "// ---------------------------------------------------------------------------\n// Top-Level: EffectSpec v2\n// ---------------------------------------------------------------------------\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Top-Level: EffectSpec v2" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_EffectName_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Archetype_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ArchetypeVariant_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GlobalStyle_MetaData[] = {
		{ "Comment", "// e.g., \"shockwave_explosion\", \"heal_burst\"\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "e.g., \"shockwave_explosion\", \"heal_burst\"" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Layers_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Events_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Requirements_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_CameraReadability_MetaData[] = {
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[] = {
		{ "Comment", "// Brief semantic description for logging/debugging\n" },
		{ "ModuleRelativePath", "Public/EffectSpecV2.h" },
		{ "ToolTip", "Brief semantic description for logging/debugging" },
	};
#endif // WITH_METADATA

// ********** Begin ScriptStruct FEffectSpecV2 constinit property declarations *********************
	static const UECodeGen_Private::FStrPropertyParams NewProp_EffectName;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Archetype_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Archetype;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ArchetypeVariant;
	static const UECodeGen_Private::FStructPropertyParams NewProp_GlobalStyle;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Layers_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Layers;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Events_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Events;
	static const UECodeGen_Private::FStructPropertyParams NewProp_Requirements;
	static const UECodeGen_Private::FStructPropertyParams NewProp_CameraReadability;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
// ********** End ScriptStruct FEffectSpecV2 constinit property declarations ***********************
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FEffectSpecV2>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
}; // struct Z_Construct_UScriptStruct_FEffectSpecV2_Statics
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FEffectSpecV2;
class UScriptStruct* FEffectSpecV2::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectSpecV2.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FEffectSpecV2.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FEffectSpecV2, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EffectSpecV2"));
	}
	return Z_Registration_Info_UScriptStruct_FEffectSpecV2.OuterSingleton;
	}

// ********** Begin ScriptStruct FEffectSpecV2 Property Definitions ********************************
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_EffectName = { "EffectName", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, EffectName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_EffectName_MetaData), NewProp_EffectName_MetaData) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Archetype_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Archetype = { "Archetype", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, Archetype), Z_Construct_UEnum_VFXAgentCore_EVFXBehaviorArchetype, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Archetype_MetaData), NewProp_Archetype_MetaData) }; // 3100817522
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_ArchetypeVariant = { "ArchetypeVariant", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, ArchetypeVariant), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ArchetypeVariant_MetaData), NewProp_ArchetypeVariant_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_GlobalStyle = { "GlobalStyle", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, GlobalStyle), Z_Construct_UScriptStruct_FEffectStyleV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GlobalStyle_MetaData), NewProp_GlobalStyle_MetaData) }; // 2376355695
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Layers_Inner = { "Layers", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FLayerSpecV2, METADATA_PARAMS(0, nullptr) }; // 1073018644
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Layers = { "Layers", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, Layers), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Layers_MetaData), NewProp_Layers_MetaData) }; // 1073018644
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Events_Inner = { "Events", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FEventBindingV2, METADATA_PARAMS(0, nullptr) }; // 4205646659
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Events = { "Events", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, Events), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Events_MetaData), NewProp_Events_MetaData) }; // 4205646659
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Requirements = { "Requirements", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, Requirements), Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Requirements_MetaData), NewProp_Requirements_MetaData) }; // 3453751168
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_CameraReadability = { "CameraReadability", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, CameraReadability), Z_Construct_UScriptStruct_FCameraReadabilityV2, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_CameraReadability_MetaData), NewProp_CameraReadability_MetaData) }; // 1984276498
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FEffectSpecV2, Description), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Description_MetaData), NewProp_Description_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FEffectSpecV2_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_EffectName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Archetype_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Archetype,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_ArchetypeVariant,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_GlobalStyle,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Layers_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Layers,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Events_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Events,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Requirements,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_CameraReadability,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewProp_Description,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectSpecV2_Statics::PropPointers) < 2048);
// ********** End ScriptStruct FEffectSpecV2 Property Definitions **********************************
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FEffectSpecV2_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	&NewStructOps,
	"EffectSpecV2",
	Z_Construct_UScriptStruct_FEffectSpecV2_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectSpecV2_Statics::PropPointers),
	sizeof(FEffectSpecV2),
	alignof(FEffectSpecV2),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000201),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FEffectSpecV2_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FEffectSpecV2_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FEffectSpecV2()
{
	if (!Z_Registration_Info_UScriptStruct_FEffectSpecV2.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FEffectSpecV2.InnerSingleton, Z_Construct_UScriptStruct_FEffectSpecV2_Statics::StructParams);
	}
	return CastChecked<UScriptStruct>(Z_Registration_Info_UScriptStruct_FEffectSpecV2.InnerSingleton);
}
// ********** End ScriptStruct FEffectSpecV2 *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV2_h__Script_VFXAgentCore_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EVFXBehaviorArchetype_StaticEnum, TEXT("EVFXBehaviorArchetype"), &Z_Registration_Info_UEnum_EVFXBehaviorArchetype, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 3100817522U) },
		{ EMotionVerbV2_StaticEnum, TEXT("EMotionVerbV2"), &Z_Registration_Info_UEnum_EMotionVerbV2, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 4286348070U) },
		{ ELayerRoleV2_StaticEnum, TEXT("ELayerRoleV2"), &Z_Registration_Info_UEnum_ELayerRoleV2, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2261688879U) },
		{ EEventTypeV2_StaticEnum, TEXT("EEventTypeV2"), &Z_Registration_Info_UEnum_EEventTypeV2, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 15509164U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FTimingEnvelopeV2::StaticStruct, Z_Construct_UScriptStruct_FTimingEnvelopeV2_Statics::NewStructOps, TEXT("TimingEnvelopeV2"),&Z_Registration_Info_UScriptStruct_FTimingEnvelopeV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FTimingEnvelopeV2), 2670399457U) },
		{ FMotionDescV2::StaticStruct, Z_Construct_UScriptStruct_FMotionDescV2_Statics::NewStructOps, TEXT("MotionDescV2"),&Z_Registration_Info_UScriptStruct_FMotionDescV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMotionDescV2), 357105703U) },
		{ FMaterialFeatureSetV2::StaticStruct, Z_Construct_UScriptStruct_FMaterialFeatureSetV2_Statics::NewStructOps, TEXT("MaterialFeatureSetV2"),&Z_Registration_Info_UScriptStruct_FMaterialFeatureSetV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialFeatureSetV2), 1328717963U) },
		{ FMaterialSpecV2::StaticStruct, Z_Construct_UScriptStruct_FMaterialSpecV2_Statics::NewStructOps, TEXT("MaterialSpecV2"),&Z_Registration_Info_UScriptStruct_FMaterialSpecV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FMaterialSpecV2), 2297257739U) },
		{ FLayerSpawnV2::StaticStruct, Z_Construct_UScriptStruct_FLayerSpawnV2_Statics::NewStructOps, TEXT("LayerSpawnV2"),&Z_Registration_Info_UScriptStruct_FLayerSpawnV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerSpawnV2), 3592808436U) },
		{ FLayerInitV2::StaticStruct, Z_Construct_UScriptStruct_FLayerInitV2_Statics::NewStructOps, TEXT("LayerInitV2"),&Z_Registration_Info_UScriptStruct_FLayerInitV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerInitV2), 2205199612U) },
		{ FLayerUpdateV2::StaticStruct, Z_Construct_UScriptStruct_FLayerUpdateV2_Statics::NewStructOps, TEXT("LayerUpdateV2"),&Z_Registration_Info_UScriptStruct_FLayerUpdateV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerUpdateV2), 1866875672U) },
		{ FLayerSpecV2::StaticStruct, Z_Construct_UScriptStruct_FLayerSpecV2_Statics::NewStructOps, TEXT("LayerSpecV2"),&Z_Registration_Info_UScriptStruct_FLayerSpecV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FLayerSpecV2), 1073018644U) },
		{ FEventBindingV2::StaticStruct, Z_Construct_UScriptStruct_FEventBindingV2_Statics::NewStructOps, TEXT("EventBindingV2"),&Z_Registration_Info_UScriptStruct_FEventBindingV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEventBindingV2), 4205646659U) },
		{ FNiagaraFeatureRequirementsV2::StaticStruct, Z_Construct_UScriptStruct_FNiagaraFeatureRequirementsV2_Statics::NewStructOps, TEXT("NiagaraFeatureRequirementsV2"),&Z_Registration_Info_UScriptStruct_FNiagaraFeatureRequirementsV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FNiagaraFeatureRequirementsV2), 3453751168U) },
		{ FCameraReadabilityV2::StaticStruct, Z_Construct_UScriptStruct_FCameraReadabilityV2_Statics::NewStructOps, TEXT("CameraReadabilityV2"),&Z_Registration_Info_UScriptStruct_FCameraReadabilityV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FCameraReadabilityV2), 1984276498U) },
		{ FEffectStyleV2::StaticStruct, Z_Construct_UScriptStruct_FEffectStyleV2_Statics::NewStructOps, TEXT("EffectStyleV2"),&Z_Registration_Info_UScriptStruct_FEffectStyleV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEffectStyleV2), 2376355695U) },
		{ FEffectSpecV2::StaticStruct, Z_Construct_UScriptStruct_FEffectSpecV2_Statics::NewStructOps, TEXT("EffectSpecV2"),&Z_Registration_Info_UScriptStruct_FEffectSpecV2, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FEffectSpecV2), 1453347971U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV2_h__Script_VFXAgentCore_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV2_h__Script_VFXAgentCore_4071547496{
	TEXT("/Script/VFXAgentCore"),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV2_h__Script_VFXAgentCore_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV2_h__Script_VFXAgentCore_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV2_h__Script_VFXAgentCore_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentCore_Public_EffectSpecV2_h__Script_VFXAgentCore_Statics::EnumInfo),
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
