// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "HttpLLMProvider.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
enum class EVFXAgentLLMBackend : uint8;
#ifdef VFXAGENTCORE_HttpLLMProvider_generated_h
#error "HttpLLMProvider.generated.h already included, missing '#pragma once' in HttpLLMProvider.h"
#endif
#define VFXAGENTCORE_HttpLLMProvider_generated_h

#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetLastRawRecipeJson); \
	DECLARE_FUNCTION(execGetLastError); \
	DECLARE_FUNCTION(execConfigure);


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_19_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHttpLLMProvider(); \
	friend struct Z_Construct_UClass_UHttpLLMProvider_Statics; \
public: \
	DECLARE_CLASS(UHttpLLMProvider, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/VFXAgentCore"), NO_API) \
	DECLARE_SERIALIZER(UHttpLLMProvider)


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_19_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHttpLLMProvider(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	UHttpLLMProvider(UHttpLLMProvider&&); \
	UHttpLLMProvider(const UHttpLLMProvider&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHttpLLMProvider); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHttpLLMProvider); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHttpLLMProvider) \
	NO_API virtual ~UHttpLLMProvider();


#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_16_PROLOG
#define FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_19_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_19_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_19_INCLASS_NO_PURE_DECLS \
	FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_19_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> VFXAGENTCORE_API UClass* StaticClass<class UHttpLLMProvider>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h


#define FOREACH_ENUM_EVFXAGENTLLMBACKEND(op) \
	op(EVFXAgentLLMBackend::Mock) \
	op(EVFXAgentLLMBackend::OpenAIChatCompletions) \
	op(EVFXAgentLLMBackend::OpenAIResponses) \
	op(EVFXAgentLLMBackend::OllamaGenerate) 

enum class EVFXAgentLLMBackend : uint8;
template<> struct TIsUEnumClass<EVFXAgentLLMBackend> { enum { Value = true }; };
template<> VFXAGENTCORE_API UEnum* StaticEnum<EVFXAgentLLMBackend>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
