// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentNiagara/Public/MaterialGenerator.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeMaterialGenerator() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UMaterialGenerator();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UMaterialGenerator_NoRegister();
// End Cross Module References

// Begin Class UMaterialGenerator
void UMaterialGenerator::StaticRegisterNativesUMaterialGenerator()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UMaterialGenerator);
UClass* Z_Construct_UClass_UMaterialGenerator_NoRegister()
{
	return UMaterialGenerator::StaticClass();
}
struct Z_Construct_UClass_UMaterialGenerator_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * Concrete implementation of material generation for VFX effects\n */" },
#endif
		{ "IncludePath", "MaterialGenerator.h" },
		{ "ModuleRelativePath", "Public/MaterialGenerator.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Concrete implementation of material generation for VFX effects" },
#endif
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UMaterialGenerator>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
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
UClass* Z_Construct_UClass_UMaterialGenerator()
{
	if (!Z_Registration_Info_UClass_UMaterialGenerator.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UMaterialGenerator.OuterSingleton, Z_Construct_UClass_UMaterialGenerator_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UMaterialGenerator.OuterSingleton;
}
template<> VFXAGENTNIAGARA_API UClass* StaticClass<UMaterialGenerator>()
{
	return UMaterialGenerator::StaticClass();
}
UMaterialGenerator::UMaterialGenerator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UMaterialGenerator);
UMaterialGenerator::~UMaterialGenerator() {}
// End Class UMaterialGenerator

// Begin Registration
struct Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UMaterialGenerator, UMaterialGenerator::StaticClass, TEXT("UMaterialGenerator"), &Z_Registration_Info_UClass_UMaterialGenerator, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UMaterialGenerator), 748567286U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_4107305420(TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_MaterialGenerator_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
