#ifndef GRAPHIC_SERVER__H_
#define GRAPHIC_SERVER__H_

#include "Server.hpp"
#include "Shader.h"
#include "Nodes/NodeViewport.h"
#include "Nodes/NodeWindow.h"

class Window;

template <>
struct Command<class GraphicServer>
{
    enum class CmdType { LOADSHADERS, SETUPVIEWPORT, OPENWINDOW, CLEAR, PRESENT } Type;
    union
    {
        NodeWindow* pNodeWindow = nullptr;
        NodeViewport* pNodeViewport;
    };
};

class GraphicServer : public Server<GraphicServer>
{
public:
    using CommandType = Command<GraphicServer>::CmdType;

    static void OpenWindow(NodeWindow* pWindow);
    static void Present(NodeWindow* pWindow);
    static void Clear(NodeWindow* pWindow);
    static void LoadShaderPrograms(NodeViewport* pViewport);

    static Shader& GetGeoVert() { return Instance().m_geoVert; }
    static Shader& GetGeoFrag() { return Instance().m_geoFrag; }
    static Shader& GetLightVert() { return Instance().m_lightVert; }
    static Shader& GetLightFrag() { return Instance().m_lightFrag; }

private:
    void FlushCommandsImpl() override;
    void BuildTasksImpl(TaskGraph& graph) override;
	void OnInitialize() override;
    void OnUnInitialize() override;
    void LoadShader();

private:
    //default shaders
    Program m_geoProgram;
    Program m_lightProgram;

    Shader m_geoVert {ShaderType::TYPE_VERTEX};
    Shader m_geoFrag {ShaderType::TYPE_FRAGMENT};

    Shader m_lightVert {ShaderType::TYPE_VERTEX};
    Shader m_lightFrag {ShaderType::TYPE_FRAGMENT};
};

#endif
