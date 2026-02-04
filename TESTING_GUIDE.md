# VFX Director 系统 - 测试和验证指南

## 快速测试

### 1. 生成Tornado特效

#### 方式A: 通过编辑器UI
1. 打开VFXAgent编辑器面板
2. 输入提示：`"Create a spinning tornado with particles"`
3. 点击"Generate"
4. 观察输出

**预期结果**：
- ✅ 3个emitter (CoreFunnel, Debris, Dust)
- ✅ 粒子向上运动，逐渐形成漏斗形
- ✅ 中心密集，向上开放
- ✅ 无下落的重力效果
- ✅ **不是**竖直喷发的爆炸

#### 方式B: 通过C++代码
```cpp
// 在某个生成函数中
FVFXRecipe TornadoRecipe;
TornadoRecipe.Intent.Archetype = EVFXArchetype::Tornado;
TornadoRecipe.Intent.Motion.PrimaryModel = EVFXMotionModel::Vortex;
TornadoRecipe.Intent.Motion.bCentripetal = true;
TornadoRecipe.Intent.Motion.bAngularVelocityIncreases = true;
TornadoRecipe.Intent.Motion.bHeightDriven = true;

TornadoRecipe.Intent.Avoidance.bAvoidConeVelocity = true;
TornadoRecipe.Intent.Avoidance.bAvoidRadialExplosion = true;
TornadoRecipe.Intent.Avoidance.bAvoidUniformGravity = true;

TArray<FString> Warnings;
FVFXRecipe Validated = UVFXRecipeCompiler::ValidateAndSanitize(TornadoRecipe, Warnings);

// 检查生成的层
UE_LOG(LogVFXAgent, Log, TEXT("Generated layers: %d"), Validated.Layers.Num());
for (const FVFXLayerRecipe& Layer : Validated.Layers)
{
    UE_LOG(LogVFXAgent, Log, TEXT("  Layer: %s"), *Layer.Name);
}
```

### 2. 验证Intent应用

#### 检查点1: Warnings日志
```cpp
TArray<FString> Warnings;
UVFXRecipeCompiler::ValidateAndSanitize(Recipe, Warnings);

// 应该看到这些日志：
// [TORNADO] Enforcing vortex motion + centripetal rules
// [TORNADO] Generating default 3-layer structure: core_funnel, debris, dust
// [TORNADO] Layer 'CoreFunnel': Reducing outward cone velocity
// [TORNADO] Layer 'CoreFunnel': Applying height-driven vortex behavior
```

#### 检查点2: 生成的参数
```cpp
FVFXRecipe Recipe; 
Recipe.Intent.Archetype = EVFXArchetype::Tornado;

TArray<FString> Warnings;
FVFXRecipe Validated = UVFXRecipeCompiler::ValidateAndSanitize(Recipe, Warnings);

// 验证生成的层
EXPECT_EQ(Validated.Layers.Num(), 3);
EXPECT_EQ(Validated.Layers[0].Name, TEXT("CoreFunnel"));
EXPECT_EQ(Validated.Layers[1].Name, TEXT("Debris"));
EXPECT_EQ(Validated.Layers[2].Name, TEXT("Dust"));

// 验证参数
EXPECT_EQ(Validated.Layers[0].Spawn.Rate, 40.0f);
EXPECT_EQ(Validated.Layers[1].Spawn.Rate, 20.0f);
EXPECT_EQ(Validated.Layers[2].Spawn.Rate, 60.0f);

// 验证向上运动
EXPECT_GT(Validated.Layers[0].InitialVelocity.Z, 0.0f);
EXPECT_GT(Validated.Layers[1].InitialVelocity.Z, 0.0f);
EXPECT_GT(Validated.Layers[2].InitialVelocity.Z, 0.0f);
```

### 3. 对比不同Archetype

#### Tornado vs Explosion
```cpp
// Tornado
FVFXRecipe Tornado;
Tornado.Intent.Archetype = EVFXArchetype::Tornado;
Tornado.Intent.Avoidance.bAvoidConeVelocity = true;
Tornado.Intent.Avoidance.bAvoidUniformGravity = true;

// Explosion
FVFXRecipe Explosion;
Explosion.Intent.Archetype = EVFXArchetype::Explosion;
Explosion.Intent.Avoidance.bAvoidConeVelocity = false;
Explosion.Intent.Avoidance.bAvoidUniformGravity = false;

// 编译两个
TArray<FString> TornadoWarnings, ExplosionWarnings;
FVFXRecipe ValidatedTornado = UVFXRecipeCompiler::ValidateAndSanitize(Tornado, TornadoWarnings);
FVFXRecipe ValidatedExplosion = UVFXRecipeCompiler::ValidateAndSanitize(Explosion, ExplosionWarnings);

// 生成Niagara系统
UNiagaraSystem* TornadoSystem = ...;
UNiagaraSystem* ExplosionSystem = ...;

// 对比视觉
// Tornado: 聚集，向上，漏斗形
// Explosion: 分散，向外+向下，球形
```

