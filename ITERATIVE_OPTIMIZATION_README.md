# VFXAgent 迭代优化与材质生成功能说明

## 概述

VFXAgent现已支持完整的AI驱动特效生成，包括：
- ✅ 自动材质生成和调整
- ✅ 程序化纹理生成
- ✅ 基于图片的特效生成
- ✅ 迭代自我优化（AI自检并多次调用LLM改进）
- ✅ 自然语言颜色和参数调整

## 核心功能

### 1. 材质生成系统

#### 新增类：
- **IMaterialGenerator** - 材质生成接口
- **UMaterialGenerator** - 材质和纹理的具体实现

#### 支持的功能：
- 自动创建材质实例（Material Instances）
- 设置基础颜色、自发光、不透明度等参数
- 程序化生成渐变纹理（Gradient Textures）
- 程序化生成噪波纹理（Noise/Perlin Textures）

#### 材质配方参数（FVFXMaterialRecipe）：
```cpp
- Name: 材质名称
- BaseColor: 基础颜色
- EmissiveColor: 自发光颜色
- EmissiveStrength: 自发光强度
- Opacity: 不透明度
- Roughness: 粗糙度
- Metallic: 金属度
- GeneratedTextures: 要生成的程序化纹理列表
```

### 2. 迭代优化系统

#### 新增类：
- **UVFXIterativeOptimizer** - 管理迭代优化流程
- **FVFXOptimizationConfig** - 优化配置
- **FVFXOptimizationResult** - 优化结果和反馈

#### 工作流程：
1. **初始生成** - LLM生成初始特效配方
2. **自我评估** - AI分析配方的问题（太暗、太淡、缺少层次等）
3. **生成改进建议** - 基于问题生成优化提示
4. **调用LLM优化** - 使用RefineRecipe进一步改进
5. **重复迭代** - 直到达到目标质量分数或最大迭代次数

#### 评估指标：
- 颜色亮度检查
- 粒子数量检查
- 材质丰富度检查
- 层次多样性检查
- 颜色变化检查

### 3. 图片输入支持

#### 新增功能：
- **图片分析** - LLM分析参考图片并生成描述
- **基于图片生成** - 根据图片创建匹配的特效
- **视觉对比** - 将生成结果与参考图片对比

#### 支持的图片格式：
- PNG
- JPG/JPEG
- WebP

#### 使用方式：
```cpp
FVFXGenerationRequest Request;
Request.TextPrompt = "创建爆炸特效";
Request.ReferenceImagePath = "C:/Images/explosion.png";
Request.bGenerateMaterials = true;
Request.bGenerateTextures = true;

FVFXRecipe Recipe = LLMProvider->GenerateRecipeFromRequest(Request);
```

### 4. 程序化纹理生成

#### 支持的纹理类型：

**渐变纹理（Gradient）**
- 在两种颜色间平滑过渡
- 可自定义分辨率
- 适用于粒子颜色渐变

**噪波纹理（Noise/Perlin）**
- 多层级分形噪波
- 可调节缩放和细节层数
- 适用于烟雾、火焰等自然效果

#### 纹理配方参数（FVFXTextureRecipe）：
```cpp
- Name: 纹理名称
- Type: "Gradient" | "Noise" | "Perlin"
- PrimaryColor: 主色
- SecondaryColor: 副色
- Resolution: 分辨率（256, 512, 1024等）
- NoiseScale: 噪波缩放
- Octaves: 分形层数
```

## UI界面更新

### 新增控件：

1. **启用迭代优化** - 复选框
   - 启用后将进行多轮LLM调用自动优化

2. **最大迭代次数** - 数值框（1-10）
   - 控制最多进行几轮优化
   - 默认值：5

3. **目标质量分数** - 滑块（0-1）
   - 达到此分数后停止迭代
   - 默认值：0.85

## 使用示例

### 示例1：文本生成 + 迭代优化

```
描述：创建一个蓝色电弧爆炸，带有火花飞溅和烟雾尾迹

设置：
✅ 启用迭代优化
最大迭代次数：5
目标质量：0.85

结果：
- 第1轮：生成基础配方
- 第2轮：AI检测到亮度不足，增加发光强度
- 第3轮：添加更多层次（火花、烟雾）
- 第4轮：调整颜色对比度
- 第5轮：优化粒子数量分布
```

### 示例2：图片参考生成

