# VFX Director Layer - 实现指南

## 📋 目录
1. [系统概览](#系统概览)
2. [Tornado特效修复](#tornado特效修复)
3. [使用VFX Intent](#使用vfx-intent)
4. [Archetype规则](#archetype规则)
5. [RecipeCompiler工作流](#recipecompiler工作流)
6. [调试和优化](#调试和优化)

---

## 系统概览

### 新增核心概念

#### 1. **FVFXIntent** - VFX导演的语义理解
```cpp
USTRUCT(BlueprintType)
struct FVFXIntent
{
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
    EVFXArchetype Archetype;  // Tornado, Explosion, Fire, etc.
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
    FVFXMotionBehavior Motion;  // 运动模型
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
    FVFXVisualHierarchy Hierarchy;  // 视觉层级
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
    FVFXPatternAvoidance Avoidance;  // 禁止模式
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
    TArray<FString> RequiredLayers;  // 所需层数
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Intent")
    TArray<FString> RequiredForces;  // 所需力类型
};
```

#### 2. **FVFXMotionBehavior** - 运动定义
```cpp
USTRUCT(BlueprintType)
struct FVFXMotionBehavior
{
    // 主运动模型（Radial, Vortex, Orbit, 等）
    EVFXMotionModel PrimaryModel;
    
    // 轴线（用于Orbit/Vortex）
    FVector MotionAxis;
    
    // 高度相关行为
    bool bRadiusDependsOnHeight;        // 漏斗效应
    bool bAngularVelocityIncreases;     // 速度随高度增加
    bool bHeightDriven;                 // 高度驱动参数
    
    // 向心运动
    bool bCentripetal;                  // 向中心吸引
    float CentripetalStrength;
};
```

#### 3. **FVFXPatternAvoidance** - 禁止列表
```cpp
USTRUCT(BlueprintType)
struct FVFXPatternAvoidance
{
    // 禁止模式标志
    bool bAvoidConeVelocity;            // 避免 AddVelocity in Cone
    bool bAvoidRadialExplosion;         // 避免 向外放射结构
    bool bAvoidUniformGravity;          // 避免 均匀向下重力
    bool bAvoidUniformRotation;         // 避免 简单旋转
    bool bAvoidHighSpread;              // 避免 粒子分散
};
```

---

## Tornado特效修复

### 问题诊断

原始龙卷风的问题：
```
❌ Shape: Sphere
❌ AddVelocity: In Cone (outward) 
❌ Gravity: -980
结果：竖直喷发 → 看起来像爆炸，不是龙卷风
```

**根本原因**：没有区分"爆炸"和"龙卷风"的物理结构。

### 解决方案

#### Step 1: AI生成Intent（两阶段提示）
系统提示词中包含：
```
TORNADO:
  - Motion: VORTEX rotating around vertical axis
  - MUST: bCentripetal=true, bAngularVelocityIncreases=true
  - MUST AVOID: Radial outward velocity, cone spray, uniform gravity
  - Layers: 3 minimum (core_funnel, debris, dust)
  - Forces: Vortex, Centripetal attraction, Vertical lift
```

**LLM输出的Intent**：
```json
{
  "intent": {
    "archetype": "Tornado",
    "motion": {
      "primaryModel": "Vortex",
      "motionAxis": [0, 0, 1],
      "bAngularVelocityIncreases": true,
      "bCentripetal": true,
      "bHeightDriven": true
    },
    "avoidance": {
      "bAvoidConeVelocity": true,
      "bAvoidRadialExplosion": true,
      "bAvoidUniformGravity": true
    },
    "requiredLayers": ["core_funnel", "debris", "dust"],
    "requiredForces": ["vortex", "centripetal", "lift"]
  }
}
```

#### Step 2: RecipeCompiler强制规则

在`VFXRecipeCompiler::ValidateAndSanitize()`中：

```cpp
// 步骤1：应用archetype特定规则
if (Result.Intent.Archetype == EVFXArchetype::Tornado)
{
    ApplyArchetypeRules(Result.Intent, Result, OutWarnings);
}

// 步骤2：生成默认3层结构
if (Result.Intent.Archetype == EVFXArchetype::Tornado && 
    Result.Layers.Num() < 3)
{
    Result.Layers.Empty();  // 清空现有层
    
    // 自动生成3层
    FVFXLayerRecipe CoreLayer;
    CoreLayer.Name = "CoreFunnel";
    CoreLayer.InitialVelocity = FVector(0, 0, 100);  // 向上！
    CoreLayer.Spawn.Rate = 40.0f;
    Result.Layers.Add(CoreLayer);
    
    // ... Debris, Dust 层
}
```

`ApplyArchetypeRules()`函数的作用：

```cpp
static void ApplyArchetypeRules(const FVFXIntent& Intent, 
                                FVFXRecipe& Recipe, 
                                TArray<FString>& OutWarnings)
{
    if (Intent.Archetype == EVFXArchetype::Tornado)
    {
        for (FVFXLayerRecipe& Layer : Recipe.Layers)
        {
            // 禁止向外的圆锥速度
            if (Intent.Avoidance.bAvoidConeVelocity && 
                !Layer.InitialVelocity.IsNearlyZero())
            {
                Layer.InitialVelocity *= 0.3f;  // 大幅减弱
            }
            
            // 禁止向下重力
            if (Intent.Avoidance.bAvoidUniformGravity)
            {
                for (FVFXForceRecipe& Force : Layer.Forces)
                {
                    if (Force.Type == EVFXForceType::Gravity)
                    {
                        Force.Strength *= 0.1f;
                    }
                }
            }
        }
    }
}
```

#### Step 3: 结果
- **3个emitter**：CoreFunnel(40/s), Debris(20/s), Dust(60/s)
- **运动**：纯向上(0, 0, 100)，无向外扩散
- **力**：无强重力下拉
- **视觉**：分层，密集中心，开放顶部 → **看起来像龙卷风**

---

## 使用VFX Intent

### 在Code中手动设置Intent

```cpp
FVFXRecipe Recipe;

// 设置Intent
Recipe.Intent.Archetype = EVFXArchetype::Tornado;
Recipe.Intent.Motion.PrimaryModel = EVFXMotionModel::Vortex;
Recipe.Intent.Motion.MotionAxis = FVector(0, 0, 1);
Recipe.Intent.Motion.bCentripetal = true;
Recipe.Intent.Motion.bAngularVelocityIncreases = true;
Recipe.Intent.Motion.bHeightDriven = true;

Recipe.Intent.Avoidance.bAvoidConeVelocity = true;
Recipe.Intent.Avoidance.bAvoidRadialExplosion = true;
Recipe.Intent.Avoidance.bAvoidUniformGravity = true;

Recipe.Intent.RequiredLayers = {"core_funnel", "debris", "dust"};
Recipe.Intent.RequiredForces = {"vortex", "centripetal", "lift"};

Recipe.Intent.Description = "A spinning tornado with swirling particles";

// 编译
TArray<FString> Warnings;
FVFXRecipe Validated = UVFXRecipeCompiler::ValidateAndSanitize(Recipe, Warnings);
// 现在 Validated 会有3个自动生成的层！
```

### 从JSON解析Intent

在`HttpLLMProvider::TryParseRecipeJson()`中，系统自动解析：

```json
{
  "intent": {
    "archetype": "Tornado",
    "motion": {
      "primaryModel": "Vortex",
      "motionAxis": {"x": 0, "y": 0, "z": 1},
      "bAngularVelocityIncreases": true,
      "bCentripetal": true
    },
    "avoidance": {
      "bAvoidConeVelocity": true,
      "bAvoidRadialExplosion": true,
      "bAvoidUniformGravity": true
    },
    "requiredLayers": ["core_funnel", "debris", "dust"],
    "requiredForces": ["vortex", "centripetal", "lift"]
  },
  "emitters": [...]
}
```

`FJsonObjectConverter::JsonObjectStringToUStruct()` 会自动填充 `FVFXRecipe.Intent`。

---

## Archetype规则

### Tornado
```cpp
Archetype: Tornado
Motion: Vortex (旋转上升)
Axis: Z (竖直)

应用规则：
- 减弱向外的InitialVelocity（✖ 不要Cone）
- 禁用或减弱重力（✖ 不要向下）
- 生成3层结构
- 应用高度驱动参数

生成的默认参数：
  Layer1 (CoreFunnel):
    SpawnRate: 40/sec
    Lifetime: 3s
    Size: 30
    InitialVelocity: (0, 0, 100)
    EmitShape: Cylinder
    
  Layer2 (Debris):
    SpawnRate: 20/sec
    Lifetime: 4s
    Size: 50
    InitialVelocity: (0, 0, 80)
    EmitShape: Sphere
    
  Layer3 (Dust):
    SpawnRate: 60/sec
    Lifetime: 5s
    Size: 15
    InitialVelocity: (0, 0, 50)
    EmitShape: Sphere
```

### Explosion
```cpp
Archetype: Explosion
Motion: Radial (向外放射)

应用规则：
- 保留向外的Cone velocity（✓ 允许）
- 启用重力（✓ 允许）
- 2-4层结构

特点：
- AddVelocity in Cone：正常强度
- Gravity：启用 (-980)
- 快速生命周期
```

### Fire
```cpp
Archetype: Fire
Motion: Vertical (向上)

应用规则：
- 强制向上速度（Z > 50）
- 减弱重力（Gravity × 0.2）
- 3层：core flame, embers, smoke

特点：
- 颜色梯度：orange → red → black
- 向上加速度
- 无重力下拉
```

### Aura / Magic
```cpp
Archetype: Aura
Motion: Orbit (轨道/悬浮)

应用规则：
- 禁用重力
- 禁用Cone velocity
- 圆周或漂浮运动
- 无边界扩散

特点：
- 静止或轻微轨道
- 聚集在中心
```

---

## RecipeCompiler工作流

### 调用流程

```
User Input (Natural Language)
    ↓
HttpLLMProvider::RequestRecipeJsonAsync()
    ↓
LLM生成 (包含Intent + Emitters)
    ↓
HttpLLMProvider::TryParseRecipeJson()
    ↓ FJsonObjectConverter 自动填充 FVFXRecipe.Intent
FVFXRecipe (with Intent)
    ↓
UVFXRecipeCompiler::ValidateAndSanitize()
    ├─→ ApplyArchetypeRules()  ← 关键！
    ├─→ 生成默认3层（如果是Tornado）
    └─→ 归一化参数
    ↓
FVFXRecipe (validated + rules applied)
    ↓
UVFXRecipeCompiler::CompileToSpec()
    ↓
FVFXEffectSpec
    ↓
FSystemAssembler::Assemble()
    ↓
UNiagaraSystem
```

### 关键点

1. **Intent是可选的** - 如果没有Intent，使用Custom archetype
2. **Archetype规则强制应用** - 即使用户的参数错误，系统也会修正
3. **默认结构覆盖** - Tornado的3层自动生成覆盖已有的emitters
4. **日志记录** - 所有应用的规则都会添加到Warnings

---

## 调试和优化

### 查看应用的规则

在`ValidateAndSanitize()`执行后，检查`OutWarnings`：

```cpp
TArray<FString> Warnings;
FVFXRecipe Validated = UVFXRecipeCompiler::ValidateAndSanitize(Recipe, Warnings);

for (const FString& Warning : Warnings)
{
    UE_LOG(LogVFXAgent, Warning, TEXT("%s"), *Warning);
}

// 输出示例：
// [TORNADO] Enforcing vortex motion + centripetal rules
// [TORNADO] Generating default 3-layer structure
// [TORNADO] Layer 'CoreFunnel': Applying height-driven vortex behavior
// [TORNADO] Recipe has only 1 layer(s); suggest 3: core_funnel, debris, dust
```

### 检查生成的层

```cpp
FVFXRecipe Recipe = ...;
UVFXRecipeCompiler::ValidateAndSanitize(Recipe, Warnings);

UE_LOG(LogVFXAgent, Log, TEXT("Generated %d layers:"), Recipe.Layers.Num());
for (const FVFXLayerRecipe& Layer : Recipe.Layers)
{
    UE_LOG(LogVFXAgent, Log, TEXT("  - %s (%s): %d/sec, life=%.1fs, size=%.0f"),
        *Layer.Name, *Layer.Role, 
        (int32)Layer.Spawn.Rate, Layer.Lifetime, Layer.Size);
}
```

### 优化Tornado参数

如果生成的龙卷风不够好，可以在LLM生成之后微调，但要保持archetype的核心：

```cpp
// ❌ 不要改这些（会被ApplyArchetypeRules覆盖）
// Recipe.Layers[0].InitialVelocity = FVector(100, 100, 0);  // 向外

// ✓ 可以改这些
Recipe.Layers[0].Size = 25.0f;  // 调整粒子大小
Recipe.Layers[0].Spawn.Rate = 50.0f;  // 调整生成速率
Recipe.Layers[0].Lifetime = 3.5f;  // 调整生命周期
Recipe.Layers[0].Color = FLinearColor(0.2f, 0.2f, 0.3f);  // 调整颜色
```

### 添加自定义Archetype规则

如果想添加新的archetype规则，编辑`ApplyArchetypeRules()`：

```cpp
static void ApplyArchetypeRules(const FVFXIntent& Intent, 
                                FVFXRecipe& Recipe, 
                                TArray<FString>& OutWarnings)
{
    // ... 现有规则 ...
    
    // 新增：自定义特效
    if (Intent.Archetype == EVFXArchetype::Custom)
    {
        // 不应用自动规则，允许完全自定义
        return;
    }
}
```

---

## 常见问题

### Q1: 为什么要2阶段（Intent + Recipe）？
**A**: 因为AI容易混淆"概念"和"实现"。Intent阶段让AI输出"我认为这是什么特效"，Recipe阶段是"生成参数"。系统在两阶段之间强制规则。

### Q2: 如果LLM生成的Intent错误怎么办？
**A**: 系统仍然会应用规则。如果LLM说"archetype=Tornado"但给了爆炸参数，`ApplyArchetypeRules()`会修正。缺点是依赖LLM的首次判断正确。

**改进**：可以添加一个Intent验证器，在应用规则前检查一致性。

### Q3: 3层的Tornado参数是硬编码的吗？
**A**: 是的，在`ValidateAndSanitize()`中硬编码。这保证一致性。但可以在生成后修改参数，系统会保留修改。

**改进**：可以从配置文件或参数表中读取默认值。

### Q4: 如何扩展到其他特效类型？
**A**:
1. 在`EVFXArchetype`中添加新枚举值
2. 在`ApplyArchetypeRules()`中添加`if`分支
3. 在系统提示词中添加该archetype的说明

例子：添加"Vortex"（漩涡，类似Tornado但平面）
```cpp
if (Intent.Archetype == EVFXArchetype::Vortex)
{
    // 类似Tornado，但轴是水平的
    for (FVFXLayerRecipe& Layer : Recipe.Layers)
    {
        Layer.InitialVelocity = FVector(100, 0, 0);  // 水平向外
        // ...
    }
}
```

---

## 总结

✅ **实现了什么**
- VFX Intent结构（Archetype + Motion + Avoidance）
- 两阶段LLM提示（Intent → Recipe）
- Archetype特定规则强制
- Tornado默认3层自动生成
- 详细的日志记录

✅ **解决的问题**
- 龙卷风看起来像爆炸
- AI不理解特效类型的物理差异
- 无法强制特定的视觉结构

✅ **后续改进方向**
- 时间驱动的参数曲线
- 多archetype预设库
- 实时Intent验证
- 可视化调试工具

