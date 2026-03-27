#include "GeometryFactory.h"


const GeoInfo& GeometryFactory::GetGeometry(PrimitivesType type)
{
	auto it = m_GeoInfo.find(type);
	if (it != m_GeoInfo.end())
		return it->second;

	GeoInfo geo;

	switch (type)
	{
	case PrimitivesType::CUBE:
		geo.m_vertices = CreateCubeVertices(1.0f, 1.0f, 1.0f);
		geo.m_indices = CreateCubeIndices();
		break;
	default:
		throw std::runtime_error("Not implemented");
	}

	auto [insertedIt, _] = m_GeoInfo.emplace(type, std::move(geo));
	return insertedIt->second;
}

void GeometryFactory::MakeCube(float width, float height, float depth) {
	std::vector<Vertex> vertices = CreateCubeVertices(width, height, depth);
	std::vector<uint32> indices = CreateCubeIndices();
	GeoInfo test;
	test.m_vertices = vertices;
	test.m_indices = indices;

	m_GeoInfo[PrimitivesType::CUBE] = test;
}

std::vector<Vertex> GeometryFactory::CreateCubeVertices(float width, float height, float depth)
{
	std::vector<Vertex> vertices;
	vertices.push_back({ glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f) });
	vertices.push_back({ glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f) });
	vertices.push_back({ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f) });
	vertices.push_back({ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
	return vertices;
}

std::vector<uint32> GeometryFactory::CreateCubeIndices()
{
	std::vector<uint32> indices = {
	0,1,2,
	0,2,3
	};

	return indices;
}
