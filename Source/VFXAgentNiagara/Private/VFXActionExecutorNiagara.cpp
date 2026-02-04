#include "VFXActionExecutorNiagara.h"
#include "NiagaraSpecExecutor.h"
#include "NiagaraSystem.h"
#include "NiagaraEmitter.h"
#include "NiagaraRendererProperties.h"
#include "NiagaraSpriteRendererProperties.h"
#include "NiagaraRibbonRendererProperties.h"
#include "NiagaraTypes.h"
#include "VFXRecipe.h"
#include "Materials/MaterialInterface.h"
#include "ImageUtils.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "VFXAgentLog.h"

static UNiagaraSystem* ResolveSystemFromContext(const FVFXAction& Action, FVFXActionContext& Context)
{
	if (!Action.System.IsEmpty())
	{
		if (UNiagaraSystem** Found = Context.SystemsByName.Find(Action.System))
		{
			return *Found;
		}
	}
	return Context.CurrentSystem;
}

static FString ResolveEmitterName(const FString& AliasOrName, const FVFXActionContext& Context)
{
	if (const FString* Found = Context.EmitterAliases.Find(AliasOrName))
	{
		return *Found;
	}
	return AliasOrName;
}

static FString ExtractEmitterFromTarget(const FString& Target)
{
	int32 DotIndex = INDEX_NONE;
	if (Target.FindChar(TEXT('.'), DotIndex))
	{
		return Target.Left(DotIndex);
	}
	return Target;
}

static FString ExtractTargetSuffix(const FString& Target)
{
	int32 DotIndex = INDEX_NONE;
	if (Target.FindChar(TEXT('.'), DotIndex))
	{
		return Target.Mid(DotIndex + 1);
	}
	return FString();
}

static FString BuildNiagaraVarName(const FString& EmitterName, const FString& TargetSuffix, const FString& ParamName)
{
	if (ParamName.Contains(TEXT(".")))
	{
		return FString::Printf(TEXT("%s.%s"), *EmitterName, *ParamName);
	}
	if (!TargetSuffix.IsEmpty())
	{
		return FString::Printf(TEXT("%s.%s.%s"), *EmitterName, *TargetSuffix, *ParamName);
	}
	return FString::Printf(TEXT("%s.%s"), *EmitterName, *ParamName);
}

static bool SetExposedParameter(UNiagaraSystem* System, const FString& FullVarName, const FVFXActionValue& Value)
{
	if (!System) return false;

	switch (Value.Type)
	{
	case EVFXValueType::Float:
	{
		FNiagaraVariable Var(FNiagaraTypeDefinition::GetFloatDef(), FName(*FullVarName));
		System->GetExposedParameters().SetParameterValue(Value.FloatValue, Var);
		return true;
	}
	case EVFXValueType::Int:
	{
		FNiagaraVariable Var(FNiagaraTypeDefinition::GetIntDef(), FName(*FullVarName));
		System->GetExposedParameters().SetParameterValue(Value.IntValue, Var);
		return true;
	}
	case EVFXValueType::Bool:
	{
		FNiagaraVariable Var(FNiagaraTypeDefinition::GetBoolDef(), FName(*FullVarName));
		System->GetExposedParameters().SetParameterValue(Value.BoolValue, Var);
		return true;
	}
	case EVFXValueType::Vec2:
	{
		FNiagaraVariable Var(FNiagaraTypeDefinition::GetVec2Def(), FName(*FullVarName));
		const FVector2f V((float)Value.Vec2.X, (float)Value.Vec2.Y);
		System->GetExposedParameters().SetParameterValue(V, Var);
		return true;
	}
	case EVFXValueType::Vec3:
	{
		FNiagaraVariable Var(FNiagaraTypeDefinition::GetVec3Def(), FName(*FullVarName));
		const FVector3f V((float)Value.Vec3.X, (float)Value.Vec3.Y, (float)Value.Vec3.Z);
		System->GetExposedParameters().SetParameterValue(V, Var);
		return true;
	}
	case EVFXValueType::Vec4:
	{
		FNiagaraVariable Var(FNiagaraTypeDefinition::GetVec4Def(), FName(*FullVarName));
		const FVector4f V((float)Value.Vec4.X, (float)Value.Vec4.Y, (float)Value.Vec4.Z, (float)Value.Vec4.W);
		System->GetExposedParameters().SetParameterValue(V, Var);
		return true;
	}
	case EVFXValueType::Color:
	{
		FNiagaraVariable Var(FNiagaraTypeDefinition::GetColorDef(), FName(*FullVarName));
		System->GetExposedParameters().SetParameterValue(Value.Color, Var);
		return true;
	}
	default:
		break;
	}

	return false;
}

