// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "MaterialGenerator.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef VFXAGENTNIAGARA_MaterialGenerator_generated_h
#error "MaterialGenerator.generated.h already included, missing '#pragma once' in MaterialGenerator.h"
#endif
#define VFXAGENTNIAGARA_MaterialGenerator_generated_h

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUMaterialGenerator(); \
	friend struct Z_Construct_UClass_UMaterialGenerator_Statics; \
public: \
	DECLARE_CLASS(UMaterialGenerator, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VFXAgentNiagara"), NO_API) \
	DECLARE_SERIALIZER(UMaterialGenerator)


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_14_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UMaterialGenerator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UMaterialGenerator(UMaterialGenerator&&); \
	UMaterialGenerator(const UMaterialGenerator&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UMaterialGenerator); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UMaterialGenerator); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UMaterialGenerator) \
	NO_API virtual ~UMaterialGenerator();


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_11_PROLOG
#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_14_INCLASS_NO_PURE_DECLS \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VFXAGENTNIAGARA_API UClass* StaticClass<class UMaterialGenerator>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
