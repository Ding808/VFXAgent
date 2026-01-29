# VFXAgent Plugin - Build and Compilation Guide for UE5.5

## Prerequisites

- **Engine**: Unreal Engine 5.5 (recommended 5.5.0 or later)
- **Visual Studio**: 2022 Community Edition or Professional
- **Windows SDK**: Windows 10 SDK or later
- **Project**: C++ project (editor mode)

## Step 1: Verify Plugin Structure

Before building, verify the plugin directory structure:

```
E:\VFXAgent\VFXAgent\
├── Source/
│   ├── VFXAgentCore/
│   │   ├── Public/
│   │   ├── Private/
│   │   └── VFXAgentCore.Build.cs
│   ├── VFXAgentEditor/
│   │   ├── Public/
│   │   ├── Private/
│   │   └── VFXAgentEditor.Build.cs
│   └── VFXAgentNiagara/
│       ├── Public/
│       ├── Private/
│       └── VFXAgentNiagara.Build.cs
├── Config/
│   └── DefaultVFXAgent.ini
├── Content/
├── Resources/
│   └── Icon128.png
└── VFXAgent.uplugin
```

All 23 source files should be present.

## Step 2: Generate Visual Studio Project Files

### Option A: Using Unreal Engine (Recommended)

1. Navigate to your Unreal Engine installation directory
2. Open Command Prompt and run:

```cmd
cd "C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles"

RunUAT.bat BuildPlugin -Plugin="E:\VFXAgent\VFXAgent\VFXAgent.uplugin" -Package="E:\VFXAgent\VFXAgent\Binaries\Win64" -CreateNew -TargetPlatforms=Win64
```

### Option B: Using Visual Studio Project Generator

1. Right-click on `VFXAgent.uplugin`
2. Select "Generate Visual Studio project files"

### Option C: Manual Generation

```powershell
# In PowerShell (as Administrator)
cd "C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles"

# Generate project files
.\GenerateProjectFiles.bat -ProjectFiles -Engine="E:\VFXAgent" -Game="E:\VFXAgent\VFXAgent.uproject"
```

## Step 3: Build the Plugin

### Option A: Build from Unreal Automation Tool

```powershell
cd "C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles"

# Build for Editor
.\RunUAT.bat BuildPlugin `
  -Plugin="E:\VFXAgent\VFXAgent\VFXAgent.uplugin" `
  -Package="E:\VFXAgent\Binaries\Win64" `
  -TargetPlatforms=Win64 `
  -CreateNew
```

### Option B: Build from Visual Studio

1. Open the generated `.sln` file in the plugin directory
2. Select **Development Editor** configuration
3. Build solution (Ctrl+Shift+B)
4. Wait for compilation to complete

### Option C: Build from Command Line

```powershell
# Navigate to UE binary tools
cd "C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64"

# Compile specific modules
.\UE4Editor-Cmd.exe E:\VFXAgent\VFXAgent.uproject -run=BuildPlugin -Plugin="VFXAgent" -TargetPlatforms=Win64
```

## Step 4: Verify Compilation

### Expected Output

During compilation, you should see:
- ✅ VFXAgentCore.Build.cs compiling
- ✅ VFXAgentNiagara.Build.cs compiling
- ✅ VFXAgentEditor.Build.cs compiling
- ✅ No linker errors
- ✅ Final message: "Successfully built project"

### Troubleshooting Common Errors

#### Error: "Module VFXAgentCore not found"
**Solution**: Verify VFXAgent.uplugin has correct module definitions:
```json
"Modules": [
  {
    "Name": "VFXAgentCore",
    "Type": "Developer",
    "LoadingPhase": "Default"
  },
  ...
]
```

#### Error: "Unknown module 'Niagara'"
**Solution**: Check VFXAgentNiagara.Build.cs includes:
```csharp
PublicDependencyModuleNames.AddRange(
  new string[] {
    "Niagara",
    ...
  }
);
```

#### Error: "FSlateApplication not found"
**Solution**: Ensure VFXAgentEditor.Build.cs includes:
```csharp
PublicDependencyModuleNames.AddRange(
  new string[] {
    "Slate",
    "SlateCore",
    "UnrealEd",
    ...
  }
);
```

#### Error: "LLM include missing"
**Solution**: Verify VFXAgentCore.Build.cs has:
```csharp
PublicDependencyModuleNames.AddRange(
  new string[] {
    "Json",
    "JsonUtilities",
    ...
  }
);
```

## Step 5: Launch Unreal Editor with Plugin

### Method 1: Direct Launch

1. Open the Unreal Launcher
2. Select **UE 5.5**
3. Create new C++ project (or open existing)
4. Copy the plugin folder to `YourProject/Plugins/VFXAgent`
5. Right-click `.uproject` → "Generate Visual Studio project files"
6. Rebuild solution in Visual Studio
7. Open project in editor

### Method 2: Command Line

```powershell
# Launch editor with plugin
"C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64\UE4Editor.exe" `
  "E:\YourProject\YourProject.uproject" `
  -Game
```

### Method 3: Plugin Folder Installation

1. Copy entire `VFXAgent` folder to `YourProject/Plugins/`
2. Open `.uproject` file in editor
3. Auto-prompt to rebuild plugin
4. Click "Yes" to rebuild
5. Editor restarts with plugin loaded

## Step 6: Verify Plugin Load

In Unreal Editor:

1. **Check Plugin is Enabled**
   - Edit → Plugins
   - Search "VFXAgent"
   - Verify "Enabled" checkbox is checked

