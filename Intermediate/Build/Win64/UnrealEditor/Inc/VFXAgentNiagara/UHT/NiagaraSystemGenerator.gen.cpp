// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "NiagaraSystemGenerator.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
static_assert(!UE_WITH_CONSTINIT_UOBJECT, "This generated code can only be compiled with !UE_WITH_CONSTINIT_OBJECT");
void EmptyLinkFunctionForGeneratedCodeNiagaraSystemGenerator() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystemGenerator();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystemGenerator_NoRegister();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UNiagaraSystemGenerator **************************************************
FClassRegistrationInfo Z_Registration_Info_UClass_UNiagaraSystemGenerator;
UClass* UNiagaraSystemGenerator::GetPrivateStaticClass()
{
	using TClass = UNiagaraSystemGenerator;
	if (!Z_Registration_Info_UClass_UNiagaraSystemGenerator.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			TClass::StaticPackage(),
			TEXT("NiagaraSystemGenerator"),
			Z_Registration_Info_UClass_UNiagaraSystemGenerator.InnerSingleton,
			StaticRegisterNativesUNiagaraSystemGenerator,
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
	return Z_Registration_Info_UClass_UNiagaraSystemGenerator.InnerSingleton;
}
UClass* Z_Construct_UClass_UNiagaraSystemGenerator_NoRegister()
{
	return UNiagaraSystemGenerator::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UNiagaraSystemGenerator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "NiagaraSystemGenerator.h" },
		{ "ModuleRelativePath", "Public/NiagaraSystemGenerator.h" },
	};
#endif // WITH_METADATA

// ********** Begin Class UNiagaraSystemGenerator constinit property declarations ******************
// ********** End Class UNiagaraSystemGenerator constinit property declarations ********************
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNiagaraSystemGenerator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
}; // struct Z_Construct_UClass_UNiagaraSystemGenerator_Statics
UObject* (*const Z_Construct_UClass_UNiagaraSystemGenerator_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentNiagara,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraSystemGenerator_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UNiagaraSystemGenerator_Statics::ClassParams = {
	&UNiagaraSystemGenerator::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraSystemGenerator_Statics::Class_MetaDataParams), Z_Construct_UClass_UNiagaraSystemGenerator_Statics::Class_MetaDataParams)
};
void UNiagaraSystemGenerator::StaticRegisterNativesUNiagaraSystemGenerator()
{
}
UClass* Z_Construct_UClass_UNiagaraSystemGenerator()
{
	if (!Z_Registration_Info_UClass_UNiagaraSystemGenerator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNiagaraSystemGenerator.OuterSingleton, Z_Construct_UClass_UNiagaraSystemGenerator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNiagaraSystemGenerator.OuterSingleton;
}
UNiagaraSystemGenerator::UNiagaraSystemGenerator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR_NS(, UNiagaraSystemGenerator);
UNiagaraSystemGenerator::~UNiagaraSystemGenerator() {}
// ********** End Class UNiagaraSystemGenerator ****************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h__Script_VFXAgentNiagara_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNiagaraSystemGenerator, UNiagaraSystemGenerator::StaticClass, TEXT("UNiagaraSystemGenerator"), &Z_Registration_Info_UClass_UNiagaraSystemGenerator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNiagaraSystemGenerator), 3670434549U) },
	};
}; // Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h__Script_VFXAgentNiagara_Statics 
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h__Script_VFXAgentNiagara_1567852478{
	TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h__Script_VFXAgentNiagara_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_e__VFXAgent_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h__Script_VFXAgentNiagara_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0,
};
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
