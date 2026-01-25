// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentEditor/Public/MockLLMProvider.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMockLLMProvider() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentEditor();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UMockLLMProvider();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UMockLLMProvider_NoRegister();
// End Cross Module References

// Begin Class UMockLLMProvider
void UMockLLMProvider::StaticRegisterNativesUMockLLMProvider()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMockLLMProvider);
UClass* Z_Construct_UClass_UMockLLMProvider_NoRegister()
{
	return UMockLLMProvider::StaticClass();
}
struct Z_Construct_UClass_UMockLLMProvider_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MockLLMProvider.h" },
		{ "ModuleRelativePath", "Public/MockLLMProvider.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMockLLMProvider>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UMockLLMProvider_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMockLLMProvider_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMockLLMProvider_Statics::ClassParams = {
	&UMockLLMProvider::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMockLLMProvider_Statics::Class_MetaDataParams), Z_Construct_UClass_UMockLLMProvider_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UMockLLMProvider()
{
	if (!Z_Registration_Info_UClass_UMockLLMProvider.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMockLLMProvider.OuterSingleton, Z_Construct_UClass_UMockLLMProvider_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMockLLMProvider.OuterSingleton;
}
template<> VFXAGENTEDITOR_API UClass* StaticClass<UMockLLMProvider>()
{
	return UMockLLMProvider::StaticClass();
}
UMockLLMProvider::UMockLLMProvider(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMockLLMProvider);
UMockLLMProvider::~UMockLLMProvider() {}
// End Class UMockLLMProvider

// Begin Registration
struct Z_CompiledInDeferFile_FID_HostProject_Plugins_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMockLLMProvider, UMockLLMProvider::StaticClass, TEXT("UMockLLMProvider"), &Z_Registration_Info_UClass_UMockLLMProvider, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMockLLMProvider), 417268716U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_HostProject_Plugins_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h_4024395999(TEXT("/Script/VFXAgentEditor"),
	Z_CompiledInDeferFile_FID_HostProject_Plugins_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_HostProject_Plugins_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
