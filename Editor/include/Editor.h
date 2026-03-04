#ifndef __EDITOR_H
#define __EDITOR_H

#include <raylib.h>
#include <raymath.h>

#include <imgui.h>
#include <imfilebrowser.h>

#include <rlImGui.h>
#include <rlImGuiColors.h>

#include <Node.h>
#include <Define.h>

class Editor
{
public:
	Editor();
	~Editor();

	void Init();
	void Run();
	void Shutdown();

private:
	// Main Loop
	void Update(float deltaTime);
	void Render3D();
	void RenderUI();

	// ImGui Panels
	void DrawHierarchyPanel();
	void DrawInspectorPanel();
	void DrawMenuBar();
	void DrawViewport3D();

	// Scene Management
	void CreateNode(std::string const& name, Node* parent = nullptr);
	void DeleteNode(Node* node);
	void SelectNode(Node* node);

	// Recursive helpers for hierarchy
	void DrawNodeTree(Node& node);

	// Load/Save
	void LoadScene(std::string const& path);
	void SaveScene(std::string const& path);

	// View Root Management
	void SetViewRoot(Node* node);
	void ResetViewRoot();

	// Popup for naming a node
	void ShowCreateNodePopup();

	void ShowCreateChildPopup(Node* parent);
	void ShowCreateSiblingPopup(Node* sibling);

	// Popup for save/load

	void ShowSaveScenePopup();
	void ShowLoadScenePopup();

private:
	// Editor State
	bool m_running = false;
	int m_screenWidth = 1900;
	int m_screenHeight = 900;

	// Scene
	uptr<Node> m_sceneRoot = nullptr;
	Node* m_selectedNode = nullptr;
	Node* m_viewRoot = nullptr; // Current view root

	// Creation Popup
	bool m_showCreatePopup = false;
	bool m_showCreateChildPopup = false;
	bool m_showCreateSiblingPopup = false;
	Node* m_pendingParent = nullptr;
	Node* m_pendingSibling = nullptr;
	char m_nodeNameBuffer[128] = "";

	// Popup save/load
	bool m_showSavePopup = false;
	bool m_showLoadPopup = false;
	char m_sceneNameBuffer[256] = "scene.json";
	char m_scenePathBuffer[512] = "";

	ImGui::FileBrowser m_saveBrowser;
	ImGui::FileBrowser m_loadBrowser;

	// 3D Camera
	Camera3D m_camera = {};

	// UI States
	bool m_showHierarchy = true;
	bool m_showInspector = true;
	bool m_showViewport = true;
};

#endif // __EDITOR_H