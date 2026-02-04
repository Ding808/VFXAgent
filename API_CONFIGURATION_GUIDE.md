# VFXAgent - API配置和故障排除指南

## ❌ 常见错误：HTTP Request Failed

### 错误信息
```
LLM error: HTTP request failed (status=Failed)
ERROR: Initial recipe generation failed
```

### 根本原因
这个错误通常是由以下原因之一引起：
1. **OpenAI API Key未配置或无效** ← 最常见
2. 网络连接问题
3. API端点URL错误
4. API服务不可用

---

## ✅ 解决方案

### 步骤1: 配置OpenAI API Key

#### 方法A: 通过编辑器UI（推荐）
1. 打开Unreal Editor
2. 进入 **编辑 (Edit) → 项目设置 (Project Settings)**
3. 在左侧搜索 **"VFXAgent"**
4. 找到 **LLM** 分类
5. 在 **LLM API Key** 字段中输入你的OpenAI API密钥
6. 点击保存

**获取API Key**：
- 访问 https://platform.openai.com/api-keys
- 登录你的OpenAI账户
- 点击 "Create new secret key"
- 复制密钥并粘贴到Unreal设置中

#### 方法B: 通过配置文件
编辑项目的配置文件：
```
你的项目/Config/DefaultVFXAgent.ini
```

添加或修改：
```ini
[/Script/VFXAgentEditor.VFXAgentSettings]
LLMApiKey="sk-proj-你的实际密钥"
LLMEndpoint="https://api.openai.com/v1/chat/completions"
LLMModel="gpt-4o-mini"
LLMBackend="OpenAI"
```

⚠️ **安全提示**：不要将API Key提交到版本控制！添加到 `.gitignore`：
```
Config/DefaultVFXAgent.ini
```

---

### 步骤2: 验证配置

#### 在编辑器中验证
1. 打开VFXAgent面板
2. 查看日志输出中的 `LLM Settings:` 行
3. 确认：
   - `Backend=OpenAI`
   - `Endpoint=https://api.openai.com/v1/chat/completions`
   - `Model=gpt-4o-mini`
   - `ApiKey=set` ← 应该显示"set"而不是"missing"

#### 测试连接
在VFXAgent面板中输入简单的测试提示：
```
Generate a simple fire particle effect
```

如果配置正确，你应该看到：
```
Generating VFX...
Iteration 0: Generating initial recipe...
Recipe generated (X tokens)
```

---

### 步骤3: 处理其他错误

#### 错误：OpenAI API key is missing or placeholder
**原因**：API Key字段为空或包含占位符值（如"set"、"<set>"）

**解决**：按步骤1设置真实的API Key

#### 错误：HTTP request timed out
**原因**：网络连接慢或API服务响应慢

**解决**：
1. 增加超时时间（项目设置 → VFXAgent → LLM Timeout Seconds）
2. 检查网络连接
3. 尝试使用VPN（如果在某些地区）

#### 错误：LLM returned HTTP 401
**原因**：API Key无效或过期

**解决**：
1. 检查API Key是否正确复制（无空格、无换行）
2. 访问 https://platform.openai.com/api-keys 验证密钥是否有效
3. 检查OpenAI账户是否有余额

#### 错误：LLM returned HTTP 429
**原因**：超过API速率限制

**解决**：
1. 等待几分钟后重试
2. 检查OpenAI账户的配额和限制
3. 考虑升级OpenAI订阅计划

#### 错误：LLM returned HTTP 500/503
**原因**：OpenAI服务暂时不可用

**解决**：
1. 访问 https://status.openai.com/ 检查服务状态
2. 等待几分钟后重试
3. 考虑使用其他兼容的API端点

---

## 🔧 使用其他LLM后端

### 选项1: 使用Ollama（本地，免费）

1. 安装Ollama: https://ollama.ai/
2. 下载模型：
   ```bash
   ollama pull llama2
   # 或者更大的模型
   ollama pull llama3
   ```
3. 在项目设置中配置：
   ```
   LLM Backend: Ollama
   LLM Endpoint: http://localhost:11434/api/generate
   LLM Model: llama2
   LLM API Key: (留空)
   ```

**优点**：
- 完全免费
- 本地运行，无隐私担忧
- 无API限制

**缺点**：
- 需要较强的GPU
- 生成质量可能不如GPT-4

### 选项2: 使用Azure OpenAI

1. 在Azure门户创建OpenAI资源
2. 获取端点和密钥
3. 配置：
   ```
   LLM Backend: OpenAI
   LLM Endpoint: https://你的资源名.openai.azure.com/openai/deployments/你的部署名/chat/completions?api-version=2024-02-15-preview
   LLM Model: (留空或使用部署名)
   LLM API Key: 你的Azure密钥
   ```

### 选项3: 使用其他OpenAI兼容端点

许多服务提供OpenAI兼容的API：
- **Together AI**: https://api.together.xyz/v1/chat/completions
- **Perplexity**: https://api.perplexity.ai/chat/completions
- **Groq**: https://api.groq.com/openai/v1/chat/completions

