// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "VFXAgentNiagara/Public/VFXRecipeCompiler.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeVFXRecipeCompiler() {}

// Begin Cross Module References
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_VFXAgentNiagara();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UVFXRecipeCompiler();
VFXAGENTNIAGARA_API UClass* Z_Construct_UClass_UVFXRecipeCompiler_NoRegister();
// End Cross Module References

// Begin Class UVFXRecipeCompiler
void UVFXRecipeCompiler::StaticRegisterNativesUVFXRecipeCompiler()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UVFXRecipeCompiler);
UClass* Z_Construct_UClass_UVFXRecipeCompiler_NoRegister()
{
	return UVFXRecipeCompiler::StaticClass();
}
struct Z_Construct_UClass_UVFXRecipeCompiler_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "VFXRecipeCompiler.h" },
		{ "ModuleRelativePath", "Public/VFXRecipeCompiler.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UVFXRecipeCompiler>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UVFXRecipeCompiler_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_VFXAgentNiagara,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXRecipeCompiler_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UVFXRecipeCompiler_Statics::ClassParams = {
	&UVFXRecipeCompiler::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UVFXRecipeCompiler_Statics::Class_MetaDataParams), Z_Construct_UClass_UVFXRecipeCompiler_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UVFXRecipeCompiler()
{
	if (!Z_Registration_Info_UClass_UVFXRecipeCompiler.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UVFXRecipeCompiler.OuterSingleton, Z_Construct_UClass_UVFXRecipeCompiler_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UVFXRecipeCompiler.OuterSingleton;
}
template<> VFXAGENTNIAGARA_API UClass* StaticClass<UVFXRecipeCompiler>()
{
	return UVFXRecipeCompiler::StaticClass();
}
UVFXRecipeCompiler::UVFXRecipeCompiler(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UVFXRecipeCompiler);
UVFXRecipeCompiler::~UVFXRecipeCompiler() {}
// End Class UVFXRecipeCompiler

// Begin Registration
struct Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXRecipeCompiler_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UVFXRecipeCompiler, UVFXRecipeCompiler::StaticClass, TEXT("UVFXRecipeCompiler"), &Z_Registration_Info_UClass_UVFXRecipeCompiler, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UVFXRecipeCompiler), 289470247U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXRecipeCompiler_h_869066586(TEXT("/Script/VFXAgentNiagara"),
	Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXRecipeCompiler_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TST_Testing_Plugins_VFXAgent_Source_VFXAgentNiagara_Public_VFXRecipeCompiler_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
