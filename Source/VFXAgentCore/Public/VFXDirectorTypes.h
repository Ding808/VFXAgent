#pragma once

#include "CoreMinimal.h"
#include "VFXDirectorTypes.generated.h"

USTRUCT(BlueprintType)
struct FVFXColorTheme
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Primary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Secondary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Accent;
};

USTRUCT(BlueprintType)
struct FVFXStyleSpec
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FString> Keywords;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVFXColorTheme ColorTheme;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float Intensity = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float Scale = 1.0f;
};

USTRUCT(BlueprintType)
struct FVFXPlanEmitter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Alias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Template;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Role;
};

USTRUCT(BlueprintType)
struct FVFXPlanEvent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Source;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Handler;
};

USTRUCT(BlueprintType)
struct FVFXPlanLayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString ArchetypeTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FVFXPlanEmitter> Emitters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FVFXPlanEvent> Events;
};

USTRUCT(BlueprintType)
struct FVFXPlan
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Version = TEXT("1.0");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVFXStyleSpec Style;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FVFXPlanLayer> Layers;
};

UENUM(BlueprintType)
enum class EVFXActionType : uint8
{
	CreateSystem,
	AddEmitterFromTemplate,
	AddModule,
	SetParameter,
	BindEventHandler,
	EnableDrag,
	CreateMaterialInstance,
	AssignRendererMaterial,
	CompileAndValidate,
	RenderThumbnail,
	Unknown
};

UENUM(BlueprintType)
enum class EVFXValueType : uint8
{
	None,
	Float,
	Int,
	Bool,
	Vec2,
	Vec3,
	Vec4,
	Color,
	Curve
};

USTRUCT(BlueprintType)
struct FVFXCurvePoint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float Time = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float Value = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float ArriveTangent = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float LeaveTangent = 0.0f;
};

USTRUCT(BlueprintType)
struct FVFXActionValue
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	EVFXValueType Type = EVFXValueType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float FloatValue = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	int32 IntValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	bool BoolValue = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVector2D Vec2 = FVector2D::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVector Vec3 = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVector4 Vec4 = FVector4(0, 0, 0, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FLinearColor Color = FLinearColor::Transparent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FVFXCurvePoint> Curve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString RawJson;
};

USTRUCT(BlueprintType)
struct FVFXAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	EVFXActionType Type = EVFXActionType::Unknown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString System;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Path;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Template;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Alias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString ParamName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVFXActionValue Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Module;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Stack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Handler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float DragCoef = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	float InheritVel = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Parent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Out;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TMap<FString, FVFXActionValue> Params;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString CameraPreset;
};

USTRUCT(BlueprintType)
struct FVFXValidationTargets
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVector BoundsMin = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVector BoundsMax = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVector2D ParticleCountRange = FVector2D(0, 0);
};

USTRUCT(BlueprintType)
struct FVFXDirectorPlan
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVFXPlan Plan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FVFXAction> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FVFXValidationTargets Validation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString RawJson;
};

USTRUCT(BlueprintType)
struct FVFXExecutionReport
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	bool bSuccess = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FString> Logs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FString> Warnings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FString> Errors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	TArray<FString> GeneratedAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFXAgent|Director")
	FString ThumbnailPath;
};
