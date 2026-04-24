#include "Passes/ShadowPass.h"

namespace Ore
{
ShadowPass::ShadowPass(Program& program) : Pass(program) 
{
}
ShadowPass::ShadowPass(Program& program, Camera* pCamera) : Pass(program, pCamera) {}

void ShadowPass::AddMesh(Mesh const& mesh)
{
    m_meshes.push_back(mesh);
}
void ShadowPass::AddLight(Light const& light)
{
    m_lights.push_back(light);
}

void ShadowPass::CreateTexture()
{
    GLuint depth;
    glGenTextures(1 ,&depth);
    TextureObject depthTexture(depth, TextureType::TYPE_2D);
    depthTexture.Bind();
    depthTexture.GenerateTexture(DataType::FLOAT, 1024.0f, 1024.0f, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT);

}

void ShadowPass::Execute()
{
    if (m_pCamera == nullptr) return;

    glBindFramebuffer(GL_FRAMEBUFFER, m_gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_program.Use();
    m_program.SetUniform("viewProj", m_pCamera->GetViewProjMatrix());
    //m_program.SetUniform("view", viewMatrix);

    for (uint32 i = 0; i < m_meshes.size(); ++i)
    {
        if (m_meshes[i].get().GetIsActive() == false)
            continue;

        m_program.SetUniform("model", m_meshes[i].get().GetTransform());
        m_meshes[i].get().Draw(m_program);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_meshes.clear();
}
}
