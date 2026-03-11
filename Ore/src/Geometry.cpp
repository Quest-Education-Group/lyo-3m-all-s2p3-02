#include "Geometry.h"
#include "Buffer.h"

Geometry::Geometry(std::vector<float> const& points, std::vector<uint32> const& indices)
{
    AddPoints(points);
    AddIndices(indices);
}

Geometry::~Geometry()
{
}

void Geometry::AddPoints(std::vector<float> const& points)
{
    GLuint id;
    glGenBuffers(1, &id); 

    Buffer arrayBuffer(points, id, BufferType::BUFFER, true);
}

void Geometry::AddIndices(std::vector<uint32> const& indices)
{
    GLuint id;
    glGenBuffers(1, &id);

    Buffer indexBuffer(indices, id, BufferType::BUFFER_ELEMENT, true);
}
