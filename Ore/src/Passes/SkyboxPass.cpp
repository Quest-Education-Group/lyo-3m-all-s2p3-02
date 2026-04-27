#include "Passes/SkyboxPass.h"

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

    }

    constexpr std::array<Vertex, 24> SkyboxPass::GenerateCubeVertices()
    {
        return{
			// FRONT
			Vertex
        	{{ -.5f, -.5f, -.5f }, { 0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},	// 0
			{{ -.5f,  .5f, -.5f }, { 0.0f, 0.0f, -1.0f},{0.0f, 0.0f}}, 	// 1
			{{  .5f,  .5f, -.5f }, { 0.0f, 0.0f, -1.0f},{1.0f, 0.0f}},	// 2
			{{  .5f, -.5f, -.5f }, { 0.0f, 0.0f, -1.0f},{1.0f, 1.0f}},	// 3

			// BACK
			{{ -.5f, -.5f,  .5f },  { 0.0f, 0.0f, 1.0f},{1.0f, 1.0f}},	// 4
			{{  .5f, -.5f,  .5f },  { 0.0f, 0.0f, 1.0f},{0.0f, 1.0f}},	// 5
			{{  .5f,  .5f,  .5f },  { 0.0f, 0.0f, 1.0f},{0.0f, 0.0f}},	// 6
			{{ -.5f,  .5f,  .5f },  { 0.0f, 0.0f, 1.0f},{1.0f, 0.0f}},	// 7

			// LEFT
			 {{ -.5f, -.5f,  .5f }, { -1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},	// 8
			 {{ -.5f,  .5f,  .5f }, { -1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},	// 9
			 {{ -.5f,  .5f, -.5f }, { -1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},	// 10
			 {{ -.5f, -.5f, -.5f }, { -1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},	// 11

			 // RIGHT
			 {{  .5f, -.5f, -.5f } , { 1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},	// 12
			 {{  .5f,  .5f, -.5f } , { 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},	// 13
			 {{  .5f,  .5f,  .5f } , { 1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},	// 14
			 {{  .5f, -.5f,  .5f } , { 1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},	// 15

			 // TOP
			 {{ -.5f,  .5f, -.5f }, { 0.0f, 1.0f, 0.f},  {0.0f, 1.0f}},	// 16
			 {{ -.5f,  .5f,  .5f }, { 0.0f, 1.0f, 0.f},  {0.0f, 0.0f}},	// 17
			 {{  .5f,  .5f,  .5f }, { 0.0f, 1.0f, 0.f},  {1.0f, 0.0f}},	// 18
			 {{  .5f,  .5f, -.5f }, { 0.0f, 1.0f, 0.f}, {1.0f, 1.0f}},	// 19

			 // BOTTOM
			 {{ -.5f, -.5f,  .5f }, { 0.0f,-1.0f,0.f }, {0.0f, 1.0f}},	// 20
			 {{ -.5f, -.5f, -.5f }, { 0.0f,-1.0f,0.f }, {0.0f, 0.0f}},	// 21
			 {{  .5f, -.5f, -.5f }, { 0.0f,-1.0f,0.f }, {1.0f, 0.0f}},	// 22
			 {{  .5f, -.5f,  .5f }, {0.0f,-1.0f,0.f },  {1.0f, 1.0f}},	// 23
		};
    }

    constexpr std::array<uint8, 36> SkyboxPass::GenerateCubeIndices()
    {
    	return {
    		// FRONT
    		0, 1, 2,
			0, 2, 3,

			// BACK
			4, 5, 6,
			4, 6, 7,

			// LEFT
			8, 9, 10,
			8, 10, 11,

			// RIGHT
			12, 13, 14,
			12, 14, 15,

			// TOP
			16, 17, 18,
			16, 18, 19,

			// BOTTOM
			20, 21, 22,
			20, 22, 23
		};
    }
}