2. **Check Output Log**
   - Window → Developer Tools → Output Log
   - Filter for "VFXAgent"
   - Should see:
     ```
     LogVFXAgent: VFXAgentCore Module Started
     LogVFXAgent: VFXAgentNiagara Module Started
     LogVFXAgent: VFXAgentEditor Module Started
     ```

3. **Access VFX Agent Panel**
   - Window menu → VFX Agent
   - Panel opens with UI

## Step 7: Test the Plugin

### Test 1: Launch Panel
1. Click Window → VFX Agent
2. Verify panel opens without errors

### Test 2: Generate VFX
1. Enter prompt: "A blue electric arc"
2. Keep default output path: `/Game/VFXAgent/Generated`
3. Asset name: `VFX_TestEffect_01`
4. Click "Generate"
5. Check Output Log for success message
6. Check Content Browser for new Niagara system

### Test 3: Refinement
1. Enter refinement: "Make it red"
2. Click "Apply Refinement"
3. Verify new asset created as `VFX_TestEffect_01_v2`

## Build Configuration Reference

### Debug Configuration
- **Use for**: Development, debugging, detailed logging
- **Performance**: Slower
- **Symbol information**: Full
- **Command**: `-Configuration=Debug`

### Development Configuration (Recommended for Plugin)
- **Use for**: Testing, normal development
- **Performance**: Good
- **Symbol information**: Limited
- **Command**: `-Configuration=Development`

### Release Configuration
- **Use for**: Shipping
- **Performance**: Optimized
- **Symbol information**: Minimal
- **Command**: `-Configuration=Shipping`

## Module Dependencies Summary

### VFXAgentCore
```
Core
CoreUObject
Engine
Json
JsonUtilities
```

### VFXAgentNiagara
```
Core
CoreUObject
Engine
Niagara
UnrealEd
AssetTools
VFXAgentCore
```

### VFXAgentEditor
```
Core
CoreUObject
Engine
Slate
SlateCore
EditorStyle
UnrealEd
ToolMenus
AssetTools
Json
JsonUtilities
VFXAgentCore
VFXAgentNiagara
```

## CMake/VS Code Support

If using VS Code instead of Visual Studio:

1. Install "Unreal Engine" extension
2. Install "CMake Tools" extension
3. Copy `.vscode/settings.json` from another UE5 project or create:

```json
{
  "cmake.configureOnOpen": true,
  "unreal.engineSourcePath": "C:/Program Files/Epic Games/UE_5.5"
}
```

4. Use CMake build commands in VS Code palette

## Performance Optimization

For faster compilation during development:

1. **Use Incremental Compilation**
   - Only changed files recompile
   - Enabled by default in Visual Studio

2. **Disable Optimizations During Development**
   - Use Development configuration
   - Faster compile times

3. **Use Precompiled Headers**
   - All modules already use PCH
   - Further optimization: Minimal code changes

4. **Parallel Compilation**
   - Visual Studio: Tools → Options → Projects → VC++ Project Settings
   - Set "Enable parallel build" to number of CPU cores

## Creating Installable Package

To create a packaged plugin for distribution:

```powershell
cd "C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles"

.\RunUAT.bat BuildPlugin `
  -Plugin="E:\VFXAgent\VFXAgent\VFXAgent.uplugin" `
  -Package="E:\VFXAgent\VFXAgent_Packaged" `
  -TargetPlatforms=Win64+Mac+Linux `
  -CreateNew
```

Output: `E:\VFXAgent\VFXAgent_Packaged\`

## Debugging the Plugin

### Enable Debug Logging

In any `.cpp` file:
```cpp
UE_LOG(LogVFXAgent, Error, TEXT("Detailed error: %s"), *ErrorMessage);
```

Visible in: Output Log window

### Set Breakpoints in Visual Studio

1. Open `.cpp` file in Visual Studio
2. Click line number to set breakpoint
3. Press F5 to start debugging
4. Debug editor will attach when breakpoint hit

### Use Debug Console

In Output Log window:
- Filter for "LogVFXAgent" to see all plugin messages
- Filter for specific function names

## Cleanup and Troubleshooting

### Clean Build
```powershell
# Remove intermediate and binary files
Remove-Item E:\VFXAgent\VFXAgent\Binaries -Recurse -Force
Remove-Item E:\VFXAgent\VFXAgent\Intermediate -Recurse -Force

# Then rebuild
```

### Reset Plugin
1. Disable plugin in editor
2. Restart editor
3. Delete Binaries and Intermediate folders
4. Re-enable plugin
5. Rebuild

### Check Compilation Flags

Verify in `.Build.cs`:
```csharp
// Optional: Enable warnings as errors for better code quality
bTreatWarningsAsErrors = true;

// Optional: Use whole program optimization
bUseWhole ProgramOptimization = true;
```

## Final Verification Checklist

- [ ] All 23 source files present
- [ ] VFXAgent.uplugin updated with modules
- [ ] Visual Studio project generated
- [ ] Solution compiles without errors
- [ ] All 3 modules load in editor (check Output Log)
- [ ] VFX Agent menu appears in Window menu
- [ ] Panel opens and displays correctly
- [ ] Generate button works and creates Niagara system
- [ ] Logs display in Output Log window
- [ ] Asset created in correct Content path

## Support and Logs

For detailed build logs, set environment variable:
```powershell
$env:UE_BUILD_LOGGING = "1"
```

Then rebuild. Logs will include:
- Module dependency resolution
- Include file paths
- Compilation commands
- Linker output

---

**Guide Version**: 1.0  
**UE Version**: 5.5+  
**Last Updated**: 2026-01-25  
**Status**: Ready for Compilation