static void LogReport(FVFXExecutionReport* Report, const FString& Message)
{
	if (Report)
	{
		Report->Logs.Add(Message);
	}
}

static void WarnReport(FVFXExecutionReport* Report, const FString& Message)
{
	if (Report)
	{
		Report->Warnings.Add(Message);
	}
}

static void ErrorReport(FVFXExecutionReport* Report, const FString& Message)
{
	if (Report)
	{
		Report->Errors.Add(Message);
	}
}

static FString NormalizeObjectPath(const FString& InPath)
{
	if (InPath.IsEmpty())
	{
		return InPath;
	}
	if (InPath.Contains(TEXT(".")))
	{
		return InPath;
	}
	const FString AssetName = FPackageName::GetShortName(InPath);
	return FString::Printf(TEXT("%s.%s"), *InPath, *AssetName);
}

static TArray<FString> GetMaterialLibraryRoots()
{
	TArray<FString> Roots;
	const TCHAR* Section = TEXT("/Script/VFXAgentEditor.VFXAgentSettings");
	const FString ConfigFiles[] = { GEditorIni, GGameIni, GEngineIni };
	for (const FString& File : ConfigFiles)
	{
		if (GConfig && GConfig->GetArray(Section, TEXT("MaterialLibraryPaths"), Roots, File) && Roots.Num() > 0)
		{
			break;
		}
	}
	if (Roots.Num() == 0)
	{
		Roots.Add(TEXT("/Game/VFXAgent/Materials"));
	}
	return Roots;
}

static bool IsInMaterialLibrary(const FString& ObjectPath)
{
	const FString PackagePath = FPackageName::ObjectPathToPackageName(ObjectPath);
	const TArray<FString> Roots = GetMaterialLibraryRoots();
	for (const FString& Root : Roots)
	{
		if (!Root.IsEmpty() && PackagePath.StartsWith(Root))
		{
			return true;
		}
	}
	return false;
}


static TArray<UNiagaraRendererProperties*> GetEmitterRenderers(UNiagaraEmitter* Emitter)
{
	TArray<UNiagaraRendererProperties*> Result;
	if (!Emitter) return Result;
	const FName PossibleNames[] = { TEXT("RendererProperties"), TEXT("Renderers") };
	for (const FName& Name : PossibleNames)
	{
		FArrayProperty* ArrayProp = FindFProperty<FArrayProperty>(Emitter->GetClass(), Name);
		if (!ArrayProp) continue;
		FScriptArrayHelper Helper(ArrayProp, ArrayProp->ContainerPtrToValuePtr<void>(Emitter));
		FObjectPropertyBase* InnerObjProp = CastField<FObjectPropertyBase>(ArrayProp->Inner);
		if (!InnerObjProp) break;
		for (int32 i = 0; i < Helper.Num(); ++i)
		{
			void* ElemPtr = Helper.GetRawPtr(i);
			UObject* Obj = InnerObjProp->GetObjectPropertyValue(ElemPtr);
			if (UNiagaraRendererProperties* RP = Cast<UNiagaraRendererProperties>(Obj))
			{
				Result.Add(RP);
			}
		}
		break;
	}
	return Result;
}

