# VFXAgent Plugin - Quick Reference Card

## 📦 Project Structure at a Glance

```
VFXAgent/
├── Source/
│   ├── VFXAgentCore/        (8 files)  Protocol & LLM
│   ├── VFXAgentNiagara/     (8 files)  Generation & Assets
│   └── VFXAgentEditor/      (7 files)  UI & Integration
├── Config/                           Settings
├── Content/                          Templates (future)
├── Resources/                        Icon128.png
└── VFXAgent.uplugin                 Descriptor
```

## 🎯 Core Components

| Component | File | Purpose |
|-----------|------|---------|
| **Data Protocol** | VFXRecipe.h | Recipe USTRUCT (Loop, Emitters[], Materials[], Parameters) |
| **LLM Interface** | ILLMProvider.h | Generate/Refine VFXRecipe methods |
| **Mock LLM** | MockLLMProvider | Returns hardcoded blue sprite recipe |
| **Niagara Gen** | NiagaraSystemGenerator | Creates UNiagaraSystem assets |
| **Asset Service** | IAssetGenService | Material/Texture/Mesh placeholders |
| **Settings** | VFXAgentSettings.h | LLMEndpoint, OutputPath, etc. |
| **UI Panel** | SVFXAgentPanel | Slate widget with input/log |
| **Menu Integration** | VFXAgentEditorModule | Window → VFX Agent |

## 📊 Data Flow

```
Prompt Input
    ↓ [SVFXAgentPanel]
LLM Call
    ↓ [MockLLMProvider.GenerateRecipe()]
VFXRecipe (JSON-compatible USTRUCT)
    ↓ [NiagaraSystemGenerator]
UNiagaraSystem Asset
    ↓ [UPackage::SavePackage()]
Content Browser: /Game/VFXAgent/Generated/VFX_*
```

## 🔌 Key Interfaces

### ILLMProvider
```cpp
GenerateRecipe(Prompt: String) → FVFXRecipe
RefineRecipe(OldRecipe, RefinementPrompt) → FVFXRecipe
```

**Implementations**:
- ✅ MockLLMProvider (working)
- 🔵 HttpLLMProvider (skeleton)

### INiagaraSystemGenerator
```cpp
GenerateNiagaraSystem(Name, Path, Recipe) → UNiagaraSystem*
UpdateNiagaraSystem(System, Recipe) → bool
```

**Implementation**:
- ✅ UNiagaraSystemGenerator (working for basic systems)

### IAssetGenService
```cpp
GenerateMaterial(Name, Path) → UMaterialInstanceConstant*
GenerateTexture(Name, Path) → UTexture2D*
GenerateStaticMesh(Name, Path) → UStaticMesh*
```

**Implementation**:
- 🔵 UBasicAssetGenService (skeleton)

## 🎮 UI Workflow

1. **Window → VFX Agent** - Opens SVFXAgentPanel
2. **Input Prompt** - "A blue electric arc explosion"
3. **Click Generate** - OnGenerateClicked()
4. **Check Log** - See generation status
5. **Browse Content** - `/Game/VFXAgent/Generated/`
6. **Refine** (Optional) - "Make it red and slower"
7. **Apply Refinement** - Creates _v2 asset

## ⚙️ Module Dependencies

```
VFXAgentEditor
    ├─→ VFXAgentCore
    ├─→ VFXAgentNiagara
    ├─→ Slate, SlateCore, UnrealEd, ToolMenus, AssetTools
    └─→ Json, JsonUtilities

VFXAgentNiagara
    ├─→ VFXAgentCore
    ├─→ Niagara, AssetTools, UnrealEd
    └─→ Core, Engine

VFXAgentCore
    └─→ Core, Engine, Json, JsonUtilities
```

## 📝 Build Steps (Quick)

```powershell
# 1. Generate VS files
Right-click VFXAgent.uproject → "Generate Visual Studio project files"

# 2. Build in Visual Studio
Open .sln → Build Solution (Ctrl+Shift+B)

# 3. Test in Editor
Open project in UE5.5 → Window → VFX Agent
```

## 📍 File Locations

| What | Where |
|------|-------|
| Core Data | `VFXAgentCore/Public/VFXRecipe.h` |
| LLM Interface | `VFXAgentCore/Public/ILLMProvider.h` |
| Niagara Gen | `VFXAgentNiagara/Public/NiagaraSystemGenerator.h` |
| UI Panel | `VFXAgentEditor/Public/SVFXAgentPanel.h` |
| Settings | `VFXAgentEditor/Public/VFXAgentSettings.h` |
| Log Category | `VFXAgentCore/Public/VFXAgentLog.h` |
| Module Init | `*/Public/*Module.h` |
| Build Config | `*/Module.Build.cs` |

