#include "MeshyModelServices.h"
#include "PipelineLog.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
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

static FString GetMeshyApiKey()
{
	FString Key;
	GConfig->GetString(TEXT("VFXAgent"), TEXT("MeshyApiKey"), Key, GEngineIni);
	return Key;
}

static FString GetMeshyEndpoint()
{
	FString Endpoint;
	GConfig->GetString(TEXT("VFXAgent"), TEXT("MeshyEndpoint"), Endpoint, GEngineIni);
	if (Endpoint.IsEmpty())
	{
		Endpoint = TEXT("https://api.meshy.ai/v1");
	}
	return Endpoint;
}

FModelServiceResult FMeshyImageGenService::GenerateTexture(const FTextureRequestV1& Request)
{
	FModelServiceResult Result;
	Result.bSuccess = false;
	Result.Error = TEXT("Meshy Text-to-Texture not fully implemented yet.");
	
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageGen, TEXT("Meshy GenerateTexture called"), TEXT("Meshy"));
	
	// TODO: Implement Meshy Text-to-Texture API polling
	
	return Result;
}

FModelServiceResult FMeshyImageTo3DService::GenerateModel(const FModelRequestV1& Request, const FString& SourceImage)
{
	FModelServiceResult Result;
	Result.bSuccess = false;
	Result.Error = TEXT("Meshy Image-to-3D not fully implemented yet.");
	
	FPipelineLog::Get().Push(EPipelineLogLevel::Info, EPipelineStage::ImageTo3D, TEXT("Meshy GenerateModel called"), TEXT("Meshy"));
	
	// TODO: Implement Meshy Image-to-3D API polling
	
	return Result;
}
