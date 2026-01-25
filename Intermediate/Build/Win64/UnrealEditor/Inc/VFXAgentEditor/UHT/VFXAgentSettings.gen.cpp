// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentEditor/Public/VFXAgentSettings.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVFXAgentSettings() {}

// Begin Cross Module References
DEVELOPERSETTINGS_API UClass* Z_Construct_UClass_UDeveloperSettings();
UPackage* Z_Construct_UPackage__Script_VFXAgentEditor();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UVFXAgentSettings();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UVFXAgentSettings_NoRegister();
// End Cross Module References

// Begin Class UVFXAgentSettings
void UVFXAgentSettings::StaticRegisterNativesUVFXAgentSettings()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVFXAgentSettings);
UClass* Z_Construct_UClass_UVFXAgentSettings_NoRegister()
{
	return UVFXAgentSettings::StaticClass();
}
struct Z_Construct_UClass_UVFXAgentSettings_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "VFXAgentSettings.h" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LLMEndpoint_MetaData[] = {
		{ "Category", "LLM" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LLMModel_MetaData[] = {
		{ "Category", "LLM" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultOutputPath_MetaData[] = {
		{ "Category", "Generation" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_DefaultTemplatePath_MetaData[] = {
		{ "Category", "Generation" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_AssetNamePrefix_MetaData[] = {
		{ "Category", "Generation" },
		{ "ModuleRelativePath", "Public/VFXAgentSettings.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_LLMEndpoint;
	static const UECodeGen_Private::FStrPropertyParams NewProp_LLMModel;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultOutputPath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_DefaultTemplatePath;
	static const UECodeGen_Private::FStrPropertyParams NewProp_AssetNamePrefix;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVFXAgentSettings>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMEndpoint = { "LLMEndpoint", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, LLMEndpoint), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LLMEndpoint_MetaData), NewProp_LLMEndpoint_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMModel = { "LLMModel", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, LLMModel), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LLMModel_MetaData), NewProp_LLMModel_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultOutputPath = { "DefaultOutputPath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, DefaultOutputPath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultOutputPath_MetaData), NewProp_DefaultOutputPath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultTemplatePath = { "DefaultTemplatePath", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, DefaultTemplatePath), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_DefaultTemplatePath_MetaData), NewProp_DefaultTemplatePath_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_AssetNamePrefix = { "AssetNamePrefix", nullptr, (EPropertyFlags)0x0010000000004001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UVFXAgentSettings, AssetNamePrefix), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_AssetNamePrefix_MetaData), NewProp_AssetNamePrefix_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMEndpoint,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_LLMModel,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultOutputPath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_DefaultTemplatePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UVFXAgentSettings_Statics::NewProp_AssetNamePrefix,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UVFXAgentSettings_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDeveloperSettings,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UVFXAgentSettings_Statics::ClassParams = {
	&UVFXAgentSettings::StaticClass,
	"VFXAgent",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::PropPointers),
	0,
	0x001000A6u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXAgentSettings_Statics::Class_MetaDataParams), Z_Construct_UClass_UVFXAgentSettings_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UVFXAgentSettings()
{
	if (!Z_Registration_Info_UClass_UVFXAgentSettings.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVFXAgentSettings.OuterSingleton, Z_Construct_UClass_UVFXAgentSettings_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UVFXAgentSettings.OuterSingleton;
}
template<> VFXAGENTEDITOR_API UClass* StaticClass<UVFXAgentSettings>()
{
	return UVFXAgentSettings::StaticClass();
}
UVFXAgentSettings::UVFXAgentSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UVFXAgentSettings);
UVFXAgentSettings::~UVFXAgentSettings() {}
// End Class UVFXAgentSettings

// Begin Registration
struct Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UVFXAgentSettings, UVFXAgentSettings::StaticClass, TEXT("UVFXAgentSettings"), &Z_Registration_Info_UClass_UVFXAgentSettings, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVFXAgentSettings), 3015712139U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_2591311050(TEXT("/Script/VFXAgentEditor"),
	Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_E__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_VFXAgentSettings_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
