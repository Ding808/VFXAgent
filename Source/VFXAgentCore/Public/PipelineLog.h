#pragma once

#include "CoreMinimal.h"
#include "Containers/Queue.h"

enum class EPipelineLogLevel : uint8
{
	Info,
	Warning,
	Error
};

enum class EPipelineStage : uint8
{
	Orchestrator,
	LLM,
	ImageGen,
	ImageTo3D,
	Import,
	Material,
	Niagara,
	Validate,
	Fallback
};

struct FPipelineLogEntry
{
	FDateTime Timestamp;
	EPipelineLogLevel Level = EPipelineLogLevel::Info;
	EPipelineStage Stage = EPipelineStage::Orchestrator;
	FString Provider;
	FString Message;
	FString Detail;
	int32 CurrentStep = 0;
	int32 TotalSteps = 0;
	float Percent = -1.0f;
};

class VFXAGENTCORE_API FPipelineLog
{
public:
	static FPipelineLog& Get();

	void Push(const FPipelineLogEntry& Entry);
	void Push(EPipelineLogLevel Level, EPipelineStage Stage, const FString& Message, const FString& Provider = FString());
	void Drain(TArray<FPipelineLogEntry>& OutEntries);

private:
	FCriticalSection Mutex;
	TQueue<FPipelineLogEntry, EQueueMode::Mpsc> Queue;
};
