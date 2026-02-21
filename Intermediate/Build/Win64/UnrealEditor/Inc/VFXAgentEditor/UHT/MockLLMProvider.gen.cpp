// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MockLLMProvider.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMockLLMProvider() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentEditor();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UMockLLMProvider();
VFXAGENTEDITOR_API UClass* Z_Construct_UClass_UMockLLMProvider_NoRegister();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMockLLMProvider *********************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMockLLMProvider;
UClass* UMockLLMProvider::GetPrivateStaticClass()
{
	using TClass = UMockLLMProvider;
	if (!Z_Registration_Info_UClass_UMockLLMProvider.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MockLLMProvider"),
			Z_Registration_Info_UClass_UMockLLMProvider.InnerSingleton,
			StaticRegisterNativesUMockLLMProvider,
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
	return Z_Registration_Info_UClass_UMockLLMProvider.InnerSingleton;
}
UClass* Z_Construct_UClass_UMockLLMProvider_NoRegister()
{
	return UMockLLMProvider::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMockLLMProvider_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "MockLLMProvider.h" },
		{ "ModuleRelativePath", "Public/MockLLMProvider.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UMockLLMProvider constinit property declarations *************************
// ********** End Class UMockLLMProvider constinit property declarations ***************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMockLLMProvider>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMockLLMProvider_Statics
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
void UMockLLMProvider::StaticRegisterNativesUMockLLMProvider()
{
}
UClass* Z_Construct_UClass_UMockLLMProvider()
{
	if (!Z_Registration_Info_UClass_UMockLLMProvider.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMockLLMProvider.OuterSingleton, Z_Construct_UClass_UMockLLMProvider_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMockLLMProvider.OuterSingleton;
}
UMockLLMProvider::UMockLLMProvider(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMockLLMProvider);
UMockLLMProvider::~UMockLLMProvider() {}
// ********** End Class UMockLLMProvider ***********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h__Script_VFXAgentEditor_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMockLLMProvider, UMockLLMProvider::StaticClass, TEXT("UMockLLMProvider"), &Z_Registration_Info_UClass_UMockLLMProvider, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMockLLMProvider), 881788419U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h__Script_VFXAgentEditor_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h__Script_VFXAgentEditor_3691876363{
	TEXT("/Script/VFXAgentEditor"),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h__Script_VFXAgentEditor_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentEditor_Public_MockLLMProvider_h__Script_VFXAgentEditor_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
