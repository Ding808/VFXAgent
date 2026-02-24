#include "MeshyModelServices.h"
#include "PipelineLog.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Misc/ConfigCacheIni.h"
#include "HttpModule.h"
#include "HttpManager.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Http.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Misc/Base64.h"
#include "Misc/DateTime.h"

namespace
{
	static constexpr double DefaultPollingTimeoutSeconds = 180.0;
	static constexpr double DefaultPollingIntervalSeconds = 2.0;

	FString EnsureDir(const FString& Dir)
	{
		IFileManager::Get().MakeDirectory(*Dir, true);
		return Dir;
	}

	FString ReadSetting(const TCHAR* Key, const FString& DefaultValue = FString())
	{
		FString Value;
		const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
		for (const FString& File : ConfigFiles)
		{
			if (GConfig && GConfig->GetString(TEXT("VFXAgent"), Key, Value, File))
			{
				Value.TrimStartAndEndInline();
				if (!Value.IsEmpty())
				{
					return Value;
				}
			}

			if (GConfig && GConfig->GetString(TEXT("/Script/VFXAgentEditor.VFXAgentSettings"), Key, Value, File))
			{
				Value.TrimStartAndEndInline();
				if (!Value.IsEmpty())
				{
					return Value;
				}
			}
		}
		return DefaultValue;
	}

	double ReadSettingDouble(const TCHAR* Key, double DefaultValue)
	{
		float Value = static_cast<float>(DefaultValue);
		const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
		for (const FString& File : ConfigFiles)
		{
			if (GConfig && GConfig->GetFloat(TEXT("VFXAgent"), Key, Value, File))
			{
				return static_cast<double>(Value);
			}
			if (GConfig && GConfig->GetFloat(TEXT("/Script/VFXAgentEditor.VFXAgentSettings"), Key, Value, File))
			{
				return static_cast<double>(Value);
			}
		}
		return DefaultValue;
	}

	FString GetMeshyApiKey()
	{
		return ReadSetting(TEXT("MeshyApiKey"));
	}

	FString GetMeshyEndpoint()
	{
		return ReadSetting(TEXT("MeshyEndpoint"), TEXT("https://api.meshy.ai/v1"));
	}

	FString JoinUrl(const FString& Base, const FString& Path)
	{
		if (Path.StartsWith(TEXT("http://")) || Path.StartsWith(TEXT("https://")))
		{
			return Path;
		}

		FString Left = Base;
		Left.TrimStartAndEndInline();
		while (Left.EndsWith(TEXT("/")))
		{
			Left.LeftChopInline(1, EAllowShrinking::No);
		}

		FString Right = Path;
		Right.TrimStartAndEndInline();
		if (!Right.StartsWith(TEXT("/")))
		{
			Right = TEXT("/") + Right;
		}

		return Left + Right;
	}

