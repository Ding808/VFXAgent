// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentNiagara/Public/NiagaraSystemGenerator.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeNiagaraSystemGenerator() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
NIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystemGenerator();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UNiagaraSystemGenerator_NoRegister();
// End Cross Module References

// Begin Class UNiagaraSystemGenerator
void UNiagaraSystemGenerator::StaticRegisterNativesUNiagaraSystemGenerator()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UNiagaraSystemGenerator);
UClass* Z_Construct_UClass_UNiagaraSystemGenerator_NoRegister()
{
	return UNiagaraSystemGenerator::StaticClass();
}
struct Z_Construct_UClass_UNiagaraSystemGenerator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "NiagaraSystemGenerator.h" },
		{ "ModuleRelativePath", "Public/NiagaraSystemGenerator.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TemplateSystem_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Optional template system used as a source of initialized emitters/modules.\n" },
#endif
		{ "ModuleRelativePath", "Public/NiagaraSystemGenerator.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Optional template system used as a source of initialized emitters/modules." },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_TemplateSystem;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UNiagaraSystemGenerator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UNiagaraSystemGenerator_Statics::NewProp_TemplateSystem = { "TemplateSystem", nullptr, (EPropertyFlags)0x0144000000002000, UECodeGen_Private::EPropertyGenFlags::Object | UECodeGen_Private::EPropertyGenFlags::ObjectPtr, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UNiagaraSystemGenerator, TemplateSystem), Z_Construct_UClass_UNiagaraSystem_NoRegister, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TemplateSystem_MetaData), NewProp_TemplateSystem_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UNiagaraSystemGenerator_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UNiagaraSystemGenerator_Statics::NewProp_TemplateSystem,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraSystemGenerator_Statics::PropPointers) < 2048);
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
	Z_Construct_UClass_UNiagaraSystemGenerator_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraSystemGenerator_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UNiagaraSystemGenerator_Statics::Class_MetaDataParams), Z_Construct_UClass_UNiagaraSystemGenerator_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UNiagaraSystemGenerator()
{
	if (!Z_Registration_Info_UClass_UNiagaraSystemGenerator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UNiagaraSystemGenerator.OuterSingleton, Z_Construct_UClass_UNiagaraSystemGenerator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UNiagaraSystemGenerator.OuterSingleton;
}
template<> VFXAGENTNIAGARA_API UClass* StaticClass<UNiagaraSystemGenerator>()
{
	return UNiagaraSystemGenerator::StaticClass();
}
UNiagaraSystemGenerator::UNiagaraSystemGenerator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UNiagaraSystemGenerator);
UNiagaraSystemGenerator::~UNiagaraSystemGenerator() {}
// End Class UNiagaraSystemGenerator

// Begin Registration
struct Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UNiagaraSystemGenerator, UNiagaraSystemGenerator::StaticClass, TEXT("UNiagaraSystemGenerator"), &Z_Registration_Info_UClass_UNiagaraSystemGenerator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UNiagaraSystemGenerator), 617558141U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h_3745475273(TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_VFXTesting_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_NiagaraSystemGenerator_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
