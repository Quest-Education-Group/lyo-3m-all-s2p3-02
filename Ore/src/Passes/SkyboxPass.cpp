#include "Passes/SkyboxPass.h"
#include "Logger.hpp"

namespace Ore
{
    SkyboxPass::SkyboxPass(Program& program, Camera* camera) : Pass(program, camera)
    {

        GLuint VAO;
        glGenVertexArrays(1, &VAO);

        GLuint buffers[3];
        glGenBuffers(3, buffers);

        auto cubeVertices = GenerateCubeVertices();
    	auto cubeIndices = GenerateCubeIndices();

        m_pVertexArray      = std::make_unique<VertexArrayObject>(VAO);
        m_pVertexBuffer     = std::make_unique<Buffer<Vertex>>(cubeVertices, buffers[1], BufferType::BUFFER, true);
        m_pIndicesBuffer    = std::make_unique<Buffer<uint8>>(cubeIndices, buffers[0], BufferType::BUFFER_ELEMENT, true);

        m_pVertexArray->Bind();
        m_pVertexBuffer->Bind();
        m_pIndicesBuffer->Bind();

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    }

    void SkyboxPass::Execute()
    {
    	if (m_pCamera == nullptr) return;

    	glBindFramebuffer(GL_FRAMEBUFFER, m_gBuffer);
    	glBindTexture(GL_TEXTURE_CUBE_MAP, m_pCubeMap->m_cubeMap);

    	glDepthMask(GL_FALSE);
    	m_program.Use();

    	glm::mat4 view = glm::mat4(glm::mat3(m_pCamera->GetViewMatrix()));
    	m_program.SetUniform("view", view);
    	m_program.SetUniform("proj", m_pCamera->GetProjMatrix());


    	m_pVertexArray->Bind();

    	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, 0);

    	glDepthMask(GL_TRUE);
    	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    constexpr std::vector<Vertex> SkyboxPass::GenerateCubeVertices()
    {
    	float hx = 0.5f;
    	float hy = 0.5f;
    	float hz = 0.5f;

    	std::vector<Ore::Vertex> vertices;
    	vertices.push_back({ { hx, -hy, -hz }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		vertices.push_back({ { hx,  hy, -hz }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } });
		vertices.push_back({ { hx,  hy,  hz }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } });
		vertices.push_back({ { hx, -hy,  hz }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } });

		// -X
		vertices.push_back({ { -hx, -hy,  hz }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } });
		vertices.push_back({ { -hx,  hy,  hz }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } });
		vertices.push_back({ { -hx,  hy, -hz }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } });
		vertices.push_back({ { -hx, -hy, -hz }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } });

		// +Y
		vertices.push_back({ { -hx,  hy, -hz }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } });
		vertices.push_back({ { -hx,  hy,  hz }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } });
		vertices.push_back({ {  hx,  hy,  hz }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } });
		vertices.push_back({ {  hx,  hy, -hz }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } });

		// -Y
		vertices.push_back({ { -hx, -hy,  hz }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f } });
		vertices.push_back({ { -hx, -hy, -hz }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
		vertices.push_back({ {  hx, -hy, -hz }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });
		vertices.push_back({ {  hx, -hy,  hz }, { 0.0f, -1.0f, 0.0f }, { 1.0f, 0.0f } });

		// +Z
		vertices.push_back({ { -hx, -hy,  hz }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } });
		vertices.push_back({ {  hx, -hy,  hz }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f } });
		vertices.push_back({ {  hx,  hy,  hz }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f } });
		vertices.push_back({ { -hx,  hy,  hz }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f } });

		// -Z
		vertices.push_back({ {  hx, -hy, -hz }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f } });
		vertices.push_back({ { -hx, -hy, -hz }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f } });
		vertices.push_back({ { -hx,  hy, -hz }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f } });
		vertices.push_back({ {  hx,  hy, -hz }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f } });
    	return vertices;
    }

    constexpr std::vector<uint8> SkyboxPass::GenerateCubeIndices()
    {
    	std::vector<uint8> indices;
    	for (uint32 face = 0; face < 6; ++face)
    	{
    		const uint32 base = face * 4;
    		indices.push_back(base + 0);
    		indices.push_back(base + 1);
    		indices.push_back(base + 2);
    		indices.push_back(base + 0);
    		indices.push_back(base + 2);
    		indices.push_back(base + 3);
    	}
    	return indices;
    }
}