---

## 深度测试

### 测试1: Intent强制规则

**目标**：验证`ApplyArchetypeRules()`是否正确修改参数

```cpp
void TestTornadoRuleEnforcement()
{
    FVFXRecipe Recipe;
    Recipe.Intent.Archetype = EVFXArchetype::Tornado;
    Recipe.Intent.Avoidance.bAvoidConeVelocity = true;
    Recipe.Intent.Avoidance.bAvoidUniformGravity = true;
    
    // 添加错误的参数（模拟LLM错误输出）
    FVFXLayerRecipe BadLayer;
    BadLayer.Name = TEXT("BadLayer");
    BadLayer.InitialVelocity = FVector(100, 100, 0);  // 向外！
    BadLayer.Forces.Add(FVFXForceRecipe{EVFXForceType::Gravity, 1.0f});
    Recipe.Layers.Add(BadLayer);
    
    // 验证&修正
    TArray<FString> Warnings;
    FVFXRecipe Fixed = UVFXRecipeCompiler::ValidateAndSanitize(Recipe, Warnings);
    
    // 检查：向外速度应被减弱
    float OriginalMagnitude = FVector(100, 100, 0).Length();
    float FixedMagnitude = Fixed.Layers[0].InitialVelocity.Length();
    EXPECT_LT(FixedMagnitude, OriginalMagnitude);
    
    // 检查：重力应被减弱
    auto GravityForce = Fixed.Layers[0].Forces.FindByPredicate(
        [](const FVFXForceRecipe& F) { return F.Type == EVFXForceType::Gravity; }
    );
    EXPECT_LT(GravityForce->Strength, 1.0f);
    
    // 检查：应输出警告日志
    bool bHasTornadoWarning = Warnings.ContainsByPredicate(
        [](const FString& W) { return W.Contains(TEXT("[TORNADO]")); }
    );
    EXPECT_TRUE(bHasTornadoWarning);
}
```

### 测试2: 3层自动生成

**目标**：验证Tornado的3层自动生成机制

```cpp
void TestTornadoAutoLayerGeneration()
{
    FVFXRecipe Recipe;
    Recipe.Intent.Archetype = EVFXArchetype::Tornado;
    
    // 初始无层
    EXPECT_EQ(Recipe.Layers.Num(), 0);
    
    // 验证&生成
    TArray<FString> Warnings;
    FVFXRecipe Generated = UVFXRecipeCompiler::ValidateAndSanitize(Recipe, Warnings);
    
    // 检查：应生成3层
    EXPECT_EQ(Generated.Layers.Num(), 3);
    
    // 检查：层的名称和角色
    EXPECT_EQ(Generated.Layers[0].Name, TEXT("CoreFunnel"));
    EXPECT_EQ(Generated.Layers[0].Role, TEXT("core_funnel"));
    
    EXPECT_EQ(Generated.Layers[1].Name, TEXT("Debris"));
    EXPECT_EQ(Generated.Layers[1].Role, TEXT("debris"));
    
    EXPECT_EQ(Generated.Layers[2].Name, TEXT("Dust"));
    EXPECT_EQ(Generated.Layers[2].Role, TEXT("dust"));
    
    // 检查：参数符合默认值
    EXPECT_EQ(Generated.Layers[0].Spawn.Rate, 40.0f);
    EXPECT_EQ(Generated.Layers[1].Spawn.Rate, 20.0f);
    EXPECT_EQ(Generated.Layers[2].Spawn.Rate, 60.0f);
    
    // 检查：向上运动
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_GT(Generated.Layers[i].InitialVelocity.Z, 0.0f);
    }
}
```

### 测试3: JSON解析

**目标**：验证从JSON正确解析Intent

