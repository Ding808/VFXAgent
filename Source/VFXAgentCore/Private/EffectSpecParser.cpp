#include "EffectSpecParser.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

static FString GetStringField(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key)
{
	FString Value;
	if (Obj.IsValid() && Obj->TryGetStringField(Key, Value))
	{
		return Value;
	}
	return FString();
}

static double GetNumberField(const TSharedPtr<FJsonObject>& Obj, const TCHAR* Key, double DefaultValue = 0.0)
{
	double Value = DefaultValue;
	if (Obj.IsValid())
	{
		Obj->TryGetNumberField(Key, Value);
	}
	return Value;
}

static void ParseMaterial(const TSharedPtr<FJsonObject>& Obj, FMaterialSpecV1& OutMat)
{
	OutMat.Shading = GetStringField(Obj, TEXT("shading"));
	OutMat.Blend = GetStringField(Obj, TEXT("blend"));

	const TSharedPtr<FJsonObject>* ParamsObj = nullptr;
	if (Obj.IsValid() && Obj->TryGetObjectField(TEXT("params"), ParamsObj) && ParamsObj && ParamsObj->IsValid())
	{
		const TSharedPtr<FJsonObject>* ScalarObj = nullptr;
		if ((*ParamsObj)->TryGetObjectField(TEXT("scalar"), ScalarObj) && ScalarObj && ScalarObj->IsValid())
		{
			for (const TPair<FString, TSharedPtr<FJsonValue>>& KV : (*ScalarObj)->Values)
			{
				OutMat.ScalarParams.Add(KV.Key, (float)KV.Value->AsNumber());
			}
		}
		const TSharedPtr<FJsonObject>* VectorObj = nullptr;
		if ((*ParamsObj)->TryGetObjectField(TEXT("vector"), VectorObj) && VectorObj && VectorObj->IsValid())
		{
			for (const TPair<FString, TSharedPtr<FJsonValue>>& KV : (*VectorObj)->Values)
			{
				const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
				if (KV.Value->TryGetArray(Arr) && Arr && Arr->Num() >= 3)
				{
					const float R = (float)(*Arr)[0]->AsNumber();
					const float G = (float)(*Arr)[1]->AsNumber();
					const float B = (float)(*Arr)[2]->AsNumber();
					const float A = (Arr->Num() > 3) ? (float)(*Arr)[3]->AsNumber() : 1.0f;
					OutMat.VectorParams.Add(KV.Key, FLinearColor(R, G, B, A));
				}
			}
		}
		const TSharedPtr<FJsonObject>* TexSlotsObj = nullptr;
		if ((*ParamsObj)->TryGetObjectField(TEXT("texture_slots"), TexSlotsObj) && TexSlotsObj && TexSlotsObj->IsValid())
		{
			for (const TPair<FString, TSharedPtr<FJsonValue>>& KV : (*TexSlotsObj)->Values)
			{
				OutMat.TextureSlots.Add(KV.Key, KV.Value->AsString());
			}
		}
	}

	const TSharedPtr<FJsonObject>* HlslObj = nullptr;
	if (Obj.IsValid() && Obj->TryGetObjectField(TEXT("hlsl_custom"), HlslObj) && HlslObj && HlslObj->IsValid())
	{
		OutMat.HLSLCustom.Enabled = (*HlslObj)->GetBoolField(TEXT("enabled"));
		OutMat.HLSLCustom.Code = GetStringField(*HlslObj, TEXT("code"));
		OutMat.HLSLCustom.Contract = GetStringField(*HlslObj, TEXT("contract"));

		const TSharedPtr<FJsonObject>* OutputsObj = nullptr;
		if ((*HlslObj)->TryGetObjectField(TEXT("outputs"), OutputsObj) && OutputsObj && OutputsObj->IsValid())
		{
			OutMat.HLSLCustom.Outputs.emissive = (*OutputsObj)->GetBoolField(TEXT("emissive"));
			OutMat.HLSLCustom.Outputs.opacity = (*OutputsObj)->GetBoolField(TEXT("opacity"));
			OutMat.HLSLCustom.Outputs.distortion = (*OutputsObj)->GetBoolField(TEXT("distortion"));
		}

		const TArray<TSharedPtr<FJsonValue>>* InputsArray = nullptr;
		if ((*HlslObj)->TryGetArrayField(TEXT("inputs"), InputsArray) && InputsArray)
		{
			for (const TSharedPtr<FJsonValue>& Val : *InputsArray)
			{
				const TSharedPtr<FJsonObject> InObj = Val->AsObject();
				if (!InObj.IsValid()) continue;
				FMaterialHLSLInput In;
				In.Name = GetStringField(InObj, TEXT("name"));
				In.Type = GetStringField(InObj, TEXT("type"));
				In.Default = (float)GetNumberField(InObj, TEXT("default"), 0.0);
				In.Min = (float)GetNumberField(InObj, TEXT("min"), 0.0);
				In.Max = (float)GetNumberField(InObj, TEXT("max"), 1.0);
				OutMat.HLSLCustom.Inputs.Add(In);
			}
		}

		const TArray<TSharedPtr<FJsonValue>>* TexInputsArray = nullptr;
		if ((*HlslObj)->TryGetArrayField(TEXT("texture_inputs"), TexInputsArray) && TexInputsArray)
		{
			for (const TSharedPtr<FJsonValue>& Val : *TexInputsArray)
			{
				const TSharedPtr<FJsonObject> InObj = Val->AsObject();
				if (!InObj.IsValid()) continue;
				FMaterialHLSLTextureInput TI;
				TI.Name = GetStringField(InObj, TEXT("name"));
				TI.Usage = GetStringField(InObj, TEXT("usage"));
				OutMat.HLSLCustom.TextureInputs.Add(TI);
			}
		}
	}
}

