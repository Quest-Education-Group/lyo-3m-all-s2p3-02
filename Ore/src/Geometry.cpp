#include "Geometry.h"
#include "VertexArrayObject.h"
#include "Logger.hpp"


using namespace Ore;

void Geometry::CalculateTangents(std::vector<Vertex>& vertices, std::vector<uint32> const& indices)
{
    //TODO 
    for(uint32 i = 0; i<indices.size(); i+=3)
    {
        uint32 index0 = indices[i];
        uint32 index1 = indices[i + 1];
        uint32 index2 = indices[i + 2];

        glm::vec3 edge1     = vertices[index1]       .position   - vertices[index0].position;
        glm::vec3 edge2     = vertices[index2]       .position   - vertices[index0].position;
        glm::vec2 deltaUV1  = vertices[index1]       .texCoords  - vertices[index0].texCoords;
        glm::vec2 deltaUV2  = vertices[index2]       .texCoords  - vertices[index0].texCoords;

        float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        glm::vec3 tangent;
        
        tangent.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangent.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangent.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

        vertices[index0].tangent = tangent;
        vertices[index1].tangent = tangent;
        vertices[index2].tangent = tangent;
    }
}

Geometry::Geometry(std::span<Vertex const> points, std::vector<uint32> const& indices)
{
    m_indiceSize = static_cast<uint32>(indices.size());
    GLuint vaoId;

    glGenVertexArrays(1, &vaoId);

    m_pVao = std::make_unique<VertexArrayObject>(vaoId);
    m_pVao->Bind();

    AddPoints(points);
    AddIndices(indices);
    Setup();    
}
Geometry::Geometry(Geometry const& other)
{
    m_pVao = std::make_unique<VertexArrayObject>(*other.m_pVao);
    m_indiceSize = other.m_indiceSize;
    m_pIndexBuffer = std::make_unique<Buffer<uint32>>(*other.m_pIndexBuffer);
    m_pVertexBuffer = std::make_unique<Buffer<Vertex>>(*other.m_pVertexBuffer);
}

void Geometry::Draw() const
{
    m_pVao->Bind();
    glDrawElements(GL_TRIANGLES, m_indiceSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Geometry::AddPoints(std::span<Vertex const> vertices)
{
    GLuint id;
    glGenBuffers(1, &id); 

    m_pVertexBuffer = std::make_unique<Buffer<Vertex>>(vertices, id, BufferType::BUFFER, true);
}

void Geometry::AddIndices(std::span<uint32 const> indices)
{
    GLuint id;
    glGenBuffers(1, &id);

    m_pIndexBuffer = std::make_unique<Buffer<uint32>>(indices, id, BufferType::BUFFER_ELEMENT, true);
}



void Geometry::Setup()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribIPointer(4, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, boneIDS));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));

    glBindVertexArray(0);
}
