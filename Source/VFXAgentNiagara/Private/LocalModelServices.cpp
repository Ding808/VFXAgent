#include "LocalModelServices.h"
#include "PipelineLog.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "ImageUtils.h"
#include "Misc/ConfigCacheIni.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Misc/Base64.h"
#include "Misc/DateTime.h"

static FString EnsureDir(const FString& Dir)
{
	IFileManager::Get().MakeDirectory(*Dir, true);
	return Dir;
}

static void AppendServiceLog(const FString& Line)
{
	const FString LogDir = EnsureDir(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("Logs")));
	const FString ServiceLogPath = FPaths::Combine(LogDir, TEXT("service_log.txt"));
	FFileHelper::SaveStringToFile(Line + TEXT("\n"), *ServiceLogPath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

FModelServiceResult FLocalImageGenService::GenerateTexture(const FTextureRequestV1& Request)
{
	FModelServiceResult Result;
	const FString BaseDir = EnsureDir(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedTextures")));
	const FString FilePath = FPaths::Combine(BaseDir, Request.Name + TEXT(".png"));

	const int32 W = FMath::Max(4, Request.Width);
	const int32 H = FMath::Max(4, Request.Height);
	TArray<FColor> Pixels;
	Pixels.SetNum(W * H);

	for (int32 y = 0; y < H; ++y)
	{
		for (int32 x = 0; x < W; ++x)
		{
			const float U = (float)x / (float)(W - 1);
			const float V = (float)y / (float)(H - 1);
			FColor C = FColor::MakeRedToGreenColorFromScalar(U);
			C.B = (uint8)(V * 255.0f);
			C.A = 255;
			Pixels[y * W + x] = C;
		}
	}

	TArray64<uint8> PngData64;
	FImageUtils::PNGCompressImageArray(W, H, Pixels, PngData64);
	if (PngData64.Num() == 0)
	{
		Result.bSuccess = false;
		Result.Error = TEXT("PNG compression failed");
		return Result;
	}

	TArray<uint8> PngData;
	PngData.Append(PngData64.GetData(), PngData64.Num());
	if (!FFileHelper::SaveArrayToFile(PngData, *FilePath))
	{
		Result.bSuccess = false;
		Result.Error = TEXT("Failed to write PNG");
		return Result;
	}

	Result.bSuccess = true;
	Result.OutputPath = FilePath;
	Result.Summary = TEXT("Local texture generated");
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageGen, TEXT("Generated local texture"), TEXT("Local"));
	AppendServiceLog(FString::Printf(TEXT("ImageGen: %s -> %s"), *Request.Name, *FilePath));
	return Result;
}

FModelServiceResult FLocalImageTo3DService::GenerateModel(const FModelRequestV1& Request, const FString& SourceImage)
{
	FModelServiceResult Result;
	const FString BaseDir = EnsureDir(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedMeshes")));
	const FString FilePath = FPaths::Combine(BaseDir, Request.Name + TEXT(".obj"));

	const FString Obj =
		TEXT("o VFXAgentMesh\n")
		TEXT("v 0 0 0\n")
		TEXT("v 0 0 10\n")
		TEXT("v 10 0 0\n")
		TEXT("f 1 2 3\n");

	if (!FFileHelper::SaveStringToFile(Obj, *FilePath))
	{
		Result.bSuccess = false;
		Result.Error = TEXT("Failed to write OBJ");
		return Result;
	}

	Result.bSuccess = true;
	Result.OutputPath = FilePath;
	Result.Summary = TEXT("Local mesh generated");
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageTo3D, TEXT("Generated local mesh"), TEXT("Local"));
	AppendServiceLog(FString::Printf(TEXT("ImageTo3D: %s -> %s"), *Request.Name, *FilePath));
	return Result;
}

static FString GetSettingString(const TCHAR* Key)
{
	FString Value;
	const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetString(Section, Key, Value, File))
		{
			return Value;
		}
	}
	return FString();
}

static bool PostJsonAndWait(const FString& Endpoint, const FString& ApiKey, const FString& Body, FString& OutResponse, FString& OutError)
{
	if (Endpoint.IsEmpty())
	{
		OutError = TEXT("Endpoint is empty");
		return false;
	}

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->SetURL(Endpoint);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	if (!ApiKey.IsEmpty())
	{
		Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
	}
	Request->SetContentAsString(Body);

	FEvent* DoneEvent = FPlatformProcess::GetSynchEventFromPool(true);
	bool bSuccess = false;
	FString Response;
	FString Error;

	Request->OnProcessRequestComplete().BindLambda([&](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bOk)
	{
		bSuccess = bOk && Resp.IsValid() && EHttpResponseCodes::IsOk(Resp->GetResponseCode());
		if (Resp.IsValid())
		{
			Response = Resp->GetContentAsString();
		}
		if (!bSuccess)
		{
			Error = Resp.IsValid() ? Resp->GetContentAsString() : TEXT("HTTP request failed");
		}
		DoneEvent->Trigger();
	});

	if (!Request->ProcessRequest())
	{
		OutError = TEXT("Failed to start HTTP request");
		FPlatformProcess::ReturnSynchEventToPool(DoneEvent);
		return false;
	}

	const double Start = FPlatformTime::Seconds();
	while (!DoneEvent->Wait(10))
	{
		if ((FPlatformTime::Seconds() - Start) > 60.0)
		{
			OutError = TEXT("HTTP request timed out");
			FPlatformProcess::ReturnSynchEventToPool(DoneEvent);
			return false;
		}
	}

	FPlatformProcess::ReturnSynchEventToPool(DoneEvent);
	OutResponse = Response;
	OutError = Error;
	return bSuccess;
}