	bool TryParseJson(const FString& Text, TSharedPtr<FJsonObject>& OutObject)
	{
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Text);
		return FJsonSerializer::Deserialize(Reader, OutObject) && OutObject.IsValid();
	}

	bool TryRequestBlocking(
		const FString& Method,
		const FString& Url,
		const FString& ApiKey,
		const FString* Body,
		double TimeoutSeconds,
		int32& OutCode,
		FString& OutText,
		TArray<uint8>& OutBytes,
		FString& OutError)
	{
		OutCode = 0;
		OutText.Reset();
		OutBytes.Reset();
		OutError.Reset();

		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
		Request->SetVerb(Method);
		Request->SetURL(Url);
		Request->SetHeader(TEXT("Accept"), TEXT("application/json, */*"));
		if (!ApiKey.IsEmpty())
		{
			Request->SetHeader(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *ApiKey));
		}
		if (Body)
		{
			Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
			Request->SetContentAsString(*Body);
		}
		Request->SetTimeout(static_cast<float>(FMath::Max(1.0, TimeoutSeconds)));

		bool bDone = false;
		Request->OnProcessRequestComplete().BindLambda(
			[&](FHttpRequestPtr Req, FHttpResponsePtr Resp, bool bOk)
			{
				if (Resp.IsValid())
				{
					OutCode = Resp->GetResponseCode();
					OutText = Resp->GetContentAsString();
					OutBytes = Resp->GetContent();
				}

				if (!bOk || !Resp.IsValid())
				{
					OutError = TEXT("HTTP request failed");
				}
				else if (!EHttpResponseCodes::IsOk(OutCode))
				{
					OutError = FString::Printf(TEXT("HTTP %d: %s"), OutCode, *OutText.Left(512));
				}

				bDone = true;
			});

		if (!Request->ProcessRequest())
		{
			OutError = TEXT("Failed to start HTTP request");
			return false;
		}

		const double Start = FPlatformTime::Seconds();
		while (!bDone)
		{
			if (IsInGameThread())
			{
				FHttpModule::Get().GetHttpManager().Tick(0.01f);
			}
			FPlatformProcess::Sleep(0.01f);

			if ((FPlatformTime::Seconds() - Start) > TimeoutSeconds)
			{
				OutError = TEXT("HTTP timeout");
				return false;
			}
		}

		return OutError.IsEmpty();
	}

	bool TryGetStringPath(const TSharedPtr<FJsonObject>& Root, const FString& Path, FString& OutValue)
	{
		if (!Root.IsValid())
		{
			return false;
		}

		TArray<FString> Parts;
		Path.ParseIntoArray(Parts, TEXT("."), true);
		if (Parts.Num() == 0)
		{
			return false;
		}

		TSharedPtr<FJsonObject> Current = Root;
		for (int32 Index = 0; Index < Parts.Num(); ++Index)
		{
			const bool bLast = (Index == Parts.Num() - 1);
			if (bLast)
			{
				if (Current->TryGetStringField(Parts[Index], OutValue))
				{
					return true;
				}

				const TSharedPtr<FJsonObject>* ChildObj = nullptr;
				if (Current->TryGetObjectField(Parts[Index], ChildObj) && ChildObj && ChildObj->IsValid())
				{
					if ((*ChildObj)->TryGetStringField(TEXT("url"), OutValue))
					{
						return true;
					}
				}
				return false;
			}

			const TSharedPtr<FJsonObject>* Child = nullptr;
			if (!Current->TryGetObjectField(Parts[Index], Child) || !Child || !Child->IsValid())
			{
				return false;
			}
			Current = *Child;
		}

		return false;
	}

	bool TryExtractTaskId(const TSharedPtr<FJsonObject>& Root, FString& OutTaskId)
	{
		const TCHAR* Candidates[] = {
			TEXT("task_id"),
			TEXT("id"),
			TEXT("result.task_id"),
			TEXT("result.id"),
			TEXT("data.task_id")
		};

		for (const TCHAR* Candidate : Candidates)
		{
			if (TryGetStringPath(Root, Candidate, OutTaskId) && !OutTaskId.IsEmpty())
			{
				return true;
			}
		}
		return false;
	}

	bool TryExtractStatus(const TSharedPtr<FJsonObject>& Root, FString& OutStatus)
	{
		const TCHAR* Candidates[] = {
			TEXT("status"),
			TEXT("state"),
			TEXT("result.status"),
			TEXT("data.status")
		};
		for (const TCHAR* Candidate : Candidates)
		{
			if (TryGetStringPath(Root, Candidate, OutStatus) && !OutStatus.IsEmpty())
			{
				OutStatus = OutStatus.ToLower();
				return true;
			}
		}
		return false;
	}

	bool IsTerminalSuccessStatus(const FString& InStatus)
	{
		const FString Status = InStatus.ToLower();
		return Status == TEXT("succeeded") || Status == TEXT("success") || Status == TEXT("completed") || Status == TEXT("complete") || Status == TEXT("done");
	}

	bool IsTerminalFailureStatus(const FString& InStatus)
	{
		const FString Status = InStatus.ToLower();
		return Status == TEXT("failed") || Status == TEXT("error") || Status == TEXT("cancelled") || Status == TEXT("canceled") || Status == TEXT("rejected");
	}

	FString ReplaceTaskIdToken(const FString& Template, const FString& TaskId)
	{
		FString Path = Template;
		Path.ReplaceInline(TEXT("{task_id}"), *TaskId, ESearchCase::CaseSensitive);
		Path.ReplaceInline(TEXT("{id}"), *TaskId, ESearchCase::CaseSensitive);
		return Path;
	}

	bool PollTaskUntilTerminal(
		const FString& BaseEndpoint,
		const FString& StatusPathTemplate,
		const FString& ApiKey,
		const FString& TaskId,
		const double PollIntervalSeconds,
		const double PollTimeoutSeconds,
		TSharedPtr<FJsonObject>& OutFinalJson,
		FString& OutError)
	{
		const FString StatusUrl = JoinUrl(BaseEndpoint, ReplaceTaskIdToken(StatusPathTemplate, TaskId));
		const double Start = FPlatformTime::Seconds();
		int32 PollCount = 0;

		while ((FPlatformTime::Seconds() - Start) <= PollTimeoutSeconds)
		{
			int32 Code = 0;
			FString ResponseText;
			TArray<uint8> ResponseBytes;
			FString RequestError;
			if (!TryRequestBlocking(TEXT("GET"), StatusUrl, ApiKey, nullptr, FMath::Max(PollIntervalSeconds * 4.0, 15.0), Code, ResponseText, ResponseBytes, RequestError))
			{
				OutError = FString::Printf(TEXT("Polling failed for task %s: %s"), *TaskId, *RequestError);
				return false;
			}

			TSharedPtr<FJsonObject> Root;
			if (!TryParseJson(ResponseText, Root))
			{
				OutError = FString::Printf(TEXT("Polling response is not valid JSON for task %s"), *TaskId);
				return false;
			}

			FString Status;
			if (TryExtractStatus(Root, Status))
			{
				if (IsTerminalSuccessStatus(Status))
				{
					OutFinalJson = Root;
					return true;
				}
				if (IsTerminalFailureStatus(Status))
				{
					FString Message;
					TryGetStringPath(Root, TEXT("message"), Message);
					if (Message.IsEmpty())
					{
						TryGetStringPath(Root, TEXT("error"), Message);
					}
					OutError = FString::Printf(TEXT("Meshy task %s failed with status '%s'. %s"), *TaskId, *Status, *Message);
					return false;
				}
			}

			++PollCount;
			if ((PollCount % 5) == 0)
			{
				FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageTo3D,
					FString::Printf(TEXT("Meshy task %s polling... (%d)"), *TaskId, PollCount),
					TEXT("Meshy"));
			}

			FPlatformProcess::Sleep(FMath::Max(0.1, PollIntervalSeconds));
		}

		OutError = FString::Printf(TEXT("Meshy task %s polling timed out after %.1f seconds"), *TaskId, PollTimeoutSeconds);
		return false;
	}

	FString ResolveExtension(const FString& PreferredFormat, const FString& Url, const FString& Fallback)
	{
		FString LowerFormat = PreferredFormat.ToLower();
		if (LowerFormat == TEXT("glb") || LowerFormat == TEXT("fbx") || LowerFormat == TEXT("obj") || LowerFormat == TEXT("png") || LowerFormat == TEXT("jpg") || LowerFormat == TEXT("jpeg"))
		{
			return LowerFormat;
		}

		FString CleanUrl = Url;
		int32 QueryPos = INDEX_NONE;
		if (CleanUrl.FindChar(TEXT('?'), QueryPos))
		{
			CleanUrl = CleanUrl.Left(QueryPos);
		}

		const FString UrlExt = FPaths::GetExtension(CleanUrl).ToLower();
		if (!UrlExt.IsEmpty())
		{
			return UrlExt;
		}

		return Fallback;
	}

	bool DownloadUrlToFile(const FString& Url, const FString& ApiKey, const FString& TargetPath, FString& OutError)
	{
		int32 Code = 0;
		FString ResponseText;
		TArray<uint8> ResponseBytes;
		if (!TryRequestBlocking(TEXT("GET"), Url, ApiKey, nullptr, 120.0, Code, ResponseText, ResponseBytes, OutError))
		{
			return false;
		}

		if (ResponseBytes.Num() <= 0)
		{
			OutError = TEXT("Downloaded response is empty");
			return false;
		}

		const FString Directory = FPaths::GetPath(TargetPath);
		if (!Directory.IsEmpty())
		{
			IFileManager::Get().MakeDirectory(*Directory, true);
		}
		if (!FFileHelper::SaveArrayToFile(ResponseBytes, *TargetPath))
		{
			OutError = FString::Printf(TEXT("Failed to save downloaded file: %s"), *TargetPath);
			return false;
		}
		return true;
	}

	bool TrySaveFromPayload(const TSharedPtr<FJsonObject>& Json, const FString& DefaultFolder, const FString& BaseName, const FString& DefaultExt, const FString& ApiKey, FString& OutFile, FString& OutError)
	{
		OutFile.Reset();

		FString ExistingFilePath;
		if (TryGetStringPath(Json, TEXT("file_path"), ExistingFilePath) && FPaths::FileExists(ExistingFilePath))
		{
			const FString Ext = ResolveExtension(TEXT(""), ExistingFilePath, DefaultExt);
			OutFile = FPaths::Combine(DefaultFolder, BaseName + TEXT(".") + Ext);
			if (IFileManager::Get().Copy(*OutFile, *ExistingFilePath) == COPY_OK)
			{
				return true;
			}
		}

		FString Base64Data;
		if (TryGetStringPath(Json, TEXT("data_base64"), Base64Data) && !Base64Data.IsEmpty())
		{
			TArray<uint8> Data;
			if (!FBase64::Decode(Base64Data, Data))
			{
				OutError = TEXT("Meshy base64 payload decode failed");
				return false;
			}

			OutFile = FPaths::Combine(DefaultFolder, BaseName + TEXT(".") + DefaultExt);
			if (!FFileHelper::SaveArrayToFile(Data, *OutFile))
			{
				OutError = FString::Printf(TEXT("Failed to save decoded payload: %s"), *OutFile);
				return false;
			}
			return true;
		}

		const TCHAR* UrlCandidates[] = {
			TEXT("model_urls.glb"),
			TEXT("model_urls.fbx"),
			TEXT("model_urls.obj"),
			TEXT("result.model_urls.glb"),
			TEXT("result.model_urls.fbx"),
			TEXT("result.model_url"),
			TEXT("output.model_url"),
			TEXT("texture_url"),
			TEXT("result.texture_url"),
			TEXT("download_url"),
			TEXT("result.download_url"),
			TEXT("url"),
			TEXT("result.url")
		};

		FString DownloadUrl;
		for (const TCHAR* Candidate : UrlCandidates)
		{
			if (TryGetStringPath(Json, Candidate, DownloadUrl) && !DownloadUrl.IsEmpty())
			{
				break;
			}
		}

		if (!DownloadUrl.IsEmpty())
		{
			const FString Ext = ResolveExtension(TEXT(""), DownloadUrl, DefaultExt);
			OutFile = FPaths::Combine(DefaultFolder, BaseName + TEXT(".") + Ext);
			return DownloadUrlToFile(DownloadUrl, ApiKey, OutFile, OutError);
		}

		OutError = TEXT("Meshy response has no downloadable file data");
		return false;
	}
}