配置方式与OpenAI相同，只需更改Endpoint和API Key。

---

## 🐛 调试技巧

### 启用详细日志
1. 在Unreal Editor中打开 Output Log 窗口
2. 筛选 "LogVFXAgent"
3. 查看详细的请求和响应信息

### 检查HTTP请求详情
在源代码中临时添加日志（仅用于调试）：

编辑 `HttpLLMProvider.cpp` 中的 `RequestRecipeJsonAsync` 函数：
```cpp
// 在 Req->ProcessRequest() 前添加
UE_LOG(LogVFXAgent, Log, TEXT("Sending HTTP request:"));
UE_LOG(LogVFXAgent, Log, TEXT("  URL: %s"), *EffectiveEndpoint);
UE_LOG(LogVFXAgent, Log, TEXT("  Model: %s"), *Model);
UE_LOG(LogVFXAgent, Log, TEXT("  Has API Key: %s"), ApiKey.IsEmpty() ? TEXT("No") : TEXT("Yes"));
```

### 手动测试API
使用curl或Postman测试API连接：

```bash
curl https://api.openai.com/v1/chat/completions \
  -H "Content-Type: application/json" \
  -H "Authorization: Bearer YOUR_API_KEY" \
  -d '{
    "model": "gpt-4o-mini",
    "messages": [{"role": "user", "content": "Say hello"}]
  }'
```

如果curl成功但Unreal失败，可能是Unreal的HTTP模块配置问题。

---

## 📋 配置检查清单

完成配置后，验证以下项目：

- [ ] API Key已设置且有效
- [ ] API Key没有前后空格
- [ ] Endpoint URL正确（https://api.openai.com/v1/chat/completions）
- [ ] Model名称正确（gpt-4o-mini 或 gpt-4o）
- [ ] Backend设置为 "OpenAI"
- [ ] 网络连接正常
- [ ] OpenAI账户有余额
- [ ] 在VFXAgent面板中看到 `ApiKey=set`

---

## 💰 OpenAI定价参考（2024）

| 模型 | 输入 | 输出 | 推荐用途 |
|------|------|------|---------|
| gpt-4o-mini | $0.15/1M tokens | $0.60/1M tokens | VFXAgent默认，性价比高 |
| gpt-4o | $2.50/1M tokens | $10.00/1M tokens | 复杂特效，质量更高 |
| gpt-3.5-turbo | $0.50/1M tokens | $1.50/1M tokens | 预算有限 |

**估算**：
- 一次简单VFX生成：~1000-2000 tokens
- 使用gpt-4o-mini成本：约 $0.001-0.002/次
- 100次生成：约 $0.10-0.20

---

## 🔐 安全最佳实践

1. **不要硬编码API Key**：使用项目设置
2. **不要提交到Git**：添加配置文件到 `.gitignore`
3. **定期轮换密钥**：在OpenAI控制台创建新密钥
4. **监控使用量**：定期检查OpenAI账户的使用情况
5. **设置使用限制**：在OpenAI控制台设置月度限额

---

## 📞 仍然无法工作？

如果按照以上步骤仍然遇到问题：

1. **检查日志**：Output Log 中搜索 "LogVFXAgent" 和 "Error"
2. **复制完整错误**：包括堆栈跟踪
3. **验证环境**：
   - Unreal Engine版本
   - VFXAgent插件版本
   - 操作系统
   - 网络环境（公司网络、VPN等）

4. **常见特殊情况**：
   - **公司网络**：可能需要配置代理
   - **中国大陆**：需要使用VPN或Azure OpenAI
   - **防火墙**：确保允许HTTPS出站连接

---

## 快速故障排除流程图

```
HTTP request failed
    ↓
检查 ApiKey=? 在日志中
    ↓
├─ "missing" → 配置API Key (步骤1)
├─ "set" → 检查网络连接
    ↓
    测试 curl 命令
        ↓
    ├─ 成功 → Unreal HTTP模块问题
    └─ 失败 → 网络/API问题
        ↓
        检查 status.openai.com
            ↓
        ├─ 服务正常 → API Key错误或余额不足
        └─ 服务异常 → 等待修复或使用备用端点
```

---

## 示例：完整的工作配置

**DefaultVFXAgent.ini**：
```ini
[/Script/VFXAgentEditor.VFXAgentSettings]
LLMEndpoint="https://api.openai.com/v1/chat/completions"
LLMModel="gpt-4o-mini"
LLMApiKey="sk-proj-xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
LLMBackend="OpenAI"
LLMTimeoutSeconds=60.000000
DefaultOutputPath="/Game/VFXAgent/Generated"
bUseTemplates=True
AssetNamePrefix="VFX_"
```

**预期日志输出**：
```
Generating VFX...
Prompt: A blue electric arc explosion with smoke trails
LLM Settings: Backend=OpenAI, Endpoint=https://api.openai.com/v1/chat/completions, Model=gpt-4o-mini, Timeout=60.0s, ApiKey=set
Using iterative optimization mode
Iteration 0: Generating initial recipe...
Recipe generated (1523 tokens)
[正常继续...]
```

