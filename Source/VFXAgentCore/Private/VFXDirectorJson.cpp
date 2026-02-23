#include "VFXDirectorJson.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "JsonObjectConverter.h"

static bool ParseDirectorJsonObject(const FString& JsonText, TSharedPtr<FJsonObject>& OutObj, FString& OutError)
{
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonText);
	if (!FJsonSerializer::Deserialize(Reader, OutObj) || !OutObj.IsValid())
	{
		OutError = TEXT("Invalid JSON object");
		return false;
	}
	return true;
}

static bool GetStringFieldRequired(const TSharedPtr<FJsonObject>& Obj, const FString& Field, FString& OutValue, FString& OutError)
{
	if (!Obj.IsValid() || !Obj->TryGetStringField(Field, OutValue))
	{
		OutError = FString::Printf(TEXT("Missing or invalid field: %s"), *Field);
		return false;
	}
	OutValue.TrimStartAndEndInline();
	if (OutValue.IsEmpty())
	{
		OutError = FString::Printf(TEXT("Empty field: %s"), *Field);
		return false;
	}
	return true;
}

static bool GetNumberFieldRequired(const TSharedPtr<FJsonObject>& Obj, const FString& Field, double& OutValue, FString& OutError)
{
	if (!Obj.IsValid() || !Obj->TryGetNumberField(Field, OutValue))
	{
		OutError = FString::Printf(TEXT("Missing or invalid field: %s"), *Field);
		return false;
	}
	return true;
}

static EVFXActionType ActionTypeFromString(const FString& In)
{
	const FString Lower = In.ToLower();
	if (Lower == TEXT("createsystem")) return EVFXActionType::CreateSystem;
	if (Lower == TEXT("addemitterfromtemplate")) return EVFXActionType::AddEmitterFromTemplate;
	if (Lower == TEXT("addmodule")) return EVFXActionType::AddModule;
	if (Lower == TEXT("setparameter") || Lower == TEXT("setparam")) return EVFXActionType::SetParameter;
	if (Lower == TEXT("bindeventhandler")) return EVFXActionType::BindEventHandler;
	if (Lower == TEXT("enabledrag")) return EVFXActionType::EnableDrag;
	if (Lower == TEXT("creatematerialinstance")) return EVFXActionType::CreateMaterialInstance;
	if (Lower == TEXT("assignrenderermaterial")) return EVFXActionType::AssignRendererMaterial;
	if (Lower == TEXT("compileandvalidate")) return EVFXActionType::CompileAndValidate;
	if (Lower == TEXT("renderthumbnail")) return EVFXActionType::RenderThumbnail;
	return EVFXActionType::Unknown;
}

static FString JsonValueToString(const TSharedPtr<FJsonValue>& Value)
{
	FString Out;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Out);
	FJsonSerializer::Serialize(Value.ToSharedRef(), TEXT(""), Writer);
	return Out;
}

