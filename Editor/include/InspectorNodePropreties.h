#ifndef EDITOR_INSPECTOR_NODE_PROPERTIES_H__
#define EDITOR_INSPECTOR_NODE_PROPERTIES_H__

#include <string>
#include <Serialization/json.hpp>
#include <map>

class Node;
class EditorImGui;

using json = nlohmann::json;

class InspectorNodePropreties
{
public:
    InspectorNodePropreties(EditorImGui* pImGuiEditor) : m_pImguiEditor(pImGuiEditor) {}

    void DrawWindow(bool windowState, Node* pSelectedNode);

    void SetWindow(int width, int height) { m_screenWidth = width; m_screenHeight = height; }

private:
    bool DrawDatas(json& publicDataJson);

private:
    EditorImGui* m_pImguiEditor = nullptr;

    int m_screenWidth = 0;
    int m_screenHeight = 0;

    int m_windowWidth = 0;
    int m_windowHeight = 0;

    bool m_isOpen = false;

    Node* m_pSelectedNode = nullptr;

    json m_currentDatas;
};

#endif //!EDITOR_INSPECTOR_NODE_PROPERTIES_H__