## 🔍 Logging

All logs use **LogVFXAgent** category:

```cpp
UE_LOG(LogVFXAgent, Log, TEXT("Message"));
UE_LOG(LogVFXAgent, Warning, TEXT("Warning"));
UE_LOG(LogVFXAgent, Error, TEXT("Error"));
```

**View in**: Window → Developer Tools → Output Log

## 🧩 Settings

**Location**: Project Settings → VFXAgent

```
LLMEndpoint = http://localhost:11434/api/generate
LLMModel = llama2
DefaultOutputPath = /Game/VFXAgent/Generated
AssetNamePrefix = VFX_
```

**File**: `Config/DefaultVFXAgent.ini`

## 🚀 Testing Commands

```
// Launch VFX Agent
Window → VFX Agent

// Test Generation
Prompt: "A blue electric arc explosion with smoke trails"
Output: /Game/VFXAgent/Generated
Name: VFX_TestEffect_01
Click: Generate

// Test Refinement
Refinement: "Make it red and slower"
Click: Apply Refinement
Result: VFX_TestEffect_01_v2
```

## 📋 Checklist

- [ ] All 23 files present
- [ ] VFXAgent.uplugin updated with modules
- [ ] .Build.cs files have correct dependencies
- [ ] Compiles without errors
- [ ] Modules load (check Output Log)
- [ ] VFX Agent menu visible
- [ ] Panel opens without crash
- [ ] Generate creates Niagara system
- [ ] Logs display correctly
- [ ] Refinement creates versioned asset

## 🔮 Extension Points

| Feature | File | Method | Status |
|---------|------|--------|--------|
| HTTP LLM | HttpLLMProvider | GenerateRecipe() | 🔵 TODO |
| Material Gen | BasicAssetGenService | GenerateMaterial() | 🔵 TODO |
| Texture Gen | BasicAssetGenService | GenerateTexture() | 🔵 TODO |
| Mesh Gen | BasicAssetGenService | GenerateStaticMesh() | 🔵 TODO |
| Emitters | NiagaraSystemGenerator | CreateBasicEmitter() | 🔵 TODO |
| Material Binding | NiagaraSystemGenerator | BindMaterialToEmitter() | 🔵 TODO |

## 💡 Key Code Examples

### Create Recipe
```cpp
FVFXRecipe Recipe;
Recipe.bLoop = true;
Recipe.Duration = 0.0f;
FVFXEmitterRecipe Emitter;
Emitter.Color = FLinearColor::Blue;
Recipe.Emitters.Add(Emitter);
```

### Generate System
```cpp
UNiagaraSystemGenerator* Gen = NewObject<UNiagaraSystemGenerator>();
UNiagaraSystem* System = Gen->GenerateNiagaraSystem(
    "MyVFX", 
    "/Game/VFXAgent/Generated", 
    Recipe
);
```

### Call LLM
```cpp
ILLMProvider* LLM = NewObject<UMockLLMProvider>();
FVFXRecipe Recipe = LLM->GenerateRecipe("Blue electric arc");
```

### Log Message
```cpp
UE_LOG(LogVFXAgent, Log, TEXT("Generated system: %s"), *SystemName);
```

## 📞 Troubleshooting

| Problem | Solution |
|---------|----------|
| Module not found | Check VFXAgent.uplugin Modules[] |
| Compile error | Verify .Build.cs dependencies |
| No menu entry | Ensure VFXAgentEditor loads in Output Log |
| Crash on open | Check SVFXAgentPanel.cpp includes |
| No logs visible | Filter Output Log for "VFXAgent" |

## 📚 Documentation Files

- **README.md** - Full architecture & usage
- **BUILD_GUIDE.md** - Step-by-step compilation
- **FILE_MANIFEST.md** - Complete file inventory
- **GENERATION_SUMMARY.md** - High-level overview

## 🎯 Success Indicators

✅ Output Log shows:
```
LogVFXAgent: VFXAgentCore Module Started
LogVFXAgent: VFXAgentNiagara Module Started
LogVFXAgent: VFXAgentEditor Module Started
LogVFXAgent: VFXAgentPanel initialized
LogVFXAgent: Generating Niagara System: VFX_TestEffect_01
LogVFXAgent: Successfully saved Niagara System
```

## 📞 Contact Info

For issues, check:
1. BUILD_GUIDE.md (Compilation section)
2. README.md (Troubleshooting)
3. Output Log (LogVFXAgent)
4. Visual Studio compiler output

---

**Quick Reference v1.0**  
**VFXAgent Plugin for UE5.5**  
**Generated: 2026-01-25**