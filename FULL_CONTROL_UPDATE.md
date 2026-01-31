# VFXAgent 全参数控制和智能材质生成更新

## 更新概述

本次更新大幅提升了AI的控制能力和材质生成智能化：

### ✅ 1. 全参数发射器控制

从原来的6个基础参数扩展到**30+个完整参数**，让LLM能够精确控制粒子行为的每个方面。

#### 新增参数分类：

**生成控制 (Spawn)**
- `spawnRate` - 每秒生成粒子数
- `burstCount` - 爆发生成数量
- `burstTime` - 爆发触发时间（支持延迟效果）

**颜色与外观 (Color & Appearance)**  
- `color` - 起始颜色
- `colorEnd` - 结束颜色（渐变）
- `bUseColorGradient` - 启用颜色随生命周期渐变

**生命周期与大小 (Lifetime & Size)**
- `lifetime` - 粒子寿命
- `lifetimeVariation` - 寿命随机变化（0-1）
- `size` - 起始大小
- `sizeEnd` - 结束大小
- `bUseSizeOverLife` - 启用大小随生命周期缩放
- `sizeVariation` - 大小随机变化

**速度与运动 (Velocity & Movement)**
- `velocity` - 初始速度向量
- `velocityVariation` - 速度随机变化
- `acceleration` - 恒定加速度（如重力）
- `drag` - 空气阻力（0-10）

**旋转 (Rotation)**
- `initialRotation` - 初始旋转角度
- `rotationRate` - 旋转速度（度/秒）
- `rotationRateVariation` - 旋转随机变化

**物理 (Physics)**
- `bUseGravity` - 使用重力
- `mass` - 粒子质量

**发射形状 (Emitter Shape)**
- `emitShape` - 发射形状："Point", "Sphere", "Box", "Cone", "Cylinder"
- `shapeSize` - 形状大小/半径

**材质与渲染 (Material & Rendering)**
- `materialIndex` - 材质索引（关联到materials数组）
- `sortOrder` - 渲染顺序（控制层叠）
- `bLocalSpace` - 粒子是否跟随发射器

### ✅ 2. 智能材质生成

LLM现在会**自动为每个视觉层创建定制材质**，而不是使用通用材质。

#### 材质配方完整参数：

```json
{
  "name": "ExplosionCoreMaterial",
  "description": "明亮的橙黄色爆炸核心材质",
  "bIsAdditive": true,
  "bIsUnlit": true,
  "baseMaterialPath": "/Engine/EngineMaterials/ParticleSpriteMaterial",
  "baseColor": {"r":1.0, "g":0.8, "b":0.5, "a":1.0},
  "emissiveColor": {"r":1.0, "g":0.5, "b":0.0, "a":1.0},
  "emissiveStrength": 3.0,
  "opacity": 0.8,
  "roughness": 1.0,
  "metallic": 0.0,
  "generatedTextures": [
    {
      "name": "ExplosionGradient",
      "type": "Gradient",
      "primaryColor": {"r":1, "g":1, "b":1, "a":1},
      "secondaryColor": {"r":0, "g":0, "b":0, "a":0},
      "resolution": 256
    }
  ]
}
```

### ✅ 3. 增强的系统提示词

新的系统提示词包含：
- 完整的JSON模式示例（所有参数）
- 详细的参数说明和推荐值范围
- 物理真实性指导
- 材质生成最佳实践
- 具体效果类型的示例配方

## LLM现在能做什么？

### 示例1：复杂爆炸效果

```
用户输入："创建一个火焰爆炸"

AI生成：
{
  "emitters": [
    {
      "name": "ExplosionCore",
      "templateName": "OmnidirectionalBurst",
      "burstCount": 200,
      "lifetime": 1.5,
      "size": 30,
      "sizeEnd": 10,
      "bUseSizeOverLife": true,
      "color": {"r":1, "g":0.6, "b":0.2, "a":1},
      "colorEnd": {"r":0.3, "g":0, "b":0, "a":0},
      "bUseColorGradient": true,
      "velocity": {"x":0, "y":0, "z":400},
      "velocityVariation": 0.5,
      "acceleration": {"x":0, "y":0, "z":-980},
      "drag": 1.0,
      "materialIndex": 0
    },
    {
      "name": "Sparks",
      "templateName": "DirectionalBurst",
      "burstCount": 150,
      "lifetime": 2.0,
      "size": 3,
      "color": {"r":1, "g":1, "b":0.5, "a":1},
      "velocity": {"x":0, "y":0, "z":600},
      "velocityVariation": 0.7,
      "bUseGravity": true,
      "drag": 0.5,
      "materialIndex": 1
    },
    {
      "name": "Smoke",
      "templateName": "Fountain",
      "spawnRate": 50,
      "lifetime": 5.0,
      "size": 20,
      "sizeEnd": 80,
      "bUseSizeOverLife": true,
      "color": {"r":0.2, "g":0.2, "b":0.2, "a":0.8},
      "colorEnd": {"r":0.1, "g":0.1, "b":0.1, "a":0},
      "bUseColorGradient": true,
      "velocity": {"x":0, "y":0, "z":50},
      "velocityVariation": 0.3,
      "drag": 3.0,
      "materialIndex": 2
    }
  ],
  "materials": [
    {
      "name": "ExplosionCoreMaterial",
      "bIsAdditive": true,
      "emissiveColor": {"r":1, "g":0.5, "b":0, "a":1},
      "emissiveStrength": 4.0,
      "generatedTextures": [...]
    },
    {
      "name": "SparkMaterial",
      "bIsAdditive": true,
      "emissiveColor": {"r":1, "g":1, "b":0.7, "a":1},
      "emissiveStrength": 5.0
    },
    {
      "name": "SmokeMaterial",
      "bIsAdditive": false,
      "opacity": 0.6,
      "generatedTextures": [...]
    }
  ]
}
```

