#include "Passes/ShadowPass.h"
#include "Logger.hpp"
#include "Passes/LightPass.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

namespace Ore
{
ShadowPass::ShadowPass(Program& program) : Pass(program) 
{
    CreateTexture();
}
ShadowPass::ShadowPass(Program& program, Camera* pCamera) : Pass(program, pCamera) 
{
    CreateTexture();
}

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
    glGenFramebuffers(1, &m_frameBufferId);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);

    GLuint depth;
    glGenTextures(1 ,&depth);
    m_shadowMap = TextureObject(depth, TextureType::TYPE_2D);
    m_shadowMap.Bind();
    m_shadowMap.GenerateTexture(DataType::FLOAT, 4096.0f, 4096.0f, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT);

    m_shadowMap.AddParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    m_shadowMap.AddParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    m_shadowMap.AddParameters(GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_shadowMap.AddParameters(GL_TEXTURE_WRAP_T, GL_REPEAT);

    m_shadowMap.AttachToFrameBuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        Logger::LogWithLevel(LogLevel::ERROR, "Shadow Pass framebuffer is not complete !");
}

void ShadowPass::Execute()
{
    if (m_pCamera == nullptr) return;

    //glBindFramebuffer(GL_FRAMEBUFFER, m_gBuffer);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);
    glViewport(0,0,4096,4096);
    m_program.Use();
    m_program.SetUniform("viewProj", m_pCamera->GetViewProjMatrix());

    glClear(GL_DEPTH_BUFFER_BIT);

    for (uint32 i = 0; i < m_lights.size(); ++i)
    {
        glm::vec3 dir = glm::vec3(m_lights[i].get().position);
        glm::vec3 lightInvDir = -dir;
        glm::mat4 depthProjectionMatrix = glm::ortho<float>(-10,10,-10,10,-10,20);
        glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir, glm::vec3(0,0,0), glm::vec3(0,1,0));
        m_lightSpaceMatrix = depthProjectionMatrix * depthViewMatrix;

        m_program.SetUniform("lightSpaceMatrix", m_lightSpaceMatrix);

        for(Mesh const& mesh : m_meshes)
        {
            m_program.SetUniform("model", mesh.GetTransform());
            mesh.GetGeometry().Draw();
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_meshes.clear();
    m_lights.clear();
}
}
