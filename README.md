# VFXAgent - AI-Powered Niagara VFX Generator for UE5.5

A comprehensive Unreal Engine 5.5 editor plugin that leverages LLM to automatically generate Niagara VFX systems from natural language descriptions. Users can generate, refine, and iterate on VFX effects through a simple editor panel.

## Project Structure

```
VFXAgent/
├── Source/
│   ├── VFXAgentCore/
│   │   ├── Public/
│   │   │   ├── VFXAgentCoreModule.h
│   │   │   ├── VFXAgentLog.h
│   │   │   ├── VFXRecipe.h                    # Core data structure (USTRUCT)
│   │   │   ├── ILLMProvider.h                 # LLM interface
│   │   │   ├── MockLLMProvider.h              # Mock implementation
│   │   │   └── HttpLLMProvider.h              # HTTP placeholder
│   │   ├── Private/
│   │   │   ├── VFXAgentCoreModule.cpp
│   │   │   ├── VFXAgentLog.cpp
│   │   │   ├── MockLLMProvider.cpp
│   │   │   └── HttpLLMProvider.cpp
│   │   └── VFXAgentCore.Build.cs
│   │
│   ├── VFXAgentNiagara/
│   │   ├── Public/
│   │   │   ├── VFXAgentNiagaraModule.h
│   │   │   ├── INiagaraSystemGenerator.h      # Interface for system generation
│   │   │   ├── NiagaraSystemGenerator.h       # Implementation
│   │   │   ├── IAssetGenService.h             # Asset gen interface (extensible)
│   │   │   └── BasicAssetGenService.h         # Placeholder asset service
│   │   ├── Private/
│   │   │   ├── VFXAgentNiagaraModule.cpp
│   │   │   ├── NiagaraSystemGenerator.cpp
│   │   │   └── BasicAssetGenService.cpp
│   │   └── VFXAgentNiagara.Build.cs
│   │
│   └── VFXAgentEditor/
│       ├── Public/
│       │   ├── VFXAgentEditorModule.h
│       │   ├── VFXAgentSettings.h             # DeveloperSettings for configuration
│       │   └── SVFXAgentPanel.h               # Slate UI panel
│       ├── Private/
│       │   ├── VFXAgentEditorModule.cpp
│       │   └── SVFXAgentPanel.cpp
│       └── VFXAgentEditor.Build.cs
│
├── Config/
│   └── DefaultVFXAgent.ini                    # Plugin configuration
│
├── Content/                                   # Plugin content (templates, etc.)
├── Resources/
│   └── Icon128.png                            # Plugin icon
└── VFXAgent.uplugin                           # Plugin descriptor

```

## Module Architecture

### VFXAgentCore (Developer Module)
- **Purpose**: Protocol and LLM interface definitions
- **Key Classes**:
  - `FVFXRecipe`: Structured recipe format (USTRUCT) for VFX configuration
  - `FVFXEmitterRecipe`: Individual emitter configuration
  - `FVFXMaterialRecipe`: Material requirements
  - `ILLMProvider`: Interface for LLM implementations
  - `UMockLLMProvider`: Mock implementation for testing
  - `UHttpLLMProvider`: Placeholder for HTTP-based LLM services

### VFXAgentNiagara (Editor Module)
- **Purpose**: Niagara system generation and asset management
- **Key Classes**:
  - `INiagaraSystemGenerator`: Interface for system generation
  - `UNiagaraSystemGenerator`: Generates/updates Niagara systems from recipes
  - `IAssetGenService`: Interface for material/texture/mesh generation (extensible)
  - `UBasicAssetGenService`: Placeholder implementations for future asset generation

### VFXAgentEditor (Editor Module)
- **Purpose**: UI and editor integration
- **Key Classes**:
  - `UVFXAgentSettings`: Developer settings for LLM endpoint, output paths
  - `SVFXAgentPanel`: Slate-based editor panel with:
    - Prompt input for VFX description
    - Output path and asset naming configuration
    - Generate button
    - Refinement prompt input and Apply button
    - Real-time log display

## Features

### MVP (Implemented)

1. **Editor Panel** (`Window → VFX Agent`)
   - Natural language prompt input for VFX descriptions
   - Output path and asset naming configuration
   - Generate button triggers LLM + Niagara system creation
   - Refinement/iteration support with versioning (_v1, _v2, etc.)
   - Real-time log display

2. **VFX Recipe Protocol**
   - Structured USTRUCT format for VFX specifications
   - Supports emitter configuration (spawn rate, type, color, lifetime)
   - Material requirements (additive, custom material paths)
   - User parameters (color, intensity, etc.)
   - Dependencies tracking for textures/models
   - Version tracking for iterations

3. **LLM Integration**
   - Interface-based architecture for multiple provider implementations
   - MockLLMProvider for testing and development
   - HttpLLMProvider skeleton for future HTTP/REST integration
   - Structured JSON output (VFXRecipe format)

4. **Niagara System Generation**
   - Create UNiagaraSystem assets from VFX recipes
   - Asset package creation with proper naming
   - SavePackage integration for asset persistence
   - Basic emitter support framework

5. **Iterative Refinement**
   - Preserve previous recipe and prompt
   - Natural language refinement commands
   - Version-based asset naming for iteration history
   - Re-generate with updated recipes

