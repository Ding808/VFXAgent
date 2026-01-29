// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VFXRecipe.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef VFXAGENTCORE_VFXRecipe_generated_h
#error "VFXRecipe.generated.h already included, missing '#pragma once' in VFXRecipe.h"
#endif
#define VFXAGENTCORE_VFXRecipe_generated_h

#define FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_9_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXEmitterRecipe_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXEmitterRecipe>();

#define FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_47_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXMaterialRecipe_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXMaterialRecipe>();

#define FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_72_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXPerSpawnInfo_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXPerSpawnInfo>();

#define FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_84_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXEmitterSpec_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXEmitterSpec>();

#define FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_122_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXEffectSpec_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXEffectSpec>();

#define FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_137_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXRepairReport_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXRepairReport>();

#define FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h_155_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXRecipe_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXRecipe>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXRecipe_h


#define FOREACH_ENUM_EVFXRENDERERTYPE(op) \
	op(EVFXRendererType::Sprite) \
	op(EVFXRendererType::Ribbon) \
	op(EVFXRendererType::Light) 

enum class EVFXRendererType : uint8;
template<> struct TIsUEnumClass<EVFXRendererType> { enum { Value = true }; };
template<> VFXAGENTCORE_API UEnum* StaticEnum<EVFXRendererType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