```
参考图片：explosion_reference.png
描述：根据图片创建类似的爆炸效果

设置：
✅ 启用迭代优化
参考图片路径：C:/Images/explosion_reference.png

流程：
1. LLM分析图片：识别出橙红色核心、黄色外围、黑色烟雾
2. 生成初始配方：3个发射器（核心、火焰、烟雾）
3. AI自检发现颜色过淡，调整EmissiveStrength
4. 添加材质和渐变纹理增强视觉效果
5. 最终生成完整特效系统
```

### 示例3：自然语言微调

```
初始生成：火焰特效

细化请求：
1. "让它更红一些" → 调整颜色向红色偏移
2. "增加粒子数量" → 提高SpawnRate
3. "添加火花效果" → 新增Sprite发射器
4. "让烟雾更浓" → 增加烟雾不透明度和粒子大小
```

## 技术架构

### 模块依赖：

```
VFXAgentEditor (UI层)
    ↓
VFXAgentNiagara (生成层)
    ├── MaterialGenerator - 材质生成
    ├── VFXIterativeOptimizer - 迭代优化
    └── NiagaraSystemGenerator - 系统组装
    ↓
VFXAgentCore (核心层)
    └── ILLMProvider - LLM接口
        ├── HttpLLMProvider - 支持OpenAI/Ollama
        └── 新增：图片分析、视觉对比
```

### 数据流：

```
用户输入（文本+图片）
    ↓
LLM分析（图片描述 + 文本理解）
    ↓
生成Recipe（包含材质和纹理配方）
    ↓
[可选] 迭代优化循环
    ├── 自我评估
    ├── 生成改进建议
    └── LLM细化配方
    ↓
材质生成器（创建材质和纹理资产）
    ↓
Niagara系统生成器（组装完整特效）
    ↓
保存并编译资产
```

## 配置要求

### LLM Provider配置：

**支持图片输入的模型：**
- OpenAI GPT-4 Vision (gpt-4o, gpt-4-vision-preview)
- 其他兼容OpenAI Vision API的模型

**最低配置：**
- Endpoint: https://api.openai.com/v1/chat/completions
- Model: gpt-4o-mini （文本）或 gpt-4o（图片）
- API Key: 必需

### 性能考虑：

**迭代优化的成本：**
- 每次迭代 = 1次LLM调用
- 5次迭代 ≈ 5-10秒（取决于网络和模型速度）
- 建议：简单特效使用2-3次迭代，复杂特效使用5-8次

**图片处理：**
- 图片会被Base64编码后发送到LLM
- 建议图片大小 < 2MB
- 较大图片会增加API调用时间和成本

## 故障排除

### 常见问题：

1. **材质未生成**
   - 检查Recipe中是否包含Materials数组
   - 确认OutputPath有写入权限

2. **迭代优化效果不明显**
   - 增加MaxIterations
   - 降低TargetQualityScore
   - 提供更详细的原始提示

3. **图片分析失败**
   - 确认使用支持Vision的模型（如gpt-4o）
   - 检查图片格式和大小
   - 验证API Key权限

4. **纹理生成失败**
   - 检查TextureRecipe中的参数有效性
   - 确保Resolution为2的幂次方（256, 512, 1024）

## 未来扩展方向

### 计划中的功能：

- [ ] 3D模型生成支持（使用Mesh发射器）
- [ ] 实时预览系统（在迭代时显示中间结果）
- [ ] 更多程序化纹理类型（Voronoi、Cellular等）
- [ ] 基于真实图片的纹理提取
- [ ] 批量生成和变体系统
- [ ] 性能自动优化（LOD生成）

## 示例Prompt

### 高质量提示词示例：

```
"创建一个魔法召唤特效：
- 地面出现蓝紫色魔法阵，向外扩散光波
- 中心升起螺旋上升的能量粒子，颜色从深蓝渐变到亮紫
- 周围有金色符文碎片漂浮旋转
- 顶部有明亮的白色爆发光芒
- 整体风格偏向奇幻魔法，带有强烈的发光效果"
```

更好的做法是提供参考图片并配合简短描述：
```
图片：magic_circle.png
描述：根据图片创建类似的魔法召唤特效，调整为蓝紫色系
```

## 总结

这次更新显著增强了VFXAgent的能力：

✅ **完整的艺术资产生成** - 不再只是参数调整，而是真正创建材质和纹理
✅ **智能自我优化** - AI能够自己评估和改进生成结果
✅ **多模态输入** - 支持文本、图片或两者结合
✅ **可控的迭代过程** - 用户可以调节优化强度和迭代次数

现在AI可以像真正的VFX美术师一样工作：分析需求、创建资产、自我检查、持续优化，直到达到满意的效果！