### 示例2：魔法传送门

```
用户："创建一个蓝色魔法传送门"

AI知道需要：
- 核心光环（Ribbon，旋转）
- 能量粒子（螺旋上升，无重力）
- 符文碎片（漂浮，发光）
- 中心爆发（明亮的蓝白色）

AI会为每层创建：
- 专用材质（不同的发光强度和颜色）
- 适当的物理参数（旋转、拖拽、速度）
- 程序化纹理（渐变、噪波）
```

## 使用效果对比

### 之前：
```json
{
  "emitters": [{
    "name": "Effect",
    "spawnRate": 10,
    "color": {"r":1, "g":1, "b":1, "a":1},
    "size": 10,
    "velocity": {"x":0, "y":0, "z":100}
  }],
  "materials": [{
    "description": "Basic material",
    "bIsAdditive": true
  }]
}
```
结果：单调、缺乏细节、通用材质

### 现在：
```json
{
  "emitters": [
    {
      "name": "CoreBurst",
      "burstCount": 200,
      "lifetime": 1.5,
      "size": 30,
      "sizeEnd": 5,
      "bUseSizeOverLife": true,
      "color": {"r":1, "g":0.6, "b":0.2, "a":1},
      "colorEnd": {"r":0.2, "g":0, "b":0, "a":0},
      "bUseColorGradient": true,
      "velocity": {"x":0, "y":0, "z":500},
      "velocityVariation": 0.5,
      "drag": 1.5,
      "rotationRate": 180,
      "materialIndex": 0
    },
    // + 更多层...
  ],
  "materials": [
    {
      "name": "CoreMaterial",
      "emissiveColor": {"r":1, "g":0.5, "b":0, "a":1},
      "emissiveStrength": 4.0,
      "opacity": 0.8,
      "generatedTextures": [{
        "type": "Gradient",
        "primaryColor": {"r":1, "g":1, "b":1, "a":1},
        "secondaryColor": {"r":0, "g":0, "b":0, "a":0}
      }]
    },
    // + 专用材质...
  ]
}
```
结果：丰富的多层效果、定制材质、真实物理行为

## LLM指导原则

系统提示词现在教导LLM：

1. **物理真实性**
   - 爆炸：高速度(300-800)，短寿命(0.5-2s)，重力
   - 火焰：中速度(50-200)，阻力，向上加速，颜色渐变
   - 烟雾：低速度(20-100)，高阻力，大小增长
   - 火花：极高速度(400-1000)，重力，小尺寸

2. **视觉质量**
   - 使用 emissiveStrength 2-5 确保可见性
   - 添加颜色渐变让效果更生动
   - 大小变化创造动态感
   - 使用variation参数增加有机感

3. **材质策略**
   - 每个视觉风格一个材质
   - 发光效果使用additive + 高emissive
   - 烟雾使用alpha blend + 低opacity
   - 为软粒子生成渐变纹理

4. **性能优化**
   - 一次性效果用burstCount
   - 持续效果用spawnRate
   - 合理的粒子数量（爆发100-500，持续10-200）

## 技术实现

### 参数应用流程：

```
FVFXEmitterRecipe (30+参数)
    ↓
NiagaraSystemGenerator (转换)
    ↓
FVFXEmitterSpec
    ↓
NiagaraSpecExecutor::ConfigureEmitter (应用)
    ↓
尝试多个常见参数名称变体
    ↓
Niagara粒子系统
```

### 智能参数映射：

ConfigureEmitter 会尝试设置多个可能的参数名：
```cpp
// 例如颜色参数
SetVariableLinearColor(System, Namespace, "InitializeParticle.Color", Color);
SetVariableLinearColor(System, Namespace, "Color", Color);
SetVariableLinearColor(System, Namespace, "Particle Color", Color);
```

这确保无论使用哪个Niagara模板，参数都能正确应用。

## 使用建议

1. **让LLM发挥**：不要过度指定参数，让AI根据效果类型选择合适的值
2. **使用描述性语言**："快速移动的火花"、"缓慢膨胀的烟雾"
3. **信任物理参数**：LLM现在会应用真实的重力、阻力等
4. **检查材质**：AI会为不同层创建专用材质
5. **迭代优化**：启用迭代模式让AI自己调整参数

## 总结

这次更新让VFXAgent从"简单参数调整"升级为"专业VFX美术师"：

- ✅ **完整控制**：30+参数覆盖粒子行为的所有方面
- ✅ **智能材质**：AI自动为每层创建定制材质
- ✅ **物理真实**：LLM理解并应用真实物理规律
- ✅ **专业品质**：生成的效果接近手工制作的质量

AI现在不仅能生成特效，还能**理解特效应该如何运动、如何发光、如何随时间变化**！
