// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "BasicAssetGenService.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeBasicAssetGenService() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UBasicAssetGenService();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UBasicAssetGenService_NoRegister();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UBasicAssetGenService ****************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UBasicAssetGenService;
UClass* UBasicAssetGenService::GetPrivateStaticClass()
{
	using TClass = UBasicAssetGenService;
	if (!Z_Registration_Info_UClass_UBasicAssetGenService.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("BasicAssetGenService"),
			Z_Registration_Info_UClass_UBasicAssetGenService.InnerSingleton,
			StaticRegisterNativesUBasicAssetGenService,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UBasicAssetGenService.InnerSingleton;
}
UClass* Z_Construct_UClass_UBasicAssetGenService_NoRegister()
{
	return UBasicAssetGenService::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UBasicAssetGenService_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "BasicAssetGenService.h" },
		{ "ModuleRelativePath", "Public/BasicAssetGenService.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UBasicAssetGenService constinit property declarations ********************
// ********** End Class UBasicAssetGenService constinit property declarations **********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UBasicAssetGenService>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UBasicAssetGenService_Statics
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
void UBasicAssetGenService::StaticRegisterNativesUBasicAssetGenService()
{
}
UClass* Z_Construct_UClass_UBasicAssetGenService()
{
	if (!Z_Registration_Info_UClass_UBasicAssetGenService.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UBasicAssetGenService.OuterSingleton, Z_Construct_UClass_UBasicAssetGenService_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UBasicAssetGenService.OuterSingleton;
}
UBasicAssetGenService::UBasicAssetGenService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UBasicAssetGenService);
UBasicAssetGenService::~UBasicAssetGenService() {}
// ********** End Class UBasicAssetGenService ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h__Script_VFXAgentNiagara_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UBasicAssetGenService, UBasicAssetGenService::StaticClass, TEXT("UBasicAssetGenService"), &Z_Registration_Info_UClass_UBasicAssetGenService, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UBasicAssetGenService), 11879961U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h__Script_VFXAgentNiagara_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h__Script_VFXAgentNiagara_3739716987{
	TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h__Script_VFXAgentNiagara_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_BasicAssetGenService_h__Script_VFXAgentNiagara_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
