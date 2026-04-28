#ifndef ORE_LIGHT_PASS__H_
#define ORE_LIGHT_PASS__H_

#include "Pass.h"
#include "Color.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "ShadowPass.h"

#include <span>

namespace Ore
{
using LightSpan =  std::span<struct Light>;

struct Light
{
    glm::vec4 position = glm::vec4(0.0f, 0.0f, 2.0f, 1.0f);
    
    float constant = 1.0f;
    float linear = 0.7f;
    float quadratic = 1.8f;
    Color color = {1.0f, 1.0f, 1.0f, 1.0f};
};

class LightPass final : public Pass
{
public:
    LightPass(Program& program, LightSpan lights);
    LightPass(Program& program, LightSpan lights, Camera* pCamera);
    ~LightPass() = default;

    void SetLights(LightSpan const& lights);
    void SetShadowPass(ShadowPass const& shadowpass);
    void Execute() override;

private:
    void RenderQuad();
    void GenerateQuad();

private:
    LightSpan m_lights;
    uptr<VertexArrayObject> m_quadVAO;
    uptr<Buffer<float>> m_quadVBO;
    GLuint m_quadVAOId;
    GLuint m_quadVBOId;
    ShadowPass m_shadowPass;
};
}
#endif
 
