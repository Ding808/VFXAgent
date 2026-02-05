#include "PipelineLog.h"

FPipelineLog& FPipelineLog::Get()
{
	static FPipelineLog Instance;
	return Instance;
}

void FPipelineLog::Push(const FPipelineLogEntry& Entry)
{
	FScopeLock Lock(&Mutex);
	Queue.Enqueue(Entry);
}

void FPipelineLog::Push(EPipelineLogLevel Level, EPipelineStage Stage, const FString& Message, const FString& Provider)
{
	FPipelineLogEntry Entry;
	Entry.Timestamp = FDateTime::UtcNow();
	Entry.Level = Level;
	Entry.Stage = Stage;
	Entry.Provider = Provider;
	Entry.Message = Message;
	Push(Entry);
}

void FPipelineLog::Drain(TArray<FPipelineLogEntry>& OutEntries)
{
	FScopeLock Lock(&Mutex);
	FPipelineLogEntry Entry;
	while (Queue.Dequeue(Entry))
	{
		OutEntries.Add(Entry);
	}
}