static bool AssignMaterialToEmitter(UNiagaraSystem* System, const FString& EmitterName, UMaterialInterface* Material)
{
	if (!System || !Material) return false;

	for (FNiagaraEmitterHandle& H : System->GetEmitterHandles())
	{
		if (H.GetName() != FName(*EmitterName)) continue;
		FVersionedNiagaraEmitter VersionedEmitter = H.GetInstance();
		UNiagaraEmitter* EmitterInstance = VersionedEmitter.Emitter;
		if (!EmitterInstance) return false;

		for (UNiagaraRendererProperties* Prop : GetEmitterRenderers(EmitterInstance))
		{
			if (UNiagaraSpriteRendererProperties* Sprite = Cast<UNiagaraSpriteRendererProperties>(Prop))
			{
				Sprite->Material = Material;
			}
			else if (UNiagaraRibbonRendererProperties* Ribbon = Cast<UNiagaraRibbonRendererProperties>(Prop))
			{
				Ribbon->Material = Material;
			}
		}

		EmitterInstance->Modify();
		EmitterInstance->PostEditChange();
		return true;
	}

	return false;
}

static bool RenderThumbnailToDisk(UObject* Object, const FString& OutPath)
{
	if (!Object || OutPath.IsEmpty()) return false;
	return false;
}

