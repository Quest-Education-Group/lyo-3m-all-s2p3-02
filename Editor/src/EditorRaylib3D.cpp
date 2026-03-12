#include "EditorRaylib3D.h"

#include <Nodes/AllNodes.h>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace rl
{
	#include <raymath.h>
}

#include <rlgl.h>

EditorRaylib3D::EditorRaylib3D(){}
EditorRaylib3D::~EditorRaylib3D()
{}

void EditorRaylib3D::Init(float const& width, float const& height)
{
	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(width, height, "Foundry Editor");
	
	SetTargetFPS(144);

	// Static Cam 
	m_camera.position = { 10.0f, 10.0f, 10.0f };
	m_camera.target = { 0.0f, 0.0f, 0.0f };
	m_camera.up = { 0.0f, 1.0f, 0.0f };
	m_camera.fovy = 45.0f;
	m_camera.projection = CAMERA_PERSPECTIVE;

	m_defaultMaterial = LoadMaterialDefault();
}

void EditorRaylib3D::Update(float deltaTime)
{
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		UpdateCamera(&m_camera, CAMERA_FREE);
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
		UpdateCamera(&m_camera, CAMERA_ORBITAL);
	}
}

void EditorRaylib3D::UpdateDisplay(Node* pNode)
{
	UpdateDrawableElement(pNode);
	for (uint32 i = 0; i < pNode->GetChildCount(); ++i)
	{
		UpdateDisplay(&pNode->GetChild(i));
	}
}

void EditorRaylib3D::AddDrawableObject(std::string const& name, Node* pNode)
{
	if (dynamic_cast<Node3D*>(pNode) != nullptr) // TestTemp
	{
		Instanciate3DMesh(name, pNode);
	}

	//if (dynamic_cast<NodeLight*>(pNode) != nullptr)
	//{
	//	//DrawLight();
	//}
	//else if (dynamic_cast<NodeMesh3D*>(pNode) != nullptr)
	//{
	//	Instanciate3DMesh(name, jsonObject);
	//}
	//else if (dynamic_cast<NodeCollider3D*>(pNode) != nullptr)
	//{
	//	//DrawCollider3D(m_loadedMeshs[element["DATAS"]["m_name"]]);
	//}
}

Matrix EditorRaylib3D::FindParentWorldMatrix(Node* pNode)
{
	Node3D* pNode3D = nullptr; // Node3D
	Matrix world = rl::MatrixIdentity();
	Node* pParent = pNode;

	pNode3D = dynamic_cast<Node3D*>(pNode);

	while (pNode3D == nullptr)
	{
		pParent = pParent->GetParent();
		if (pParent == nullptr) break;
		pNode3D = dynamic_cast<Node3D*>(pParent);
	}
	
	if (pNode3D != nullptr)
	{
		glm::mat4 m1 = pNode3D->GetWorldMatrix();
		world = {
			m1[0][0], m1[1][0], m1[2][0], m1[3][0],
			m1[0][1], m1[1][1], m1[2][1], m1[3][1],
			m1[0][2], m1[1][2], m1[2][2], m1[3][2],
			m1[0][3], m1[1][3], m1[2][3], m1[3][3]
		};
	}

	return world;
}

void EditorRaylib3D::UpdateDrawableElement(Node* pNode)
{
	if (dynamic_cast<Node3D*>(pNode) != nullptr) // TestTemp
	{
		m_loadedMeshs[pNode->GetName()].get()->worldMatrix = FindParentWorldMatrix(pNode);
	}
}

void EditorRaylib3D::RemoveDrawableElement(std::string const& elementName)
{
	 if (m_loadedMeshs.contains(elementName))
	 {
		 UnloadMesh(*m_loadedMeshs[elementName]->mesh.release());
		 m_loadedMeshs.erase(elementName);
	 }
}


void EditorRaylib3D::Instanciate3DMesh(std::string const& name, Node* pNodeMesh3D) // NodeMesh3D
{
	if (m_loadedMeshs.find(name) != m_loadedMeshs.end())
	{
		// ERROR
	}
	else
	{
		Mesh m_mesh = GenMeshCube(1, 1, 1);
		// Custom Mesh with Mesh3D
		UploadMesh(&m_mesh, false);
		m_loadedMeshs[name] = std::make_unique<DrawableElement>();
		m_loadedMeshs[name].get()->mesh = std::make_unique<Mesh>(m_mesh); // GetMesh
		m_loadedMeshs[name].get()->worldMatrix = FindParentWorldMatrix(pNodeMesh3D);
	}
}


void EditorRaylib3D::InstanciateCollider3D()
{
}

void EditorRaylib3D::InstanciateLight()
{
}


void EditorRaylib3D::Render()
{
	BeginMode3D(m_camera);
	DrawViewPort();

	for (std::map<std::string, uptr<DrawableElement>>::iterator it  = m_loadedMeshs.begin(); it != m_loadedMeshs.end(); it++)
	{
		DrawMesh(*it->second.get()->mesh.get(), m_defaultMaterial, it->second.get()->worldMatrix);
		//Matrix m = it->second.get()->worldMatrix;
		//Transform gTransform = GizmoIdentity();
		//DrawGizmo3D(GIZMO_TRANSLATE, &gTransform);
	}

	EndMode3D();
}

void EditorRaylib3D::DrawViewPort()
{
	DrawGrid(20, 1.0f);
	DrawLine3D({ 0, 0, 0 }, { 500, 0, 0 }, RED);
	DrawLine3D({ 0, 0, 0 }, { 0, 500, 0 }, GREEN);
	DrawLine3D({ 0, 0, 0 }, { 0, 0, 500 }, BLUE);
	DrawLine3D({ 0, 0, 0 }, { -500, 0, 0 }, RED);
	DrawLine3D({ 0, 0, 0 }, { 0, -500, 0 }, GREEN);
	DrawLine3D({ 0, 0, 0 }, { 0, 0,-500 }, BLUE);
}


void EditorRaylib3D::Shutdown()
{
}