static bool TryWriteFileFromResponse(const FString& Response, const FString& TargetPath, FString& OutError)
{
	TSharedPtr<FJsonObject> Root;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		OutError = TEXT("Invalid JSON response");
		return false;
	}

	FString FilePath;
	if (Root->TryGetStringField(TEXT("file_path"), FilePath) && FPaths::FileExists(FilePath))
	{
		return IFileManager::Get().Copy(*TargetPath, *FilePath) == COPY_OK;
	}

	FString Base64;
	if (Root->TryGetStringField(TEXT("data_base64"), Base64))
	{
		TArray<uint8> Data;
		if (!FBase64::Decode(Base64, Data))
		{
			OutError = TEXT("Base64 decode failed");
			return false;
		}
		return FFileHelper::SaveArrayToFile(Data, *TargetPath);
	}

	OutError = TEXT("Response missing file_path or data_base64");
	return false;
}

FModelServiceResult FExternalImageGenService::GenerateTexture(const FTextureRequestV1& Request)
{
	FModelServiceResult Result;
	const FString Endpoint = GetSettingString(TEXT("ImageGenEndpoint"));
	const FString ApiKey = GetSettingString(TEXT("ImageGenApiKey"));
	if (Endpoint.IsEmpty())
	{
		Result.bSuccess = false;
		Result.Error = TEXT("ImageGen endpoint not configured");
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageGen, TEXT("ImageGen endpoint not configured"), TEXT("External"));
		return Result;
	}
	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("name"), Request.Name);
	Body->SetNumberField(TEXT("width"), Request.Width);
	Body->SetNumberField(TEXT("height"), Request.Height);
	Body->SetStringField(TEXT("usage"), Request.Usage);

	FString BodyStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyStr);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	FString Response;
	FString Error;
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageGen, TEXT("Calling external ImageGen..."), TEXT("External"));
	if (!PostJsonAndWait(Endpoint, ApiKey, BodyStr, Response, Error))
	{
		Result.bSuccess = false;
		Result.Error = Error;
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageGen, Error, TEXT("External"));
		return Result;
	}

	const FString BaseDir = EnsureDir(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedTextures")));
	const FString FilePath = FPaths::Combine(BaseDir, Request.Name + TEXT(".png"));
	if (!TryWriteFileFromResponse(Response, FilePath, Error))
	{
		Result.bSuccess = false;
		Result.Error = Error;
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageGen, Error, TEXT("External"));
		return Result;
	}

	Result.bSuccess = true;
	Result.OutputPath = FilePath;
	Result.Summary = TEXT("External texture generated");
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageGen, TEXT("Generated external texture"), TEXT("External"));
	return Result;
}

FModelServiceResult FExternalImageTo3DService::GenerateModel(const FModelRequestV1& Request, const FString& SourceImage)
{
	FModelServiceResult Result;
	const FString Endpoint = GetSettingString(TEXT("ImageTo3DEndpoint"));
	const FString ApiKey = GetSettingString(TEXT("ImageTo3DApiKey"));
	if (Endpoint.IsEmpty())
	{
		Result.bSuccess = false;
		Result.Error = TEXT("ImageTo3D endpoint not configured");
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageTo3D, TEXT("ImageTo3D endpoint not configured"), TEXT("External"));
		return Result;
	}
	TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField(TEXT("name"), Request.Name);
	Body->SetStringField(TEXT("format"), Request.Format.IsEmpty() ? TEXT("obj") : Request.Format);
	Body->SetStringField(TEXT("source_image"), SourceImage);

	FString BodyStr;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&BodyStr);
	FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);

	FString Response;
	FString Error;
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageTo3D, TEXT("Calling external ImageTo3D..."), TEXT("External"));
	if (!PostJsonAndWait(Endpoint, ApiKey, BodyStr, Response, Error))
	{
		Result.bSuccess = false;
		Result.Error = Error;
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageTo3D, Error, TEXT("External"));
		return Result;
	}

	const FString Ext = Request.Format.IsEmpty() ? TEXT("obj") : Request.Format;
	const FString BaseDir = EnsureDir(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedMeshes")));
	const FString FilePath = FPaths::Combine(BaseDir, Request.Name + TEXT(".") + Ext);
	if (!TryWriteFileFromResponse(Response, FilePath, Error))
	{
		Result.bSuccess = false;
		Result.Error = Error;
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageTo3D, Error, TEXT("External"));
		return Result;
	}

	Result.bSuccess = true;
	Result.OutputPath = FilePath;
	Result.Summary = TEXT("External model generated");
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageTo3D, TEXT("Generated external model"), TEXT("External"));
	return Result;
}
