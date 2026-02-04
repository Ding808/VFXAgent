# VFX Director Layer - Semantic-First Architecture

## 核心问题与解决方案

### 原问题：盲目堆模块
之前的流程是：
```
自然语言 → LLM → 直接生成Niagara节点组合
```

结果：AI不知道什么是"龙卷风"，只会随机组合`Gravity + Cone Velocity + Drag`，这必然产生爆炸效果而不是旋转效果。

### 新解决方案：导演层 (Director Layer)
```
自然语言 
  ↓
[1] 语义理解（导演脑）- 输出VFX Intent JSON
  - 这是什么类型的特效？(Tornado/Explosion/Fire/etc)
  - 需要什么物理模型？(Vortex/Radial/Vertical/etc)
  - 什么行为绝对不能出现？(Avoidance patterns)
  - 需要几层结构？
  ↓
[2] Recipe编译 - 根据Intent生成Niagara参数
  - 强制archetype-specific规则
  - 禁用不适用的patterns
  - 应用默认结构
  ↓
[3] Niagara系统构建
```

---

## VFX Intent 结构

### Archetype（特效原型）
定义了特效的基本类型：
- `Tornado` - 旋转，内向吸引，高度相关行为
- `Explosion` - 放射状向外，重力
- `Fire` - 向上，无强重力，颜色梯度
- `Aura` - 轨道/漂浮，无重力
- `Trail` - 跟踪路径
- `Beam` - 射线
- `Dust` - 飘散
- `Smoke` - 烟雾
- 等等

### MotionModel（运动模型）
定义粒子如何移动：
- `Radial` - 向外放射（爆炸）
- `RadialInward` - 向内吸引（漩涡）
- `Orbit` - 圆周运动（轨道）
- `Vortex` - 旋转上升（龙卷风）
- `Directional` - 单向（射线/束）
- `Vertical` - 垂直（上/下）
- `Turbulent` - 混乱（噪声驱动）
- `Static` - 静止（悬浮）

### MotionBehavior（运动行为）
```cpp
struct FVFXMotionBehavior
{
    EVFXMotionModel PrimaryModel;      // 主运动模型
    FVector MotionAxis;                 // 轴线（用于Orbit/Vortex）
    bool bRadiusDependsOnHeight;        // 漏斗效应
    bool bAngularVelocityIncreases;     // 速度随高度增加
    bool bCentripetal;                  // 向中心吸引
    float CentripetalStrength;
    bool bHeightDriven;                 // 高度相关参数
};
```

### PatternAvoidance（模式禁止）
这是关键！明确告诉系统哪些Niagara模式对这个特效是**完全错误的**：

```cpp
struct FVFXPatternAvoidance
{
    bool bAvoidConeVelocity;            // 不要"AddVelocity in Cone"
    bool bAvoidRadialExplosion;         // 不要"向外放射"结构
    bool bAvoidUniformGravity;          // 不要"均匀向下重力"
    bool bAvoidUniformRotation;         // 不要"简单旋转"
    bool bAvoidHighSpread;              // 保持集中，不要分散
};
```

---

## Tornado 特效的正确方式

### ❌ 错误的龙卷风（现在的输出）
```
Emitter:
  Shape: Sphere (or Point)
  AddVelocity: In Cone (outward)   ← 这是问题！
  Gravity: -980                    ← 这也是问题！
  Drag: 0.5
结果：竖直上抛的点云，不是旋转
```

### ✅ 正确的龙卷风（新系统输出）

#### Step 1: AI理解阶段
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
      "bAvoidConeVelocity": true,      // 禁用Cone
      "bAvoidRadialExplosion": true,   // 禁用向外
      "bAvoidUniformGravity": true     // 禁用重力
    },
    "requiredLayers": ["core_funnel", "debris", "dust"],
    "requiredForces": ["vortex", "centripetal", "lift"],
    "suggestedEmitterCount": 3
  }
}
```

#### Step 2: Recipe编译
RecipeCompiler读到`Archetype == Tornado`后：
1. **禁用** `bAvoidConeVelocity` - 避免AddVelocity in Cone
2. **强制** 3层结构
3. **应用** `ApplyArchetypeRules(Tornado)` 函数

```cpp
// VFXRecipeCompiler.cpp 中的规则
if (Intent.Archetype == EVFXArchetype::Tornado)
{
    // 减弱向外的圆锥速度
    for (auto& Layer : Recipe.Layers)
    {
        if (!Layer.InitialVelocity.IsNearlyZero())
        {
            Layer.InitialVelocity *= 0.3f;  // 减弱！
        }
        // 应用高度驱动的参数
        ApplyHeightDrivenBehavior(Layer);
    }
}
```

#### Step 3: 默认结构（自动生成3层）
```cpp
// 层1: 核心漏斗（主要视觉）
CoreFunnel:
  Name: "CoreFunnel"
  SpawnRate: 40/sec
  Lifetime: 3s
  Size: 30
  Color: Gray-blue
  InitialVelocity: (0, 0, 100)  // 向上，不向外！
  Shape: Cylinder (150x150x500)
  
// 层2: 碎片（中层）
Debris:
  SpawnRate: 20/sec
  Lifetime: 4s
  Size: 50
  Color: Brown
  InitialVelocity: (0, 0, 80)
  Shape: Sphere (100 radius)
  
// 层3: 尘埃（外围）
Dust:
  SpawnRate: 60/sec
  Lifetime: 5s
  Size: 15
  Color: Light gray
  InitialVelocity: (0, 0, 50)
  Shape: Sphere (200x200x100)
