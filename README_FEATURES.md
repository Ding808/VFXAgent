# VFXAgent - AI-Powered Iterative VFX Generation

## New Features Summary

Your VFXAgent plugin now includes advanced AI-driven capabilities for creating complete, production-ready visual effects:

### 🎨 Material Generation System
- **Automatic material creation** with customizable properties (base color, emissive, opacity, roughness, metallic)
- **Procedural texture generation** (gradients, noise, Perlin)
- **Dynamic material assignment** to Niagara emitters

### 🔄 Iterative Self-Optimization
- **AI self-evaluation** - Analyzes generated recipes for issues (too dark, lacks particles, needs more layers)
- **Multiple LLM calls** - Automatically refines the effect through iterative improvements
- **Quality scoring** - Stops when target quality threshold is reached
- **Configurable iterations** (1-10 rounds) with adjustable quality targets (0-1)

### 🖼️ Image-Based Generation
- **Reference image analysis** - LLM understands visual effects from images
- **Vision API support** - Works with GPT-4 Vision and compatible models
- **Visual comparison** - Compares generated effects against reference images

### 🔧 Enhanced Recipe System
- **Material recipes** - Define materials with colors, textures, and properties
- **Texture recipes** - Specify procedural textures (type, colors, resolution, noise parameters)
- **Multi-emitter support** - Create complex layered effects automatically

## How It Works

### Standard Workflow (Text Prompt):
```
User Input: "Blue electric explosion with sparks"
    ↓
LLM generates initial recipe
    ↓
[Optional] Iterative optimization (multiple rounds)
    ├── AI evaluates: "Too dark, needs more emissive"
    ├── Refines recipe with brighter colors
    ├── AI evaluates: "Lacks variety, add more emitters"
    └── Adds spark and glow layers
    ↓
Materials & textures generated
    ↓
Complete Niagara system created
```

### Image-Based Workflow:
```
User provides reference image + optional text prompt
    ↓
LLM analyzes image: "Orange-red core, yellow flames, black smoke"
    ↓
Generates matching recipe with appropriate materials
    ↓
Iterative refinement to match visual style
    ↓
Complete effect matching reference
```

## UI Controls

### New Panel Options:
- ✅ **Enable AI Self-Refinement** - Checkbox to enable iterative optimization
- **Max Iterations** - Spinner (1-10) controlling optimization rounds
- **Target Quality Score** - Slider (0-1) for quality threshold
- **Reference Image** - File picker for image-based generation

## Usage Examples

### Example 1: Iterative Text Generation
```
Prompt: "Create a magical portal with swirling energy"

With iterations enabled (Max: 5):
- Round 1: Basic portal ring
- Round 2: AI adds swirl particles
- Round 3: AI increases emissive strength (was too dim)
- Round 4: AI adds glow layer for depth
- Round 5: Fine-tunes colors and timing
Result: Rich, multi-layered portal effect
```

### Example 2: Image Reference
```
Reference: explosion_photo.jpg
Prompt: "Recreate this explosion effect"

Process:
1. LLM analyzes image colors, layers, behavior
2. Generates recipe with matching emitters
3. Creates custom materials with gradient textures
4. Iterates to match visual style
5. Final system with 4-6 emitters, custom materials
```

### Example 3: Natural Language Refinement
```
Initial: "Fire effect"
Refinement 1: "Make it more orange-red"
Refinement 2: "Add more particles"
Refinement 3: "Include smoke trails"

Each refinement calls LLM to adjust the recipe
```

## Key Classes

### Material Generation:
- `IMaterialGenerator` - Interface for material creation
- `UMaterialGenerator` - Implementation with texture support
- `FVFXMaterialRecipe` - Material parameters (colors, textures, properties)
- `FVFXTextureRecipe` - Texture generation parameters

### Iterative Optimization:
- `UVFXIterativeOptimizer` - Manages optimization loop
- `FVFXOptimizationConfig` - Configuration (max iterations, quality target)
- `FVFXOptimizationResult` - Evaluation results and suggestions

### Enhanced LLM Provider:
- `FVFXGenerationRequest` - Supports text + image input
- `GenerateRecipeFromRequest()` - Multi-modal generation
- `AnalyzeReferenceImage()` - Extract visual description from images
- `CompareWithReference()` - Visual comparison feedback

## Configuration

### For Image Support:
- **Required Model**: GPT-4 Vision (gpt-4o, gpt-4-vision-preview) or compatible
- **API Endpoint**: https://api.openai.com/v1/chat/completions
- **Supported Formats**: PNG, JPG, WebP

### Performance Notes:
- Each iteration = 1 LLM call
- 5 iterations ≈ 5-10 seconds (depends on network/model)
- Images are Base64 encoded (keep < 2MB for best performance)

## Material & Texture Capabilities

### Generated Materials Include:
- Base color with alpha
- Emissive color and strength
- Roughness and metallic values
- Support for additive/translucent blending
- Custom texture assignments

### Procedural Textures:
- **Gradient**: Smooth color transitions (good for particles)
- **Noise**: Fractal noise with octaves (good for smoke, fire)
- **Perlin**: Organic patterns (good for natural effects)

## Quality Evaluation Metrics

The AI evaluates recipes based on:
- **Brightness**: Checks if colors/emissive values are visible
- **Opacity**: Ensures particles aren't too transparent
- **Particle Count**: Validates spawn rates and burst counts
- **Material Richness**: Encourages custom materials
- **Layer Variety**: Promotes multi-emitter complexity
- **Color Diversity**: Checks for color variation across emitters

## Best Practices

### For Best Results:
1. **Detailed prompts** - Describe layers, colors, behavior explicitly
2. **Use iterations** - Enable for complex effects (3-5 rounds typical)
3. **Provide references** - Images give much better context than text alone
4. **Adjust quality target** - Lower for faster results, higher for polish
5. **Monitor logs** - Watch iteration feedback to understand AI reasoning

### Prompt Tips:
❌ Bad: "explosion"
✅ Good: "Orange-red explosion with bright core, yellow-white sparks flying outward, dark smoke trails, and a shockwave ring"

✅ Best: Provide reference image + "Create similar explosion with purple-blue color scheme"

## Troubleshooting

**Materials not generated?**
- Check Recipe includes Materials array
- Verify OutputPath has write permissions

**Iterations not improving quality?**
- Increase max iterations
- Lower quality target threshold
- Use more descriptive prompts

**Image analysis fails?**
- Ensure using Vision-capable model (gpt-4o)
- Check image format and size
- Verify API key has Vision access

## What's Next?

This system now enables:
- ✅ Complete artistic asset creation (materials, textures, not just parameters)
- ✅ Self-improving AI that evaluates and refines its own work
- ✅ Multi-modal input (text, images, or both)
- ✅ User-controlled optimization intensity

The AI can now work like a real VFX artist: analyzing requirements, creating assets, self-reviewing, and iterating until the effect meets quality standards!