bool FEffectSpecParser::ParseFromJsonString(const FString& Json, FEffectSpecV1& OutSpec, FString& OutError)
{
	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		OutError = TEXT("Invalid JSON");
		return false;
	}

	OutSpec.EffectName = GetStringField(Root, TEXT("effect_name"));

	const TSharedPtr<FJsonObject>* StyleObj = nullptr;
	if (Root->TryGetObjectField(TEXT("global_style"), StyleObj) && StyleObj && StyleObj->IsValid())
	{
		OutSpec.GlobalStyle.Palette = GetStringField(*StyleObj, TEXT("palette"));
		OutSpec.GlobalStyle.RealismToAnime = (float)GetNumberField(*StyleObj, TEXT("realism_to_anime"), 0.5);
		OutSpec.GlobalStyle.Brightness = (float)GetNumberField(*StyleObj, TEXT("brightness"), 1.0);
		OutSpec.GlobalStyle.Contrast = (float)GetNumberField(*StyleObj, TEXT("contrast"), 1.0);
		OutSpec.GlobalStyle.NoiseStyle = GetStringField(*StyleObj, TEXT("noise_style"));
	}

	const TArray<TSharedPtr<FJsonValue>>* LayersArray = nullptr;
	if (Root->TryGetArrayField(TEXT("layers"), LayersArray) && LayersArray)
	{
		for (const TSharedPtr<FJsonValue>& Val : *LayersArray)
		{
			const TSharedPtr<FJsonObject> LayerObj = Val->AsObject();
			if (!LayerObj.IsValid()) continue;

			FLayerSpecV1 Layer;
			Layer.Id = GetStringField(LayerObj, TEXT("id"));
			Layer.Name = GetStringField(LayerObj, TEXT("name"));
			Layer.Role = GetStringField(LayerObj, TEXT("role"));
			Layer.RendererType = GetStringField(LayerObj, TEXT("renderer_type"));

			const TSharedPtr<FJsonObject>* SpawnObj = nullptr;
			if (LayerObj->TryGetObjectField(TEXT("spawn"), SpawnObj) && SpawnObj && SpawnObj->IsValid())
			{
				Layer.Spawn.Mode = GetStringField(*SpawnObj, TEXT("mode"));
				Layer.Spawn.Rate = (float)GetNumberField(*SpawnObj, TEXT("rate"), 0.0);
				Layer.Spawn.BurstCount = (int32)GetNumberField(*SpawnObj, TEXT("burst_count"), 0.0);
				Layer.Spawn.Duration = (float)GetNumberField(*SpawnObj, TEXT("duration"), 0.0);
			}

			const TSharedPtr<FJsonObject>* InitObj = nullptr;
			if (LayerObj->TryGetObjectField(TEXT("init"), InitObj) && InitObj && InitObj->IsValid())
			{
				Layer.Init.Lifetime = (float)GetNumberField(*InitObj, TEXT("lifetime"), 2.0);
				const TArray<TSharedPtr<FJsonValue>>* SizeArr = nullptr;
				if ((*InitObj)->TryGetArrayField(TEXT("size_range"), SizeArr) && SizeArr && SizeArr->Num() >= 2)
				{
					Layer.Init.SizeRange.X = (float)(*SizeArr)[0]->AsNumber();
					Layer.Init.SizeRange.Y = (float)(*SizeArr)[1]->AsNumber();
				}

				const TSharedPtr<FJsonObject>* VelObj = nullptr;
				if ((*InitObj)->TryGetObjectField(TEXT("velocity"), VelObj) && VelObj && VelObj->IsValid())
				{
					Layer.Init.Velocity.X = (float)GetNumberField(*VelObj, TEXT("x"), 0.0);
					Layer.Init.Velocity.Y = (float)GetNumberField(*VelObj, TEXT("y"), 0.0);
					Layer.Init.Velocity.Z = (float)GetNumberField(*VelObj, TEXT("z"), 0.0);
				}
			}

			const TSharedPtr<FJsonObject>* UpdateObj = nullptr;
			if (LayerObj->TryGetObjectField(TEXT("update"), UpdateObj) && UpdateObj && UpdateObj->IsValid())
			{
				Layer.Update.Drag = (float)GetNumberField(*UpdateObj, TEXT("drag"), 0.0);
				Layer.Update.CurlNoiseStrength = (float)GetNumberField(*UpdateObj, TEXT("curl_noise_strength"), 0.0);
			}

			const TSharedPtr<FJsonObject>* MotionObj = nullptr;
			if (LayerObj->TryGetObjectField(TEXT("motion"), MotionObj) && MotionObj && MotionObj->IsValid())
			{
				Layer.Motion.Semantic = GetStringField(*MotionObj, TEXT("semantic"));
			}

			const TArray<TSharedPtr<FJsonValue>>* TexArr = nullptr;
			if (LayerObj->TryGetArrayField(TEXT("textures_needed"), TexArr) && TexArr)
			{
				for (const TSharedPtr<FJsonValue>& V : *TexArr)
				{
					const TSharedPtr<FJsonObject> TObj = V->AsObject();
					if (!TObj.IsValid()) continue;
					FTextureRequestV1 TR;
					TR.Name = GetStringField(TObj, TEXT("name"));
					TR.Usage = GetStringField(TObj, TEXT("usage"));
					TR.Width = (int32)GetNumberField(TObj, TEXT("width"), 512);
					TR.Height = (int32)GetNumberField(TObj, TEXT("height"), 512);
					Layer.TexturesNeeded.Add(TR);
				}
			}

			const TSharedPtr<FJsonObject>* ModelObj = nullptr;
			if (LayerObj->TryGetObjectField(TEXT("model_needed"), ModelObj) && ModelObj && ModelObj->IsValid())
			{
				Layer.ModelNeeded.Name = GetStringField(*ModelObj, TEXT("name"));
				Layer.ModelNeeded.Format = GetStringField(*ModelObj, TEXT("format"));
			}

			const TSharedPtr<FJsonObject>* MatObj = nullptr;
			if (LayerObj->TryGetObjectField(TEXT("material"), MatObj) && MatObj && MatObj->IsValid())
			{
				ParseMaterial(*MatObj, Layer.Material);
			}

			OutSpec.Layers.Add(Layer);
		}
	}

	return true;
}
