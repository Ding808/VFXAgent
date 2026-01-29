// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentCore/Public/HttpLLMProvider.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHttpLLMProvider() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentCore();
VFXAGENTCORE_API UClass* Z_Construct_UClass_UHttpLLMProvider();
VFXAGENTCORE_API UClass* Z_Construct_UClass_UHttpLLMProvider_NoRegister();
VFXAGENTCORE_API UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend();
// End Cross Module References

// Begin Enum EVFXAgentLLMBackend
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EVFXAgentLLMBackend;
static UEnum* EVFXAgentLLMBackend_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EVFXAgentLLMBackend.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EVFXAgentLLMBackend.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend, (UObject*)Z_Construct_UPackage__Script_VFXAgentCore(), TEXT("EVFXAgentLLMBackend"));
	}
	return Z_Registration_Info_UEnum_EVFXAgentLLMBackend.OuterSingleton;
}
template<> VFXAGENTCORE_API UEnum* StaticEnum<EVFXAgentLLMBackend>()
{
	return EVFXAgentLLMBackend_StaticEnum();
}
struct Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Mock.DisplayName", "Mock" },
		{ "Mock.Name", "EVFXAgentLLMBackend::Mock" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
		{ "OllamaGenerate.DisplayName", "Ollama /api/generate" },
		{ "OllamaGenerate.Name", "EVFXAgentLLMBackend::OllamaGenerate" },
		{ "OpenAIChatCompletions.DisplayName", "OpenAI Chat Completions" },
		{ "OpenAIChatCompletions.Name", "EVFXAgentLLMBackend::OpenAIChatCompletions" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EVFXAgentLLMBackend::Mock", (int64)EVFXAgentLLMBackend::Mock },
		{ "EVFXAgentLLMBackend::OpenAIChatCompletions", (int64)EVFXAgentLLMBackend::OpenAIChatCompletions },
		{ "EVFXAgentLLMBackend::OllamaGenerate", (int64)EVFXAgentLLMBackend::OllamaGenerate },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_VFXAgentCore,
	nullptr,
	"EVFXAgentLLMBackend",
	"EVFXAgentLLMBackend",
	Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend_Statics::Enum_MetaDataParams), Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend()
{
	if (!Z_Registration_Info_UEnum_EVFXAgentLLMBackend.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EVFXAgentLLMBackend.InnerSingleton, Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EVFXAgentLLMBackend.InnerSingleton;
}
// End Enum EVFXAgentLLMBackend

// Begin Class UHttpLLMProvider Function Configure
struct Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics
{
	struct HttpLLMProvider_eventConfigure_Parms
	{
		EVFXAgentLLMBackend InBackend;
		FString InEndpoint;
		FString InModel;
		FString InApiKey;
		float InTimeoutSeconds;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "CPP_Default_InTimeoutSeconds", "30.000000" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InEndpoint_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InModel_MetaData[] = {
		{ "NativeConst", "" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_InApiKey_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_InBackend_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_InBackend;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InEndpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InModel;
	static const UECodeGen_Private::FStrPropertyParams NewProp_InApiKey;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_InTimeoutSeconds;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InBackend_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InBackend = { "InBackend", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HttpLLMProvider_eventConfigure_Parms, InBackend), Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend, METADATA_PARAMS(0, nullptr) }; // 722003213
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InEndpoint = { "InEndpoint", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HttpLLMProvider_eventConfigure_Parms, InEndpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InEndpoint_MetaData), NewProp_InEndpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InModel = { "InModel", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HttpLLMProvider_eventConfigure_Parms, InModel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InModel_MetaData), NewProp_InModel_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InApiKey = { "InApiKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HttpLLMProvider_eventConfigure_Parms, InApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_InApiKey_MetaData), NewProp_InApiKey_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InTimeoutSeconds = { "InTimeoutSeconds", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HttpLLMProvider_eventConfigure_Parms, InTimeoutSeconds), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InBackend_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InBackend,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InEndpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InModel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InApiKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::NewProp_InTimeoutSeconds,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHttpLLMProvider, nullptr, "Configure", nullptr, nullptr, Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::HttpLLMProvider_eventConfigure_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::HttpLLMProvider_eventConfigure_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHttpLLMProvider_Configure()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHttpLLMProvider_Configure_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHttpLLMProvider::execConfigure)
{
	P_GET_ENUM(EVFXAgentLLMBackend,Z_Param_InBackend);
	P_GET_PROPERTY(FStrProperty,Z_Param_InEndpoint);
	P_GET_PROPERTY(FStrProperty,Z_Param_InModel);
	P_GET_PROPERTY(FStrProperty,Z_Param_InApiKey);
	P_GET_PROPERTY(FFloatProperty,Z_Param_InTimeoutSeconds);
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->Configure(EVFXAgentLLMBackend(Z_Param_InBackend),Z_Param_InEndpoint,Z_Param_InModel,Z_Param_InApiKey,Z_Param_InTimeoutSeconds);
	P_NATIVE_END;
}
// End Class UHttpLLMProvider Function Configure

// Begin Class UHttpLLMProvider Function GetLastError
struct Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics
{
	struct HttpLLMProvider_eventGetLastError_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HttpLLMProvider_eventGetLastError_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHttpLLMProvider, nullptr, "GetLastError", nullptr, nullptr, Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::HttpLLMProvider_eventGetLastError_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::HttpLLMProvider_eventGetLastError_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHttpLLMProvider_GetLastError()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHttpLLMProvider_GetLastError_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHttpLLMProvider::execGetLastError)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetLastError();
	P_NATIVE_END;
}
// End Class UHttpLLMProvider Function GetLastError

// Begin Class UHttpLLMProvider Function GetLastRawRecipeJson
struct Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics
{
	struct HttpLLMProvider_eventGetLastRawRecipeJson_Parms
	{
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(HttpLLMProvider_eventGetLastRawRecipeJson_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHttpLLMProvider, nullptr, "GetLastRawRecipeJson", nullptr, nullptr, Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::PropPointers), sizeof(Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::HttpLLMProvider_eventGetLastRawRecipeJson_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::Function_MetaDataParams), Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::Function_MetaDataParams) };
static_assert(sizeof(Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::HttpLLMProvider_eventGetLastRawRecipeJson_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UHttpLLMProvider::execGetLastRawRecipeJson)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=P_THIS->GetLastRawRecipeJson();
	P_NATIVE_END;
}
// End Class UHttpLLMProvider Function GetLastRawRecipeJson

// Begin Class UHttpLLMProvider
void UHttpLLMProvider::StaticRegisterNativesUHttpLLMProvider()
{
	UClass* Class = UHttpLLMProvider::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "Configure", &UHttpLLMProvider::execConfigure },
		{ "GetLastError", &UHttpLLMProvider::execGetLastError },
		{ "GetLastRawRecipeJson", &UHttpLLMProvider::execGetLastRawRecipeJson },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UHttpLLMProvider);
UClass* Z_Construct_UClass_UHttpLLMProvider_NoRegister()
{
	return UHttpLLMProvider::StaticClass();
}
struct Z_Construct_UClass_UHttpLLMProvider_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "HttpLLMProvider.h" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Backend_MetaData[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Endpoint_MetaData[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Model_MetaData[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_ApiKey_MetaData[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TimeoutSeconds_MetaData[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastError_MetaData[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LastRawRecipeJson_MetaData[] = {
		{ "Category", "VFXAgent|LLM" },
		{ "ModuleRelativePath", "Public/HttpLLMProvider.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FBytePropertyParams NewProp_Backend_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Backend;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Endpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_Model;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ApiKey;
	static const UECodeGen_Private::FFloatPropertyParams NewProp_TimeoutSeconds;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LastError;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LastRawRecipeJson;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UHttpLLMProvider_Configure, "Configure" }, // 2445116401
		{ &Z_Construct_UFunction_UHttpLLMProvider_GetLastError, "GetLastError" }, // 2559575072
		{ &Z_Construct_UFunction_UHttpLLMProvider_GetLastRawRecipeJson, "GetLastRawRecipeJson" }, // 4030418761
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHttpLLMProvider>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Backend_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Backend = { "Backend", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHttpLLMProvider, Backend), Z_Construct_UEnum_VFXAgentCore_EVFXAgentLLMBackend, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Backend_MetaData), NewProp_Backend_MetaData) }; // 722003213
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Endpoint = { "Endpoint", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHttpLLMProvider, Endpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Endpoint_MetaData), NewProp_Endpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Model = { "Model", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHttpLLMProvider, Model), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Model_MetaData), NewProp_Model_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_ApiKey = { "ApiKey", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHttpLLMProvider, ApiKey), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_ApiKey_MetaData), NewProp_ApiKey_MetaData) };
const UECodeGen_Private::FFloatPropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_TimeoutSeconds = { "TimeoutSeconds", nullptr, (EPropertyFlags)0x0040000000000001, UECodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHttpLLMProvider, TimeoutSeconds), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TimeoutSeconds_MetaData), NewProp_TimeoutSeconds_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_LastError = { "LastError", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHttpLLMProvider, LastError), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastError_MetaData), NewProp_LastError_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_LastRawRecipeJson = { "LastRawRecipeJson", nullptr, (EPropertyFlags)0x0040000000020001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UHttpLLMProvider, LastRawRecipeJson), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LastRawRecipeJson_MetaData), NewProp_LastRawRecipeJson_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UHttpLLMProvider_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Backend_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Backend,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Endpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_Model,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_ApiKey,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_TimeoutSeconds,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_LastError,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UHttpLLMProvider_Statics::NewProp_LastRawRecipeJson,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHttpLLMProvider_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UHttpLLMProvider_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentCore,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UHttpLLMProvider_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UHttpLLMProvider_Statics::ClassParams = {
	&UHttpLLMProvider::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UHttpLLMProvider_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UHttpLLMProvider_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UHttpLLMProvider_Statics::Class_MetaDataParams), Z_Construct_UClass_UHttpLLMProvider_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UHttpLLMProvider()
{
	if (!Z_Registration_Info_UClass_UHttpLLMProvider.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UHttpLLMProvider.OuterSingleton, Z_Construct_UClass_UHttpLLMProvider_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UHttpLLMProvider.OuterSingleton;
}
template<> VFXAGENTCORE_API UClass* StaticClass<UHttpLLMProvider>()
{
	return UHttpLLMProvider::StaticClass();
}
UHttpLLMProvider::UHttpLLMProvider(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UHttpLLMProvider);
UHttpLLMProvider::~UHttpLLMProvider() {}
// End Class UHttpLLMProvider

// Begin Registration
struct Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ EVFXAgentLLMBackend_StaticEnum, TEXT("EVFXAgentLLMBackend"), &Z_Registration_Info_UEnum_EVFXAgentLLMBackend, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 722003213U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UHttpLLMProvider, UHttpLLMProvider::StaticClass, TEXT("UHttpLLMProvider"), &Z_Registration_Info_UClass_UHttpLLMProvider, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UHttpLLMProvider), 2905766652U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_2227347871(TEXT("/Script/VFXAgentCore"),
	Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_Statics::ClassInfo),
	nullptr, 0,
	Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentCore_Public_HttpLLMProvider_h_Statics::EnumInfo));
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