```

#### Step 4: 结果
- 3个emitter各自独立，产生分层视觉
- 向上运动，**没有**向外的圆锥喷发
- 向上加速不同（内层100，中层80，外层50）→ 自然漏斗形
- 无重力干扰 → 纯粹的上升运动

---

## 系统中的其他Archetype

### Explosion
```json
"motion": {
  "primaryModel": "Radial",
  "bAngularVelocityIncreases": false
},
"avoidance": {
  "bAvoidConeVelocity": false,      // 允许Cone！
  "bAvoidRadialExplosion": false,
  "bAvoidUniformGravity": false     // 允许重力
}
```
→ 使用AddVelocity in Cone，加重力

### Fire
```json
"motion": {
  "primaryModel": "Vertical"
},
"avoidance": {
  "bAvoidUniformGravity": true      // 禁用强重力
}
```
→ 向上，无下拉

### Aura/Magic
```json
"motion": {
  "primaryModel": "Orbit"
},
"avoidance": {
  "bAvoidUniformGravity": true,
  "bAvoidConeVelocity": true
}
```
→ 轨道运动，无重力、无扩散

---

## 对提示词工程的影响

### 旧的（无效的）提示
```
"Make a more realistic tornado"
"Make it spin faster"
"Make it look less like an explosion"
```
这些对AI无意义，因为AI不知道"龙卷风"在Niagara中的具体含义。

### 新的（有效的）工程级提示
```
You are a VFX director, not a node stacker.

Analyze the effect request and output VFX Intent JSON:
- archetype: Is this a vortex? radial burst? lifting motion?
- motion: What is the primary motion model?
- avoidance: What patterns MUST NOT appear?
- layers: How many emitters needed and their roles?

Then create Niagara recipe matching the intent.
```

**系统自动强制这个流程** → 即使用户说"Make it like a tornado"，系统也会：
1. 生成Intent（识别archetype）
2. ApplyArchetypeRules强制规则
3. 禁用错误patterns
4. 应用正确的3层默认结构

---

## 实现的关键位置

### 1. VFXRecipe.h
添加了：
- `EVFXArchetype` 枚举
- `EVFXMotionModel` 枚举  
- `FVFXMotionBehavior` 结构
- `FVFXVisualHierarchy` 结构
- `FVFXPatternAvoidance` 结构
- `FVFXIntent` 结构 ← **核心**

```cpp
USTRUCT(BlueprintType)
struct FVFXRecipe
{
    UPROPERTY(...)
    FVFXIntent Intent;  // ← 现在的第一步
    
    // ... 其他Recipe字段
};
```

### 2. HttpLLMProvider.cpp - BuildSystemPrompt()
新的prompt包含：
- **两阶段指令**：先Intent，后Recipe
- **Archetype说明**：每个类型的具体规则
- **避免patterns指导**：明确什么不能做
- **输出格式**：`{ "intent": {...}, "emitters": [...] }`

### 3. VFXRecipeCompiler.cpp - ValidateAndSanitize()
添加了`ApplyArchetypeRules()`函数：
```cpp
void ApplyArchetypeRules(const FVFXIntent& Intent, 
                         FVFXRecipe& Recipe, 
                         TArray<FString>& OutWarnings)
{
    if (Intent.Archetype == EVFXArchetype::Tornado)
    {
        // 禁用Cone velocity
        // 生成3层结构
        // 强制高度驱动参数
        // ...
    }
    else if (Intent.Archetype == EVFXArchetype::Explosion)
    {
        // 启用Radial和Gravity
        // ...
    }
    // ...
}
```

### 4. Tornado默认3层结构
在`ValidateAndSanitize()`中检测到`Tornado`时，自动生成：
- CoreFunnel (40/sec, 3s, 30size)
- Debris (20/sec, 4s, 50size)
- Dust (60/sec, 5s, 15size)

---

## 工作流示例

### 用户请求：
```
"Create a spinning tornado effect with dark clouds"
```

### 系统流程：

**Step 1: LLM理解阶段**
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
    "requiredLayers": ["core", "debris", "dust"],
    "requiredForces": ["vortex", "centripetal", "lift"]
  },
  "emitters": [
    // LLM可以修改默认参数，但结构由系统强制
  ]
}
```

**Step 2: RecipeCompiler处理**
- 读到`Archetype == Tornado`
- 调用`ApplyArchetypeRules(Tornado, ...)`
- 减弱向外的速度
- 生成或验证3层结构
- 应用高度驱动参数

**Step 3: Niagara构建**
- 3个emitter，分层渲染
- 无Cone velocity
- 无向下重力
- 向上+轻度随机 → **看起来像龙卷风**

---

## 关键insight

> **80%的问题不在AI能力，而在"任务定义"。**

AI不蠢，但如果你问它"生成Niagara节点"，它就会盲目生成。  
如果你问它"你觉得龙卷风应该怎么动"，它会说出对的概念，但不知道如何转化成Niagara参数。

**解决方案：在AI和Niagara之间插入"导演层"**，让系统强制正确的语义→实现映射。

---

## 后续改进方向

1. **时间相关行为**
   - 不同高度的粒子生命周期不同
   - 顶部快速散开，底部缓慢积累

2. **动画曲线支持**
   - 高度→角速度曲线
   - 高度→半径曲线
   - 高度→向上力曲线

3. **更多Archetype特化**
   - 每个archetype添加专用的Material、Texture配置
   - Shape自动选择（Tornado用Cylinder，Explosion用Sphere）

4. **多物理模型结合**
   - Tornado可能需要 Orbit + Centripetal + Lift 组合
   - 系统应支持多个MotionModel同时应用

5. **视觉反馈**
   - 在编辑器中显示"这个特效是什么archetype"
   - 显示应用了哪些archetype规则
   - 标注哪些pattern被避免了

