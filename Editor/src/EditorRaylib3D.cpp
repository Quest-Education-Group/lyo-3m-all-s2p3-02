#include "EditorRaylib3D.h"


EditorRaylib3D::EditorRaylib3D(){}
EditorRaylib3D::~EditorRaylib3D(){}

void EditorRaylib3D::InitWindow(float const& width, float const& height)
{
	rl::SetConfigFlags(rl::FLAG_MSAA_4X_HINT | rl::FLAG_VSYNC_HINT | rl::FLAG_WINDOW_RESIZABLE);
	rl::InitWindow(width, height, "Foundry Editor");
	rl::SetTargetFPS(144);

	// Static Cam 
	m_camera.position = { 10.0f, 10.0f, 10.0f };
	m_camera.target = { 0.0f, 0.0f, 0.0f };
	m_camera.up = { 0.0f, 1.0f, 0.0f };
	m_camera.fovy = 45.0f;
	m_camera.projection = rl::CAMERA_PERSPECTIVE;
}

void EditorRaylib3D::LoadDrawableObject(json const& jsonObject)
{
	CheckIfIsDrawable(jsonObject);
}

void EditorRaylib3D::Update(float deltaTime)
{
	if (rl::IsMouseButtonDown(rl::MOUSE_BUTTON_RIGHT)) {
		UpdateCamera(&m_camera, rl::CAMERA_FREE);
	}
	if (rl::IsMouseButtonDown(rl::MOUSE_BUTTON_MIDDLE)) {
		UpdateCamera(&m_camera, rl::CAMERA_ORBITAL);
	}
}

void EditorRaylib3D::Render()
{
	rl::BeginMode3D(m_camera);
	DrawViewPort();

	//json nFinder = m_jsonElementFromRoot["Root"];
	//
	//CheckIfIsDrawable(nFinder);

	rl::EndMode3D();
}

void EditorRaylib3D::DrawViewPort()
{
	rl::DrawGrid(20, 1.0f);
	rl::DrawLine3D({ 0, 0, 0 }, { 500, 0, 0 }, rl::RED);
	rl::DrawLine3D({ 0, 0, 0 }, { 0, 500, 0 }, rl::GREEN);
	rl::DrawLine3D({ 0, 0, 0 }, { 0, 0, 500 }, rl::BLUE);
	rl::DrawLine3D({ 0, 0, 0 }, { -500, 0, 0 }, rl::RED);
	rl::DrawLine3D({ 0, 0, 0 }, { 0, -500, 0 }, rl::GREEN);
	rl::DrawLine3D({ 0, 0, 0 }, { 0, 0,-500 }, rl::BLUE);
}

void EditorRaylib3D::CheckIfIsDrawable(json element)
{
	if (element["TYPE"] == "class Node3D")
	{
		for (uint32 i = 0; i < element["Children"].size(); i++)
		{
			// CreateWorldMatrix From Values
			CheckIfIsDrawable(element["Children"][i]);
		}
		return;
	}
	else if (element["TYPE"] == "class NodeLight")
	{
		DrawLight();
	}
	else if (element["TYPE"] == "class NodeMesh3D")
	{
		// Recupérer les vertices 
		Draw3DMesh(element);
	}
	else if (element["TYPE"] == "class NodeCollider3D")
	{
		//DrawCollider3D(m_loadedMeshs[element["DATAS"]["m_name"]]);
	}

	for (uint32 i = 0; i < element["Children"].size(); i++)
	{
		CheckIfIsDrawable(element["Children"][i]);
	}
}

void EditorRaylib3D::Draw3DMesh(json& nodeMesh3D)
{
	rl::Mesh m_mesh = {};

	//m_mesh.vertices = ...;
	//m_mesh.indices = ...;
	//m_mesh.vertexCount = m_mesh.vertices.size();
	//m_mesh.triangleCount = m_mesh.indices.size() / 3;

	rl::UploadMesh(&m_mesh,false);
}

void EditorRaylib3D::DrawCollider3D()
{
}

void EditorRaylib3D::DrawLight()
{
}


void EditorRaylib3D::Shutdown()
{
}