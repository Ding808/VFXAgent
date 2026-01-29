// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentNiagara/Public/BasicAssetGenService.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeBasicAssetGenService() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UBasicAssetGenService();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UBasicAssetGenService_NoRegister();
// End Cross Module References

// Begin Class UBasicAssetGenService
void UBasicAssetGenService::StaticRegisterNativesUBasicAssetGenService()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UBasicAssetGenService);
UClass* Z_Construct_UClass_UBasicAssetGenService_NoRegister()
{
	return UBasicAssetGenService::StaticClass();
}
struct Z_Construct_UClass_UBasicAssetGenService_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "BasicAssetGenService.h" },
		{ "ModuleRelativePath", "Public/BasicAssetGenService.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBasicAssetGenService>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UBasicAssetGenService_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentNiagara,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicAssetGenService_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UBasicAssetGenService_Statics::ClassParams = {
	&UBasicAssetGenService::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UBasicAssetGenService_Statics::Class_MetaDataParams), Z_Construct_UClass_UBasicAssetGenService_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UBasicAssetGenService()
{
	if (!Z_Registration_Info_UClass_UBasicAssetGenService.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBasicAssetGenService.OuterSingleton, Z_Construct_UClass_UBasicAssetGenService_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBasicAssetGenService.OuterSingleton;
}
template<> VFXAGENTNIAGARA_API UClass* StaticClass<UBasicAssetGenService>()
{
	return UBasicAssetGenService::StaticClass();
}
UBasicAssetGenService::UBasicAssetGenService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UBasicAssetGenService);
UBasicAssetGenService::~UBasicAssetGenService() {}
// End Class UBasicAssetGenService

// Begin Registration
struct Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBasicAssetGenService, UBasicAssetGenService::StaticClass, TEXT("UBasicAssetGenService"), &Z_Registration_Info_UClass_UBasicAssetGenService, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBasicAssetGenService), 1161424616U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h_2313296780(TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