```cpp
void TestIntentJsonParsing()
{
    const FString JsonStr = TEXT(R"(
    {
        "intent": {
            "archetype": "Tornado",
            "motion": {
                "primaryModel": "Vortex",
                "motionAxis": {"x": 0, "y": 0, "z": 1},
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
        },
        "emitters": []
    }
    )");
    
    // 解析JSON
    FVFXRecipe ParsedRecipe;
    FString Error;
    bool bSuccess = UHttpLLMProvider::TryParseRecipeJson(JsonStr, ParsedRecipe, Error);
    
    // 验证解析
    EXPECT_TRUE(bSuccess);
    EXPECT_EQ(ParsedRecipe.Intent.Archetype, EVFXArchetype::Tornado);
    EXPECT_EQ(ParsedRecipe.Intent.Motion.PrimaryModel, EVFXMotionModel::Vortex);
    EXPECT_TRUE(ParsedRecipe.Intent.Motion.bCentripetal);
    EXPECT_TRUE(ParsedRecipe.Intent.Motion.bAngularVelocityIncreases);
    EXPECT_TRUE(ParsedRecipe.Intent.Avoidance.bAvoidConeVelocity);
}
```

---

## 性能测试

### 测试4: 编译性能

**目标**：验证Intent应用和3层生成的性能开销

```cpp
void TestCompilePerformance()
{
    FVFXRecipe Recipe;
    Recipe.Intent.Archetype = EVFXArchetype::Tornado;
    
    // 时间测量
    double StartTime = FPlatformTime::Seconds();
    
    TArray<FString> Warnings;
    for (int i = 0; i < 1000; ++i)
    {
        FVFXRecipe Temp = Recipe;
        UVFXRecipeCompiler::ValidateAndSanitize(Temp, Warnings);
    }
    
    double ElapsedTime = FPlatformTime::Seconds() - StartTime;
    
    // 应该很快（< 100ms for 1000 iterations）
    UE_LOG(LogVFXAgent, Log, TEXT("1000 compilations took %.2f ms"), ElapsedTime * 1000.0);
    EXPECT_LT(ElapsedTime, 0.1);  // < 100ms
}
```

---

## 可视化验证

### 在编辑器中验证效果

#### Step 1: 生成系统
```
1. 打开VFXAgent编辑器面板
2. 输入："Create a spinning tornado with dark particles"
3. 点击 Generate
4. 等待系统生成
```

#### Step 2: 检查输出
在日志中搜索 `[TORNADO]`：
```
[TORNADO] Enforcing vortex motion + centripetal rules
[TORNADO] Generating default 3-layer structure: core_funnel, debris, dust
[TORNADO] Layer 'CoreFunnel': Reducing outward cone velocity
[TORNADO] Layer 'CoreFunnel': Applying height-driven vortex behavior
[TORNADO] Layer 'Debris': Reducing outward cone velocity
...
```

#### Step 3: 检查Niagara编辑器
1. 打开生成的Niagara系统
2. 查看Emitter列表：应有3个（CoreFunnel, Debris, Dust）
3. 每个Emitter的属性：
   - **CoreFunnel**: 小号，向上，高更新率
   - **Debris**: 中号，向上，中等更新率
   - **Dust**: 大号，向上，高扩散

#### Step 4: 播放预览
- 按空格播放
- 观察粒子行为：
  - ✅ 向上（不是向外）
  - ✅ 中心密集，向上开放
  - ✅ 逐渐形成漏斗形
  - ✅ **不是**爆炸或喷泉

---

## 对比测试

### Tornado vs Explosion vs Fire

```cpp
void TestArchetypeComparison()
{
    // 创建三个相同输入，不同archetype
    FVFXRecipe BaseRecipe;
    BaseRecipe.Bounds = FVector(100, 100, 100);
    BaseRecipe.Duration = 5.0f;
    
    // Tornado
    FVFXRecipe TornadoRecipe = BaseRecipe;
    TornadoRecipe.Intent.Archetype = EVFXArchetype::Tornado;
    TornadoRecipe.Intent.Motion.PrimaryModel = EVFXMotionModel::Vortex;
    TornadoRecipe.Intent.Avoidance.bAvoidConeVelocity = true;
    TornadoRecipe.Intent.Avoidance.bAvoidUniformGravity = true;
    
    // Explosion
    FVFXRecipe ExplosionRecipe = BaseRecipe;
    ExplosionRecipe.Intent.Archetype = EVFXArchetype::Explosion;
    ExplosionRecipe.Intent.Motion.PrimaryModel = EVFXMotionModel::Radial;
    ExplosionRecipe.Intent.Avoidance.bAvoidConeVelocity = false;
    ExplosionRecipe.Intent.Avoidance.bAvoidUniformGravity = false;
    
    // Fire
    FVFXRecipe FireRecipe = BaseRecipe;
    FireRecipe.Intent.Archetype = EVFXArchetype::Fire;
    FireRecipe.Intent.Motion.PrimaryModel = EVFXMotionModel::Vertical;
    FireRecipe.Intent.Avoidance.bAvoidUniformGravity = true;
    
    // 编译所有
    TArray<FString> Warnings;
    auto TornadoValidated = UVFXRecipeCompiler::ValidateAndSanitize(TornadoRecipe, Warnings);
    auto ExplosionValidated = UVFXRecipeCompiler::ValidateAndSanitize(ExplosionRecipe, Warnings);
    auto FireValidated = UVFXRecipeCompiler::ValidateAndSanitize(FireRecipe, Warnings);
    
    // 验证结构
    EXPECT_EQ(TornadoValidated.Layers.Num(), 3);     // 龙卷风：3层
    EXPECT_EQ(ExplosionValidated.Layers.Num(), 1);   // 爆炸：1-2层
    EXPECT_GE(FireValidated.Layers.Num(), 1);        // 火焰：灵活
    
    // 生成Niagara并播放
    // 观察三个效果的视觉差异
}
```