FModelServiceResult FMeshyImageGenService::GenerateTexture(const FTextureRequestV1& Request)
{
	FModelServiceResult Result;
	Result.bSuccess = false;

	const FString ApiKey = GetMeshyApiKey();
	const FString Endpoint = GetMeshyEndpoint();
	if (Endpoint.IsEmpty() || ApiKey.IsEmpty())
	{
		Result.Error = TEXT("Meshy endpoint/api key not configured");
		return Result;
	}

	const FString SubmitPath = ReadSetting(TEXT("MeshyTextToTextureSubmitPath"), TEXT("/text-to-texture"));
	const FString StatusPathTemplate = ReadSetting(TEXT("MeshyTextToTextureStatusPath"), TEXT("/text-to-texture/{task_id}"));
	const double PollInterval = ReadSettingDouble(TEXT("MeshyPollingIntervalSeconds"), DefaultPollingIntervalSeconds);
	const double PollTimeout = ReadSettingDouble(TEXT("MeshyPollingTimeoutSeconds"), DefaultPollingTimeoutSeconds);

	TSharedPtr<FJsonObject> SubmitBody = MakeShared<FJsonObject>();
	SubmitBody->SetStringField(TEXT("prompt"), Request.Name);
	SubmitBody->SetStringField(TEXT("name"), Request.Name);
	SubmitBody->SetStringField(TEXT("usage"), Request.Usage);
	SubmitBody->SetNumberField(TEXT("width"), Request.Width);
	SubmitBody->SetNumberField(TEXT("height"), Request.Height);

	FString SubmitBodyText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&SubmitBodyText);
		FJsonSerializer::Serialize(SubmitBody.ToSharedRef(), Writer);
	}

	const FString SubmitUrl = JoinUrl(Endpoint, SubmitPath);
	int32 SubmitCode = 0;
	FString SubmitResponse;
	TArray<uint8> SubmitBytes;
	FString SubmitError;
	if (!TryRequestBlocking(TEXT("POST"), SubmitUrl, ApiKey, &SubmitBodyText, 60.0, SubmitCode, SubmitResponse, SubmitBytes, SubmitError))
	{
		Result.Error = FString::Printf(TEXT("Meshy texture submit failed: %s"), *SubmitError);
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageGen, Result.Error, TEXT("Meshy"));
		return Result;
	}

	TSharedPtr<FJsonObject> SubmitJson;
	if (!TryParseJson(SubmitResponse, SubmitJson))
	{
		Result.Error = TEXT("Meshy texture submit response is not valid JSON");
		return Result;
	}

	FString TaskId;
	if (!TryExtractTaskId(SubmitJson, TaskId))
	{
		Result.Error = FString::Printf(TEXT("Meshy texture submit did not return a task id: %s"), *SubmitResponse.Left(256));
		return Result;
	}

	TSharedPtr<FJsonObject> FinalJson;
	FString PollError;
	if (!PollTaskUntilTerminal(Endpoint, StatusPathTemplate, ApiKey, TaskId, PollInterval, PollTimeout, FinalJson, PollError))
	{
		Result.Error = PollError;
		return Result;
	}

	const FString BaseDir = EnsureDir(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedTextures")));
	FString SavedPath;
	FString SaveError;
	if (!TrySaveFromPayload(FinalJson, BaseDir, Request.Name.IsEmpty() ? TEXT("MeshyTexture") : Request.Name, TEXT("png"), ApiKey, SavedPath, SaveError))
	{
		Result.Error = SaveError;
		return Result;
	}

	Result.bSuccess = true;
	Result.OutputPath = SavedPath;
	Result.Summary = FString::Printf(TEXT("Meshy texture task %s completed"), *TaskId);
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageGen, Result.Summary, TEXT("Meshy"));
	return Result;
}

