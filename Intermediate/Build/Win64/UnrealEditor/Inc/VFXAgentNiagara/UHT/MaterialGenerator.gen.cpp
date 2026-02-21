// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "MaterialGenerator.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeMaterialGenerator() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UMaterialGenerator();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UMaterialGenerator_NoRegister();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UMaterialGenerator *******************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UMaterialGenerator;
UClass* UMaterialGenerator::GetPrivateStaticClass()
{
	using TClass = UMaterialGenerator;
	if (!Z_Registration_Info_UClass_UMaterialGenerator.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("MaterialGenerator"),
			Z_Registration_Info_UClass_UMaterialGenerator.InnerSingleton,
			StaticRegisterNativesUMaterialGenerator,
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
	return Z_Registration_Info_UClass_UMaterialGenerator.InnerSingleton;
}
UClass* Z_Construct_UClass_UMaterialGenerator_NoRegister()
{
	return UMaterialGenerator::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UMaterialGenerator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "Comment", "/**\n * Concrete implementation of material generation for VFX effects\n */" },
		{ "IncludePath", "MaterialGenerator.h" },
		{ "ModuleRelativePath", "Public/MaterialGenerator.h" },
		{ "ToolTip", "Concrete implementation of material generation for VFX effects" },
	};
#endif // WITH_METADATA

// ********** Begin Class UMaterialGenerator constinit property declarations ***********************
// ********** End Class UMaterialGenerator constinit property declarations *************************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMaterialGenerator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UMaterialGenerator_Statics
UObject* (*const Z_Construct_UClass_UMaterialGenerator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentNiagara,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UMaterialGenerator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UMaterialGenerator_Statics::ClassParams = {
	&UMaterialGenerator::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UMaterialGenerator_Statics::Class_MetaDataParams), Z_Construct_UClass_UMaterialGenerator_Statics::Class_MetaDataParams)
};
void UMaterialGenerator::StaticRegisterNativesUMaterialGenerator()
{
}
UClass* Z_Construct_UClass_UMaterialGenerator()
{
	if (!Z_Registration_Info_UClass_UMaterialGenerator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMaterialGenerator.OuterSingleton, Z_Construct_UClass_UMaterialGenerator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMaterialGenerator.OuterSingleton;
}
UMaterialGenerator::UMaterialGenerator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UMaterialGenerator);
UMaterialGenerator::~UMaterialGenerator() {}
// ********** End Class UMaterialGenerator *********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h__Script_VFXAgentNiagara_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMaterialGenerator, UMaterialGenerator::StaticClass, TEXT("UMaterialGenerator"), &Z_Registration_Info_UClass_UMaterialGenerator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMaterialGenerator), 1408293021U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h__Script_VFXAgentNiagara_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h__Script_VFXAgentNiagara_3191573169{
	TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h__Script_VFXAgentNiagara_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h__Script_VFXAgentNiagara_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