---

## 调试技巧

### 1. 启用详细日志
```cpp
// 在 VFXAgentLog.h 中
#define UE_VFXLOG_INTENT 1  // 启用Intent相关日志
```

### 2. 打印Intent信息
```cpp
void PrintIntent(const FVFXIntent& Intent)
{
    UE_LOG(LogVFXAgent, Log, TEXT("Intent:"));
    UE_LOG(LogVFXAgent, Log, TEXT("  Archetype: %d"), (int32)Intent.Archetype);
    UE_LOG(LogVFXAgent, Log, TEXT("  Motion Model: %d"), (int32)Intent.Motion.PrimaryModel);
    UE_LOG(LogVFXAgent, Log, TEXT("  Centripetal: %s"), Intent.Motion.bCentripetal ? TEXT("true") : TEXT("false"));
    UE_LOG(LogVFXAgent, Log, TEXT("  AvoidCone: %s"), Intent.Avoidance.bAvoidConeVelocity ? TEXT("true") : TEXT("false"));
    UE_LOG(LogVFXAgent, Log, TEXT("  RequiredLayers: %d"), Intent.RequiredLayers.Num());
    for (const FString& Layer : Intent.RequiredLayers)
    {
        UE_LOG(LogVFXAgent, Log, TEXT("    - %s"), *Layer);
    }
}
```

### 3. 对比修改前后
```cpp
void DebugRecipeModification(const FVFXRecipe& Before, const FVFXRecipe& After)
{
    UE_LOG(LogVFXAgent, Log, TEXT("Recipe Changes:"));
    UE_LOG(LogVFXAgent, Log, TEXT("  Layers: %d → %d"), Before.Layers.Num(), After.Layers.Num());
    
    for (int i = 0; i < FMath::Max(Before.Layers.Num(), After.Layers.Num()); ++i)
    {
        if (i < Before.Layers.Num() && i < After.Layers.Num())
        {
            const FVFXLayerRecipe& B = Before.Layers[i];
            const FVFXLayerRecipe& A = After.Layers[i];
            
            if (!B.InitialVelocity.Equals(A.InitialVelocity))
            {
                UE_LOG(LogVFXAgent, Log, TEXT("    Layer %d Velocity: (%f,%f,%f) → (%f,%f,%f)"),
                    i, B.InitialVelocity.X, B.InitialVelocity.Y, B.InitialVelocity.Z,
                    A.InitialVelocity.X, A.InitialVelocity.Y, A.InitialVelocity.Z);
            }
        }
    }
}
```

---

## 检查清单

### 编译和基础功能
- [ ] 代码编译无错误
- [ ] 包含头文件正确
- [ ] 枚举值正确定义
- [ ] 结构体字段完整

### Intent功能
- [ ] 可以手动设置Intent
- [ ] Intent从JSON正确解析
- [ ] Archetype值正确映射
- [ ] Motion参数正确传递

### Archetype规则
- [ ] Tornado规则被正确应用
- [ ] Explosion规则被正确应用
- [ ] Fire规则被正确应用
- [ ] Custom不应用任何规则

### 3层生成
- [ ] 检测到Tornado时自动生成3层
- [ ] 层的名称、角色、参数正确
- [ ] 向上初速度正确（100, 80, 50）
- [ ] 生成速率正确（40, 20, 60）

### 日志和调试
- [ ] Warnings包含[TORNADO]标记
- [ ] 应用的规则都有日志
- [ ] 错误信息清晰

---

## 总结

✅ **核心测试**
- Intent设置和解析
- Archetype规则应用
- 3层自动生成
- 与旧系统对比

✅ **验证点**
- 编译无错误
- 日志信息完整
- 生成参数符合预期
- 视觉效果符合archetype

✅ **性能**
- 编译速度快
- 无额外开销