bool FVFXNiagaraActionExecutor::ExecuteAction(const FVFXAction& Action, FVFXActionContext& Context)
{
	switch (Action.Type)
	{
	case EVFXActionType::CreateSystem:
	{
		const FString OutputPath = Action.Path.IsEmpty() ? Context.DefaultOutputPath : Action.Path;
		UNiagaraSystem* System = FNiagaraSpecExecutor::CreateNiagaraSystemAsset(OutputPath, Action.Name);
		if (!System)
		{
			ErrorReport(Context.Report, FString::Printf(TEXT("CreateSystem failed: %s"), *Action.Name));
			return false;
		}
		Context.CurrentSystem = System;
		Context.SystemsByName.Add(Action.Name, System);
		if (Context.Report)
		{
			Context.Report->GeneratedAssets.Add(System->GetPathName());
		}
		LogReport(Context.Report, FString::Printf(TEXT("Created system: %s"), *System->GetPathName()));
		return true;
	}
	case EVFXActionType::AddEmitterFromTemplate:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("AddEmitterFromTemplate: no system"));
			return false;
		}
		const bool bOk = FNiagaraSpecExecutor::AddEmitterFromTemplate(System, Action.Template, Action.Alias);
		if (bOk)
		{
			Context.EmitterAliases.Add(Action.Alias, Action.Alias);
			LogReport(Context.Report, FString::Printf(TEXT("Added emitter '%s'"), *Action.Alias));
		}
		else
		{
			ErrorReport(Context.Report, FString::Printf(TEXT("Failed to add emitter '%s'"), *Action.Alias));
		}
		return bOk;
	}
	case EVFXActionType::AddModule:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("AddModule: no system"));
			return false;
		}
		const FString EmitterAlias = ExtractEmitterFromTarget(Action.Target);
		const FString EmitterName = ResolveEmitterName(EmitterAlias, Context);
		const bool bOk = FNiagaraSpecExecutor::AddModuleToEmitter(System, EmitterName, Action.Module, Action.Stack);
		if (!bOk)
		{
			WarnReport(Context.Report, FString::Printf(TEXT("AddModule failed: %s"), *Action.Module));
		}
		return bOk;
	}
	case EVFXActionType::SetParameter:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("SetParameter: no system"));
			return false;
		}
		const FString EmitterAlias = ExtractEmitterFromTarget(Action.Target);
		const FString EmitterName = ResolveEmitterName(EmitterAlias, Context);
		const FString TargetSuffix = ExtractTargetSuffix(Action.Target);
		const FString FullVarName = BuildNiagaraVarName(EmitterName, TargetSuffix, Action.ParamName);
		const bool bOk = SetExposedParameter(System, FullVarName, Action.Value);
		if (!bOk)
		{
			WarnReport(Context.Report, FString::Printf(TEXT("SetParameter failed: %s"), *FullVarName));
		}
		return bOk;
	}
	case EVFXActionType::BindEventHandler:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("BindEventHandler: no system"));
			return false;
		}
		const FString SourceAlias = ResolveEmitterName(Action.Target, Context);
		const FString TargetAlias = ResolveEmitterName(Action.Alias, Context);
		if (Action.Event.ToLower().Contains(TEXT("collision")))
		{
			FVFXEventRecipe EventRecipe;
			EventRecipe.Type = EVFXEventType::OnEmitterCollision;
			const bool bOk = FNiagaraSpecExecutor::ConfigureCollisionEventHandler(System, SourceAlias, TargetAlias, EventRecipe);
			return bOk;
		}
		WarnReport(Context.Report, FString::Printf(TEXT("BindEventHandler not implemented for event '%s'"), *Action.Event));
		return false;
	}
	case EVFXActionType::EnableDrag:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("EnableDrag: no system"));
			return false;
		}
		const FString EmitterAlias = ExtractEmitterFromTarget(Action.Target);
		const FString EmitterName = ResolveEmitterName(EmitterAlias, Context);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Drag.Drag"), Action.DragCoef);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Drag"), Action.DragCoef);
		FNiagaraSpecExecutor::SetVariableFloat(System, EmitterName, TEXT("Drag.InheritVelocity"), Action.InheritVel);
		return true;
	}
	case EVFXActionType::CreateMaterialInstance:
	{
		WarnReport(Context.Report, TEXT("CreateMaterialInstance skipped (material generation disabled)."));
		return true;
	}
	case EVFXActionType::AssignRendererMaterial:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("AssignRendererMaterial: no system"));
			return false;
		}
		const FString NormalizedMaterialPath = NormalizeObjectPath(Action.Material);
		if (!IsInMaterialLibrary(NormalizedMaterialPath))
		{
			ErrorReport(Context.Report, FString::Printf(TEXT("AssignRendererMaterial blocked (not in material library): %s"), *Action.Material));
			return false;
		}
		UMaterialInterface* Mat = LoadObject<UMaterialInterface>(nullptr, *NormalizedMaterialPath);
		if (!Mat)
		{
			ErrorReport(Context.Report, FString::Printf(TEXT("AssignRendererMaterial: material not found: %s"), *Action.Material));
			return false;
		}
		const FString EmitterAlias = ExtractEmitterFromTarget(Action.Target);
		const FString EmitterName = ResolveEmitterName(EmitterAlias, Context);
		return AssignMaterialToEmitter(System, EmitterName, Mat);
	}
	case EVFXActionType::CompileAndValidate:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("CompileAndValidate: no system"));
			return false;
		}
		FVFXRepairReport Report;
		const bool bOk = FNiagaraSpecExecutor::SaveCompileAndSelfCheck(System, Report);
		if (!bOk)
		{
			for (const FString& E : Report.Errors) ErrorReport(Context.Report, E);
			for (const FString& W : Report.Warnings) WarnReport(Context.Report, W);
		}
		else
		{
			LogReport(Context.Report, TEXT("CompileAndValidate succeeded"));
		}
		if (Context.Report)
		{
			Context.Report->GeneratedAssets.Add(Report.SystemPath);
		}
		return bOk;
	}
	case EVFXActionType::RenderThumbnail:
	{
		UNiagaraSystem* System = ResolveSystemFromContext(Action, Context);
		if (!System)
		{
			ErrorReport(Context.Report, TEXT("RenderThumbnail: no system"));
			return false;
		}
		const bool bOk = RenderThumbnailToDisk(System, Action.Out);
		if (bOk && Context.Report)
		{
			Context.Report->ThumbnailPath = Action.Out;
		}
		return bOk;
	}
	default:
		break;
	}

	WarnReport(Context.Report, TEXT("Unknown action type"));
	return false;
}

bool FVFXNiagaraActionExecutor::ExecuteActionList(const TArray<FVFXAction>& Actions, FVFXActionContext& Context)
{
	bool bAllOk = true;
	for (const FVFXAction& Action : Actions)
	{
		const bool bOk = ExecuteAction(Action, Context);
		bAllOk = bAllOk && bOk;
	}
	if (Context.Report)
	{
		Context.Report->bSuccess = bAllOk && Context.Report->Errors.Num() == 0;
	}
	return bAllOk;
}
