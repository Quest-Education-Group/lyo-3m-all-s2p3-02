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
    TextureObject depthTexture(depth, TextureType::TYPE_2D);
    depthTexture.Bind();
    depthTexture.GenerateTexture(DataType::FLOAT, 1024.0f, 1024.0f, GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT);

    depthTexture.AddParameters(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    depthTexture.AddParameters(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    depthTexture.AddParameters(GL_TEXTURE_WRAP_S, GL_REPEAT);
    depthTexture.AddParameters(GL_TEXTURE_WRAP_T, GL_REPEAT);

    depthTexture.AttachToFrameBuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);

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

    m_program.Use();
    m_program.SetUniform("viewProj", m_pCamera->GetViewProjMatrix());

    Camera::OrthographicSettings orth 
    {
        -10.0f, -10.0f, 
         10.0f,  10.0f,
        -10.0f, 20.0f

    };
    Camera lightPOV(orth);

    for (uint32 i = 0; i < m_lights.size(); ++i)
    {
        
        glm::vec3 dir = glm::vec3(m_lights[i].get().position);
        //dir.z = -dir.z;
        lightPOV.LookAt(dir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        lightPOV.UpdateCamera();
        m_program.Use();

        glViewport(0,0,1024,1024);
        glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferId);
        glClear(GL_DEPTH_BUFFER_BIT);
        glm::vec3 lightInvDir = dir;
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