### Extensible (Placeholders for Future)

- **Material Generation**: `IAssetGenService::GenerateMaterial()` interface ready
- **Texture Generation**: `IAssetGenService::GenerateTexture()` placeholder
- **Mesh Generation**: `IAssetGenService::GenerateStaticMesh()` placeholder
- **HTTP LLM Provider**: Skeleton ready for Ollama, OpenAI, or local LLM integration
- **Advanced Emitter Setup**: Framework for sprite, mesh, ribbon renderers

## Configuration

### Settings Location
**Project Settings → VFXAgent**

Available settings:
- `LLMEndpoint`: HTTP endpoint for LLM service (default: `http://localhost:11434/api/generate`)
- `LLMModel`: Model name for LLM (default: `llama2`)
- `DefaultOutputPath`: Default content path for generated assets (default: `/Game/VFXAgent/Generated`)
- `AssetNamePrefix`: Prefix for generated asset names (default: `VFX_`)

### Config File
- **Location**: `Config/DefaultVFXAgent.ini`
- **Customizable**: Yes, modify values as needed

## Building and Running

### Prerequisites
- Unreal Engine 5.5 installed
- Visual Studio 2022 or later
- Windows (PowerShell execution confirmed)

### Build Steps

1. **Generate Visual Studio Project**
   - Right-click on `.uproject` → Generate Visual Studio project files
   - (Or use Unreal Automation Tool if preferred)

2. **Build the Plugin**
   ```powershell
   cd E:\VFXAgent
   # Compile all modules
   # If using Unreal's build system:
   # UnrealBuildTool.exe VFXAgent -TargetType=Editor -Platform=Win64 -Configuration=Development -Project="E:\VFXAgent\VFXAgent.uproject"
   ```

3. **Open in Unreal Editor**
   - Launch UE5.5 with the project
   - Plugin should load automatically (modules: VFXAgentCore, VFXAgentNiagara, VFXAgentEditor)

4. **Access VFX Agent**
   - In Editor: `Window → VFX Agent` (menu entry added by the editor module)
   - Panel opens with all input fields and log

### Troubleshooting

- **Module not found**: Verify `.Build.cs` files have correct module dependencies
- **Slate compilation errors**: Ensure `UnrealEd`, `ToolMenus`, `Slate` are in Public/PrivateDependencyModuleNames
- **Niagara not compiling**: Ensure `Niagara` module is listed in VFXAgentNiagara.Build.cs
- **Log category missing**: Include `VFXAgentLog.h` where needed

## Usage Example

1. **Open VFX Agent Panel**
   - Window menu → VFX Agent

2. **Enter Prompt**
   - Example: "A blue electric arc explosion with smoke trails"

3. **Configure Output**
   - Output Path: `/Game/VFXAgent/Generated`
   - Asset Name: `VFX_ArcExplosion_01`

4. **Generate**
   - Click "Generate" button
   - Check Content Browser for new Niagara system asset
   - Monitor log for generation status

5. **Refine** (Optional)
   - Refinement Input: "Make it red and slower"
   - Click "Apply Refinement"
   - New asset generated as `VFX_ArcExplosion_01_v2`

## Code Structure Notes

### Include Organization
- Core data structures in `VFXAgentCore/Public`
- Generation logic in `VFXAgentNiagara/Public` and `Private`
- UI in `VFXAgentEditor/Public` and `Private`

### Naming Conventions
- Headers: `.h`
- Implementations: `.cpp`
- Interfaces: `I*` prefix
- Slate widgets: `S*` prefix
- Unreal objects: `U*` prefix
- Modules: `*Module.h/.cpp`

### Key Design Patterns
- **Interface-based**: LLMProvider, AssetGenService for extensibility
- **Factory pattern**: NiagaraSystemGenerator creates assets
- **Settings pattern**: UDeveloperSettings for configuration
- **Slate widget composition**: SVFXAgentPanel uses standard Slate widgets

## Compilation Verification

All files include:
- ✅ Required includes (`CoreMinimal.h`, `Modules/ModuleManager.h`, etc.)
- ✅ Module dependency declarations (`.Build.cs`)
- ✅ UPLUGIN module configuration
- ✅ Log category definition
- ✅ Proper preprocessor directives

## Future Extensions

### Phase 2
- Implement HttpLLMProvider for Ollama/OpenAI integration
- Add material parameter input validation
- Support Mesh and Ribbon renderer types
- Texture/material asset generation

### Phase 3
- Template-based system creation
- Parameter UI generation from recipe
- Batch generation support
- Asset organization and prefixing

### Phase 4
- VFX marketplace integration
- User library management
- Collaborative refinement
- Advanced Niagara graph manipulation

## Support and Debugging

Enable detailed logging:
```cpp
// In any source file:
UE_LOG(LogVFXAgent, Log, TEXT("Your message here"));
UE_LOG(LogVFXAgent, Warning, TEXT("Warning: %s"), *Message);
UE_LOG(LogVFXAgent, Error, TEXT("Error: %s"), *Message);
```

Output visible in:
- Unreal Editor Output Log
- Visual Studio Debug Output (when running in debug)

---

**Author**: VFXAgent Development Team  
**Version**: 1.0  
**Engine**: Unreal Engine 5.5+  
**License**: [Your License Here]