FModelServiceResult FMeshyImageTo3DService::GenerateModel(const FModelRequestV1& Request, const FString& SourceImage)
{
	FModelServiceResult Result;
	Result.bSuccess = false;

	const FString ApiKey = GetMeshyApiKey();
	const FString Endpoint = GetMeshyEndpoint();
	if (Endpoint.IsEmpty() || ApiKey.IsEmpty())
	{
		Result.Error = TEXT("Meshy endpoint/api key not configured");
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageTo3D, Result.Error, TEXT("Meshy"));
		return Result;
	}

	const FString SubmitPath = ReadSetting(TEXT("MeshyImageTo3DSubmitPath"), TEXT("/image-to-3d"));
	const FString StatusPathTemplate = ReadSetting(TEXT("MeshyImageTo3DStatusPath"), TEXT("/image-to-3d/{task_id}"));
	const double PollInterval = ReadSettingDouble(TEXT("MeshyPollingIntervalSeconds"), DefaultPollingIntervalSeconds);
	const double PollTimeout = ReadSettingDouble(TEXT("MeshyPollingTimeoutSeconds"), DefaultPollingTimeoutSeconds);

	const FString MeshName = Request.Name.IsEmpty() ? TEXT("MeshyMesh") : Request.Name;
	const FString Format = Request.Format.IsEmpty() ? TEXT("glb") : Request.Format.ToLower();

	TSharedPtr<FJsonObject> SubmitBody = MakeShared<FJsonObject>();
	SubmitBody->SetStringField(TEXT("prompt"), MeshName);
	SubmitBody->SetStringField(TEXT("name"), MeshName);
	SubmitBody->SetStringField(TEXT("format"), Format);

	if (!SourceImage.IsEmpty())
	{
		if (SourceImage.StartsWith(TEXT("http://")) || SourceImage.StartsWith(TEXT("https://")))
		{
			SubmitBody->SetStringField(TEXT("image_url"), SourceImage);
		}
		else if (FPaths::FileExists(SourceImage))
		{
			TArray<uint8> ImageData;
			if (FFileHelper::LoadFileToArray(ImageData, *SourceImage))
			{
				SubmitBody->SetStringField(TEXT("source_image_base64"), FBase64::Encode(ImageData));
			}
		}
	}

	FString SubmitBodyText;
	{
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&SubmitBodyText);
		FJsonSerializer::Serialize(SubmitBody.ToSharedRef(), Writer);
	}

	const FString SubmitUrl = JoinUrl(Endpoint, SubmitPath);
	int32 SubmitCode = 0;
	FString SubmitResponse;
	TArray<uint8> SubmitBytes;
	FString SubmitError;
	if (!TryRequestBlocking(TEXT("POST"), SubmitUrl, ApiKey, &SubmitBodyText, 60.0, SubmitCode, SubmitResponse, SubmitBytes, SubmitError))
	{
		Result.Error = FString::Printf(TEXT("Meshy model submit failed: %s"), *SubmitError);
		FPipelineLog::Get().Push(EPipelineLogLevel::Error, EPipelineStage::ImageTo3D, Result.Error, TEXT("Meshy"));
		return Result;
	}

	TSharedPtr<FJsonObject> SubmitJson;
	if (!TryParseJson(SubmitResponse, SubmitJson))
	{
		Result.Error = TEXT("Meshy model submit response is not valid JSON");
		return Result;
	}

	FString TaskId;
	if (!TryExtractTaskId(SubmitJson, TaskId))
	{
		Result.Error = FString::Printf(TEXT("Meshy model submit did not return a task id: %s"), *SubmitResponse.Left(256));
		return Result;
	}

	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageTo3D,
		FString::Printf(TEXT("Meshy task submitted: %s"), *TaskId),
		TEXT("Meshy"));

	TSharedPtr<FJsonObject> FinalJson;
	FString PollError;
	if (!PollTaskUntilTerminal(Endpoint, StatusPathTemplate, ApiKey, TaskId, PollInterval, PollTimeout, FinalJson, PollError))
	{
		Result.Error = PollError;
		return Result;
	}

	const FString BaseDir = EnsureDir(FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("VFXAgent"), TEXT("GeneratedMeshes")));
	FString SavedPath;
	FString SaveError;
	if (!TrySaveFromPayload(FinalJson, BaseDir, MeshName, Format, ApiKey, SavedPath, SaveError))
	{
		Result.Error = SaveError;
		return Result;
	}

	Result.bSuccess = true;
	Result.OutputPath = SavedPath;
	Result.Summary = FString::Printf(TEXT("Meshy 3D task %s completed"), *TaskId);
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageTo3D, Result.Summary, TEXT("Meshy"));
	return Result;
}