bool FVFXDirectorJson::ParseActionValue(const TSharedPtr<FJsonValue>& JsonValue, const FString& ParamName, FVFXActionValue& OutValue, FString& OutError)
{
	if (!JsonValue.IsValid())
	{
		OutError = TEXT("Value is null");
		return false;
	}

	OutValue.RawJson = JsonValueToString(JsonValue);

	if (JsonValue->Type == EJson::Boolean)
	{
		OutValue.Type = EVFXValueType::Bool;
		OutValue.BoolValue = JsonValue->AsBool();
		return true;
	}
	if (JsonValue->Type == EJson::Number)
	{
		const double Num = JsonValue->AsNumber();
		const double Rounded = FMath::RoundToDouble(Num);
		if (FMath::IsNearlyEqual(Num, Rounded))
		{
			OutValue.Type = EVFXValueType::Int;
			OutValue.IntValue = (int32)Rounded;
		}
		else
		{
			OutValue.Type = EVFXValueType::Float;
			OutValue.FloatValue = (float)Num;
		}
		return true;
	}
	if (JsonValue->Type == EJson::String)
	{
		OutValue.Type = EVFXValueType::None;
		return true;
	}
	if (JsonValue->Type == EJson::Array)
	{
		const TArray<TSharedPtr<FJsonValue>> Arr = JsonValue->AsArray();
		if (Arr.Num() == 2)
		{
			OutValue.Type = EVFXValueType::Vec2;
			OutValue.Vec2 = FVector2D((float)Arr[0]->AsNumber(), (float)Arr[1]->AsNumber());
			return true;
		}
		if (Arr.Num() == 3)
		{
			OutValue.Type = EVFXValueType::Vec3;
			OutValue.Vec3 = FVector((float)Arr[0]->AsNumber(), (float)Arr[1]->AsNumber(), (float)Arr[2]->AsNumber());
			return true;
		}
		if (Arr.Num() == 4)
		{
			const FString Lower = ParamName.ToLower();
			const bool bLooksLikeColor = Lower.Contains(TEXT("color")) || Lower.Contains(TEXT("tint")) || Lower.Contains(TEXT("emissive"));
			if (bLooksLikeColor)
			{
				OutValue.Type = EVFXValueType::Color;
				OutValue.Color = FLinearColor((float)Arr[0]->AsNumber(), (float)Arr[1]->AsNumber(), (float)Arr[2]->AsNumber(), (float)Arr[3]->AsNumber());
				return true;
			}
			OutValue.Type = EVFXValueType::Vec4;
			OutValue.Vec4 = FVector4((float)Arr[0]->AsNumber(), (float)Arr[1]->AsNumber(), (float)Arr[2]->AsNumber(), (float)Arr[3]->AsNumber());
			return true;
		}

		OutError = TEXT("Unsupported array value size");
		return false;
	}
	if (JsonValue->Type == EJson::Object)
	{
		const TSharedPtr<FJsonObject> Obj = JsonValue->AsObject();
		FString TypeStr;
		if (Obj.IsValid() && Obj->TryGetStringField(TEXT("type"), TypeStr))
		{
			const FString Lower = TypeStr.ToLower();
			if (Lower == TEXT("color"))
			{
				const TArray<TSharedPtr<FJsonValue>> Arr = Obj->GetArrayField(TEXT("value"));
				if (Arr.Num() == 3 || Arr.Num() == 4)
				{
					OutValue.Type = EVFXValueType::Color;
					const float A = (Arr.Num() == 4) ? (float)Arr[3]->AsNumber() : 1.0f;
					OutValue.Color = FLinearColor((float)Arr[0]->AsNumber(), (float)Arr[1]->AsNumber(), (float)Arr[2]->AsNumber(), A);
					return true;
				}
			}
			if (Lower == TEXT("vec4"))
			{
				const TArray<TSharedPtr<FJsonValue>> Arr = Obj->GetArrayField(TEXT("value"));
				if (Arr.Num() == 4)
				{
					OutValue.Type = EVFXValueType::Vec4;
					OutValue.Vec4 = FVector4((float)Arr[0]->AsNumber(), (float)Arr[1]->AsNumber(), (float)Arr[2]->AsNumber(), (float)Arr[3]->AsNumber());
					return true;
				}
			}
			if (Lower == TEXT("curve"))
			{
				OutValue.Type = EVFXValueType::Curve;
				const TArray<TSharedPtr<FJsonValue>> Points = Obj->GetArrayField(TEXT("points"));
				for (const TSharedPtr<FJsonValue>& P : Points)
				{
					const TArray<TSharedPtr<FJsonValue>> Pair = P->AsArray();
					if (Pair.Num() >= 2)
					{
						FVFXCurvePoint CP;
						CP.Time = (float)Pair[0]->AsNumber();
						CP.Value = (float)Pair[1]->AsNumber();
						OutValue.Curve.Add(CP);
					}
				}
				return true;
			}
		}
	}

	OutError = TEXT("Unsupported value type");
	return false;
}

