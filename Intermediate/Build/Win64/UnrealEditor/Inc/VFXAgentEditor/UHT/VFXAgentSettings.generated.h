// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "VFXAgentSettings.h"

#ifdef VFXAGENTEDITOR_VFXAgentSettings_generated_h
#error "VFXAgentSettings.generated.h already included, missing '#pragma once' in VFXAgentSettings.h"
#endif
#define VFXAGENTEDITOR_VFXAgentSettings_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UVFXAgentSettings ********************************************************
struct Z_Construct_UClass_UVFXAgentSettings_Statics;
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UVFXAgentSettings_NoRegister();

#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUVFXAgentSettings(); \
	friend struct ::Z_Construct_UClass_UVFXAgentSettings_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend VFXAGENTEDITOR_API UClass* ::Z_Construct_UClass_UVFXAgentSettings_NoRegister(); \
public: \
	DECLARE_CLASS2(UVFXAgentSettings, UDeveloperSettings, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/VFXAgentEditor"), Z_Construct_UClass_UVFXAgentSettings_NoRegister) \
	DECLARE_SERIALIZER(UVFXAgentSettings) \
	static constexpr const TCHAR* StaticConfigName() {return TEXT("VFXAgent");} \



#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UVFXAgentSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UVFXAgentSettings(UVFXAgentSettings&&) = delete; \
	UVFXAgentSettings(const UVFXAgentSettings&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UVFXAgentSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UVFXAgentSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UVFXAgentSettings) \
	NO_API virtual ~UVFXAgentSettings();


#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_7_PROLOG
#define FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_10_INCLASS_NO_PURE_DECLS \
	FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UVFXAgentSettings;

// ********** End Class UVFXAgentSettings **********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
