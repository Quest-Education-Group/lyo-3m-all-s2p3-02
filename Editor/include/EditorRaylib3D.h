#ifndef __EDITOR_RAYLIB3D__H_
#define __EDITOR_RAYLIB3D__H_

#include <Serialization/json.hpp>

#include <raylib.h>

#include <Node.h>
#include <Define.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#define RLIGHTS_IMPLEMENTATION
#include "rlights.h"

using json = nlohmann::json;

struct DrawableElement
{
	uptr<Mesh> mesh;
	Matrix worldMatrix;

};

class EditorRaylib3D
{

public:
	EditorRaylib3D();
	~EditorRaylib3D();

	void Init(float const& width, float const& height);
	void Render();
	void Update(float deltaTime);
	void UpdateDisplay(Node* pNode);
	void Shutdown();

	void AddDrawableObject(std::string const& name,Node* jsonObject);
	void UpdateDrawableElement(Node* pNode);
	void RemoveDrawableElement(std::string const& elementName);

private:
	void DrawViewPort();
	
	void CheckIfIsDrawable(json element);

	void Instanciate3DMesh(std::string const& name, Node* nodeMesh3D);
	void InstanciateCollider3D();
	void InstanciateLight();

	Matrix FindParentWorldMatrix(Node* pNode);


	Matrix ConvertGLMValuesToRaylibMat(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot);

private:
	// List of Meshs will depends on NodeMesh for vertices later
	
	Camera3D m_camera;
	Material m_defaultMaterial;

	std::map<std::string, uptr<DrawableElement>> m_loadedMeshs;
};

#endif // __EDITOR_RAYLIB3D__H_