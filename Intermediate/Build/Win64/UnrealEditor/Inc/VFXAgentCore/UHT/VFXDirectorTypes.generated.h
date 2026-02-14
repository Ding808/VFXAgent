// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VFXDirectorTypes.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef VFXAGENTCORE_VFXDirectorTypes_generated_h
#error "VFXDirectorTypes.generated.h already included, missing '#pragma once' in VFXDirectorTypes.h"
#endif
#define VFXAGENTCORE_VFXDirectorTypes_generated_h

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_9_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXColorTheme_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXColorTheme>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_24_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXStyleSpec_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXStyleSpec>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_42_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXPlanEmitter_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXPlanEmitter>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_57_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXPlanEvent_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXPlanEvent>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_75_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXPlanLayer_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXPlanLayer>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_93_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXPlan_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXPlan>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_138_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXCurvePoint_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXCurvePoint>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_156_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXActionValue_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXActionValue>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_192_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXAction_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXAction>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_258_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXValidationTargets_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXValidationTargets>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_273_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXDirectorPlan_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXDirectorPlan>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h_291_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXExecutionReport_Statics; \
	VFXAGENTCORE_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTCORE_API UScriptStruct* StaticStruct<struct FVFXExecutionReport>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_VFXDirectorTypes_h


#define FOREACH_ENUM_EVFXACTIONTYPE(op) \
	op(EVFXActionType::CreateSystem) \
	op(EVFXActionType::AddEmitterFromTemplate) \
	op(EVFXActionType::AddModule) \
	op(EVFXActionType::SetParameter) \
	op(EVFXActionType::BindEventHandler) \
	op(EVFXActionType::EnableDrag) \
	op(EVFXActionType::CreateMaterialInstance) \
	op(EVFXActionType::AssignRendererMaterial) \
	op(EVFXActionType::CompileAndValidate) \
	op(EVFXActionType::RenderThumbnail) \
	op(EVFXActionType::Unknown) 

enum class EVFXActionType : uint8;
template<> struct TIsUEnumClass<EVFXActionType> { enum { Value = true }; };
template<> VFXAGENTCORE_API UEnum* StaticEnum<EVFXActionType>();

#define FOREACH_ENUM_EVFXVALUETYPE(op) \
	op(EVFXValueType::None) \
	op(EVFXValueType::Float) \
	op(EVFXValueType::Int) \
	op(EVFXValueType::Bool) \
	op(EVFXValueType::Vec2) \
	op(EVFXValueType::Vec3) \
	op(EVFXValueType::Vec4) \
	op(EVFXValueType::Color) \
	op(EVFXValueType::Curve) 

enum class EVFXValueType : uint8;
template<> struct TIsUEnumClass<EVFXValueType> { enum { Value = true }; };
template<> VFXAGENTCORE_API UEnum* StaticEnum<EVFXValueType>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