bool FVFXDirectorJson::ParseDirectorJson(const FString& JsonText, FVFXDirectorPlan& OutPlan, FString& OutError)
{
	TSharedPtr<FJsonObject> Root;
	if (!ParseDirectorJsonObject(JsonText, Root, OutError))
	{
		return false;
	}

	OutPlan = FVFXDirectorPlan();
	OutPlan.RawJson = JsonText;

	FString VersionStr;
	if (!GetStringFieldRequired(Root, TEXT("version"), VersionStr, OutError))
	{
		return false;
	}
	OutPlan.Plan.Version = VersionStr;

	TSharedPtr<FJsonObject> StyleObj = Root->GetObjectField(TEXT("style"));
	if (!StyleObj.IsValid())
	{
		OutError = TEXT("Missing style object");
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>> Keywords = StyleObj->GetArrayField(TEXT("keywords"));
	for (const TSharedPtr<FJsonValue>& K : Keywords)
	{
		OutPlan.Plan.Style.Keywords.Add(K->AsString());
	}

	TSharedPtr<FJsonObject> ThemeObj = StyleObj->GetObjectField(TEXT("colorTheme"));
	if (!ThemeObj.IsValid())
	{
		OutError = TEXT("Missing style.colorTheme");
		return false;
	}
	if (!GetStringFieldRequired(ThemeObj, TEXT("primary"), OutPlan.Plan.Style.ColorTheme.Primary, OutError)) return false;
	if (!GetStringFieldRequired(ThemeObj, TEXT("secondary"), OutPlan.Plan.Style.ColorTheme.Secondary, OutError)) return false;
	if (!GetStringFieldRequired(ThemeObj, TEXT("accent"), OutPlan.Plan.Style.ColorTheme.Accent, OutError)) return false;

	double Intensity = 1.0;
	double Scale = 1.0;
	if (!GetNumberFieldRequired(StyleObj, TEXT("intensity"), Intensity, OutError)) return false;
	if (!GetNumberFieldRequired(StyleObj, TEXT("scale"), Scale, OutError)) return false;
	OutPlan.Plan.Style.Intensity = (float)Intensity;
	OutPlan.Plan.Style.Scale = (float)Scale;

	const TArray<TSharedPtr<FJsonValue>> Layers = Root->GetArrayField(TEXT("layers"));
	if (Layers.Num() == 0)
	{
		OutError = TEXT("Missing layers array");
		return false;
	}

	for (const TSharedPtr<FJsonValue>& LayerVal : Layers)
	{
		TSharedPtr<FJsonObject> LayerObj = LayerVal->AsObject();
		if (!LayerObj.IsValid())
		{
			OutError = TEXT("Invalid layer object");
			return false;
		}

		FVFXPlanLayer Layer;
		if (!GetStringFieldRequired(LayerObj, TEXT("name"), Layer.Name, OutError)) return false;
		if (!GetStringFieldRequired(LayerObj, TEXT("archetypeTag"), Layer.ArchetypeTag, OutError)) return false;

		const TArray<TSharedPtr<FJsonValue>> Emitters = LayerObj->GetArrayField(TEXT("emitters"));
		if (Emitters.Num() == 0)
		{
			OutError = TEXT("Layer has no emitters");
			return false;
		}
		for (const TSharedPtr<FJsonValue>& EVal : Emitters)
		{
			TSharedPtr<FJsonObject> EObj = EVal->AsObject();
			if (!EObj.IsValid())
			{
				OutError = TEXT("Invalid emitter object");
				return false;
			}
			FVFXPlanEmitter Emitter;
			if (!GetStringFieldRequired(EObj, TEXT("alias"), Emitter.Alias, OutError)) return false;
			if (!GetStringFieldRequired(EObj, TEXT("template"), Emitter.Template, OutError)) return false;
			if (!GetStringFieldRequired(EObj, TEXT("role"), Emitter.Role, OutError)) return false;
			Layer.Emitters.Add(Emitter);
		}

		if (LayerObj->HasTypedField<EJson::Array>(TEXT("events")))
		{
			const TArray<TSharedPtr<FJsonValue>> Events = LayerObj->GetArrayField(TEXT("events"));
			for (const TSharedPtr<FJsonValue>& EV : Events)
			{
				TSharedPtr<FJsonObject> EventObj = EV->AsObject();
				if (!EventObj.IsValid())
				{
					OutError = TEXT("Invalid event object");
					return false;
				}
				FVFXPlanEvent Event;
				if (!GetStringFieldRequired(EventObj, TEXT("source"), Event.Source, OutError)) return false;
				if (!GetStringFieldRequired(EventObj, TEXT("event"), Event.Event, OutError)) return false;
				if (!GetStringFieldRequired(EventObj, TEXT("target"), Event.Target, OutError)) return false;
				if (!GetStringFieldRequired(EventObj, TEXT("handler"), Event.Handler, OutError)) return false;
				Layer.Events.Add(Event);
			}
		}

		OutPlan.Plan.Layers.Add(Layer);
	}

	const TArray<TSharedPtr<FJsonValue>> Actions = Root->GetArrayField(TEXT("actions"));
	if (Actions.Num() == 0)
	{
		OutError = TEXT("Missing actions array");
		return false;
	}

	for (const TSharedPtr<FJsonValue>& ActionVal : Actions)
	{
		TSharedPtr<FJsonObject> AObj = ActionVal->AsObject();
		if (!AObj.IsValid())
		{
			OutError = TEXT("Invalid action object");
			return false;
		}

		FString TypeStr;
		if (!GetStringFieldRequired(AObj, TEXT("type"), TypeStr, OutError)) return false;
		FVFXAction Action;
		Action.Type = ActionTypeFromString(TypeStr);
		if (Action.Type == EVFXActionType::Unknown)
		{
			OutError = FString::Printf(TEXT("Unknown action type: %s"), *TypeStr);
			return false;
		}

		switch (Action.Type)
		{
		case EVFXActionType::CreateSystem:
			if (!GetStringFieldRequired(AObj, TEXT("name"), Action.Name, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("path"), Action.Path, OutError)) return false;
			break;
		case EVFXActionType::AddEmitterFromTemplate:
			if (!GetStringFieldRequired(AObj, TEXT("system"), Action.System, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("template"), Action.Template, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("alias"), Action.Alias, OutError)) return false;
			break;
		case EVFXActionType::AddModule:
			if (!GetStringFieldRequired(AObj, TEXT("target"), Action.Target, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("module"), Action.Module, OutError)) return false;
			AObj->TryGetStringField(TEXT("stack"), Action.Stack);
			break;
		case EVFXActionType::SetParameter:
			if (!GetStringFieldRequired(AObj, TEXT("target"), Action.Target, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("name"), Action.ParamName, OutError)) return false;
			{
				const TSharedPtr<FJsonValue>* ValueFieldPtr = AObj->Values.Find(TEXT("value"));
				if (!ValueFieldPtr || !ValueFieldPtr->IsValid())
				{
					OutError = TEXT("Missing value field");
					return false;
				}
				if (!ParseActionValue(*ValueFieldPtr, Action.ParamName, Action.Value, OutError)) return false;
			}
			break;
		case EVFXActionType::BindEventHandler:
			if (!GetStringFieldRequired(AObj, TEXT("source"), Action.Target, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("event"), Action.Event, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("target"), Action.Alias, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("handler"), Action.Handler, OutError)) return false;
			break;
		case EVFXActionType::EnableDrag:
			if (!GetStringFieldRequired(AObj, TEXT("target"), Action.Target, OutError)) return false;
			if (!AObj->TryGetNumberField(TEXT("dragCoef"), Action.DragCoef))
			{
				OutError = TEXT("Missing dragCoef");
				return false;
			}
			AObj->TryGetNumberField(TEXT("inheritVel"), Action.InheritVel);
			break;
		case EVFXActionType::CreateMaterialInstance:
			if (!GetStringFieldRequired(AObj, TEXT("parent"), Action.Parent, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("out"), Action.Out, OutError)) return false;
			if (AObj->HasTypedField<EJson::Object>(TEXT("params")))
			{
				TSharedPtr<FJsonObject> ParamsObj = AObj->GetObjectField(TEXT("params"));
				for (const auto& KV : ParamsObj->Values)
				{
					FVFXActionValue ParamValue;
					FString ParamErr;
					if (!ParseActionValue(KV.Value, KV.Key, ParamValue, ParamErr))
					{
						OutError = FString::Printf(TEXT("Material param '%s' invalid: %s"), *KV.Key, *ParamErr);
						return false;
					}
					Action.Params.Add(KV.Key, ParamValue);
				}
			}
			break;
		case EVFXActionType::AssignRendererMaterial:
			if (!GetStringFieldRequired(AObj, TEXT("target"), Action.Target, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("material"), Action.Material, OutError)) return false;
			break;
		case EVFXActionType::CompileAndValidate:
			if (!GetStringFieldRequired(AObj, TEXT("system"), Action.System, OutError)) return false;
			break;
		case EVFXActionType::RenderThumbnail:
			if (!GetStringFieldRequired(AObj, TEXT("system"), Action.System, OutError)) return false;
			if (!GetStringFieldRequired(AObj, TEXT("out"), Action.Out, OutError)) return false;
			AObj->TryGetStringField(TEXT("cameraPreset"), Action.CameraPreset);
			break;
		default:
			break;
		}

		OutPlan.Actions.Add(Action);
	}

	if (Root->HasTypedField<EJson::Object>(TEXT("validationTargets")))
	{
		TSharedPtr<FJsonObject> ValObj = Root->GetObjectField(TEXT("validationTargets"));
		if (ValObj->HasTypedField<EJson::Array>(TEXT("bounds")))
		{
			const TArray<TSharedPtr<FJsonValue>> Bounds = ValObj->GetArrayField(TEXT("bounds"));
			if (Bounds.Num() >= 2)
			{
				const TArray<TSharedPtr<FJsonValue>> Min = Bounds[0]->AsArray();
				const TArray<TSharedPtr<FJsonValue>> Max = Bounds[1]->AsArray();
				if (Min.Num() == 3 && Max.Num() == 3)
				{
					OutPlan.Validation.BoundsMin = FVector((float)Min[0]->AsNumber(), (float)Min[1]->AsNumber(), (float)Min[2]->AsNumber());
					OutPlan.Validation.BoundsMax = FVector((float)Max[0]->AsNumber(), (float)Max[1]->AsNumber(), (float)Max[2]->AsNumber());
				}
			}
		}
		if (ValObj->HasTypedField<EJson::Array>(TEXT("particleCountRange")))
		{
			const TArray<TSharedPtr<FJsonValue>> Range = ValObj->GetArrayField(TEXT("particleCountRange"));
			if (Range.Num() == 2)
			{
				OutPlan.Validation.ParticleCountRange = FVector2D((float)Range[0]->AsNumber(), (float)Range[1]->AsNumber());
			}
		}
	}

	return true;
}

FString FVFXDirectorJson::ExecutionReportToJson(const FVFXExecutionReport& Report)
{
	TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
	Root->SetBoolField(TEXT("success"), Report.bSuccess);

	TArray<TSharedPtr<FJsonValue>> Logs;
	for (const FString& L : Report.Logs)
	{
		Logs.Add(MakeShared<FJsonValueString>(L));
	}
	Root->SetArrayField(TEXT("logs"), Logs);

	TArray<TSharedPtr<FJsonValue>> Warns;
	for (const FString& W : Report.Warnings)
	{
		Warns.Add(MakeShared<FJsonValueString>(W));
	}
	Root->SetArrayField(TEXT("warnings"), Warns);

	TArray<TSharedPtr<FJsonValue>> Errors;
	for (const FString& E : Report.Errors)
	{
		Errors.Add(MakeShared<FJsonValueString>(E));
	}
	Root->SetArrayField(TEXT("errors"), Errors);

	TArray<TSharedPtr<FJsonValue>> Assets;
	for (const FString& A : Report.GeneratedAssets)
	{
		Assets.Add(MakeShared<FJsonValueString>(A));
	}
	Root->SetArrayField(TEXT("assets"), Assets);

	Root->SetStringField(TEXT("thumbnail"), Report.ThumbnailPath);

	FString Output;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Output);
	FJsonSerializer::Serialize(Root, Writer);
	return Output;
}
