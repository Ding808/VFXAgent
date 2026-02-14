// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VFXIterativeOptimizer.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UNiagaraSystem;
struct FVFXOptimizationConfig;
struct FVFXOptimizationResult;
struct FVFXRecipe;
#ifdef VFXAGENTNIAGARA_VFXIterativeOptimizer_generated_h
#error "VFXIterativeOptimizer.generated.h already included, missing '#pragma once' in VFXIterativeOptimizer.h"
#endif
#define VFXAGENTNIAGARA_VFXIterativeOptimizer_generated_h

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_14_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXOptimizationResult_Statics; \
	VFXAGENTNIAGARA_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTNIAGARA_API UScriptStruct* StaticStruct<struct FVFXOptimizationResult>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_38_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FVFXOptimizationConfig_Statics; \
	VFXAGENTNIAGARA_API static class UScriptStruct* StaticStruct();


template<> VFXAGENTNIAGARA_API UScriptStruct* StaticStruct<struct FVFXOptimizationConfig>();

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execEvaluateEffect);


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUVFXIterativeOptimizer(); \
	friend struct Z_Construct_UClass_UVFXIterativeOptimizer_Statics; \
public: \
	DECLARE_CLASS(UVFXIterativeOptimizer, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VFXAgentNiagara"), NO_API) \
	DECLARE_SERIALIZER(UVFXIterativeOptimizer)


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UVFXIterativeOptimizer(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UVFXIterativeOptimizer(UVFXIterativeOptimizer&&); \
	UVFXIterativeOptimizer(const UVFXIterativeOptimizer&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UVFXIterativeOptimizer); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UVFXIterativeOptimizer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UVFXIterativeOptimizer) \
	NO_API virtual ~UVFXIterativeOptimizer();


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_59_PROLOG
#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_INCLASS_NO_PURE_DECLS \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h_62_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VFXAGENTNIAGARA_API UClass* StaticClass<class UVFXIterativeOptimizer>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXIterativeOptimizer_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
