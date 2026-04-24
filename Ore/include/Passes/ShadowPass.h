#ifndef ORE_SHADOW_PASS__h_
#define ORE_SHADOW_PASS__h_

#include "Pass.h"
#include "Mesh.h"
#include "LightPass.h"

namespace Ore
{
class ShadowPass : public Pass 
{
public:
    ShadowPass(Program& program);
    ShadowPass(Program& program, Camera* pCamera);
    ~ShadowPass() = default;

    void Execute() override;
    void AddMesh(Mesh const& mesh);
    void AddLight(Light const& light);

private:
    void CreateTexture();

private:
    std::vector<std::reference_wrapper<Mesh const>> m_meshes;
    std::vector<std::reference_wrapper<Light const>> m_lights;

    uptr<VertexArrayObject> m_quadVAO;
    uptr<Buffer<float>> m_quadVBO;
    GLuint m_frameBufferId;

};
}
#endif
