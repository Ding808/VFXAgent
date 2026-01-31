#pragma once

#include "CoreMinimal.h"

// Export/import macro so the log symbol is visible across modules
#if defined(VFXAGENTCORE_API)
	#define VFXAGENT_API VFXAGENTCORE_API
#elif defined(VFXAGENTNIAGARA_API)
	#define VFXAGENT_API VFXAGENTNIAGARA_API
#elif defined(VFXAGENTEDITOR_API)
	#define VFXAGENT_API VFXAGENTEDITOR_API
#else
	#define VFXAGENT_API
#endif

VFXAGENT_API DECLARE_LOG_CATEGORY_EXTERN(LogVFXAgent, Log, All);