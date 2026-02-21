// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VFXIterativeOptimizer.h"

#ifdef VFXAGENTNIAGARA_VFXIterativeOptimizer_generated_h
#error "VFXIterativeOptimizer.generated.h already included, missing '#pragma once' in VFXIterativeOptimizer.h"
#endif
#define VFXAGENTNIAGARA_VFXIterativeOptimizer_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UNiagaraSystem;
struct FVFXOptimizationConfig;
struct FVFXOptimizationResult;
struct FVFXRecipe;

// ********** Begin ScriptStruct FVFXOptimizationResult ********************************************
struct Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics;
#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_14_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics; \
	VFXAGENTNIAGARA_API static class UScriptStruct* StaticStruct();


struct FVFXOptimizationResult;
// ********** End ScriptStruct FVFXOptimizationResult **********************************************

// ********** Begin ScriptStruct FVFXOptimizationConfig ********************************************
struct Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics;
#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_38_GENERATED_BODY \
	friend struct ::Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics; \
	VFXAGENTNIAGARA_API static class UScriptStruct* StaticStruct();


struct FVFXOptimizationConfig;
// ********** End ScriptStruct FVFXOptimizationConfig **********************************************

// ********** Begin Class UVFXIterativeOptimizer ***************************************************
#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execEvaluateEffect);


struct Z_Construct_UClass_UVFXIterativeOptimizer_Statics;
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UVFXIterativeOptimizer_NoRegister();

#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUVFXIterativeOptimizer(); \
	friend struct ::Z_Construct_UClass_UVFXIterativeOptimizer_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend VFXAGENTNIAGARA_API UClass* ::Z_Construct_UClass_UVFXIterativeOptimizer_NoRegister(); \
public: \
	DECLARE_CLASS2(UVFXIterativeOptimizer, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VFXAgentNiagara"), Z_Construct_UClass_UVFXIterativeOptimizer_NoRegister) \
	DECLARE_SERIALIZER(UVFXIterativeOptimizer)


#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UVFXIterativeOptimizer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UVFXIterativeOptimizer(UVFXIterativeOptimizer&&) = delete; \
	UVFXIterativeOptimizer(const UVFXIterativeOptimizer&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UVFXIterativeOptimizer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UVFXIterativeOptimizer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UVFXIterativeOptimizer) \
	NO_API virtual ~UVFXIterativeOptimizer();


#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_59_PROLOG
#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_INCLASS_NO_PURE_DECLS \
	FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UVFXIterativeOptimizer;

// ********** End Class UVFXIterativeOptimizer *****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
