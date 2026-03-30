#include "Servers/GraphicServer.h"

#include "Nodes/NodeWindow.h"
#include "Nodes/NodeViewport.h"

void GraphicServer::OpenWindow(NodeWindow* pWindow)
{
    Instance().m_commands.push({CommandType::OPENWINDOW, pWindow});
}

void GraphicServer::Present(NodeWindow* pWindow)
{
    Instance().m_commands.push({CommandType::PRESENT, pWindow});
}

void GraphicServer::Clear(NodeWindow* pWindow)
{
    Instance().m_commands.push({CommandType::CLEAR, pWindow});
}

void GraphicServer::LoadShaderPrograms(NodeViewport* pViewport)
{
    Command<GraphicServer> cmd;
    cmd.Type = CommandType::SETUPVIEWPORT;
    cmd.pNodeViewport = pViewport;
    Instance().m_commands.push(cmd);
}

void GraphicServer::OnInitialize()
{
    Instance().m_commands.push({CommandType::LOADSHADERS, nullptr});
}

void GraphicServer::OnUnInitialize()
{
    m_geoVert.Unload();
    m_geoFrag.Unload();

    m_lightVert.Unload();
    m_lightFrag.Unload();
}

void GraphicServer::LoadShader()
{
    m_geoVert.Load("res/shaders/GBuffer.vert");
    m_geoFrag.Load("res/shaders/GBuffer.frag");

    m_lightVert.Load("res/shaders/LightPass.vert");
    m_lightFrag.Load("res/shaders/LightPass.frag");

    m_geoProgram.AddShader(&m_geoVert);
    m_geoProgram.AddShader(&m_geoFrag);
    m_geoProgram.Load();

    m_lightProgram.AddShader(&m_lightVert);
    m_lightProgram.AddShader(&m_lightFrag);
    m_lightProgram.Load();
}

void GraphicServer::BuildTasksImpl(TaskGraph& graph) {}

void GraphicServer::FlushCommandsImpl()
{
    while (m_commands.empty() == false)
    {
        auto& cmd = m_commands.front();
        switch (cmd.Type)
        {
            case CommandType::SETUPVIEWPORT:
                cmd.pNodeViewport->Setup();
                break;
            case CommandType::LOADSHADERS:
                LoadShader();
                break;
            case CommandType::OPENWINDOW:
                cmd.pNodeWindow->OpenWindow();
                break;
            case CommandType::CLEAR:
                cmd.pNodeWindow->ClearWindow();
                break;
            case CommandType::PRESENT:
                cmd.pNodeWindow->PresentWindow();
                break;
        }
        m_commands.pop();
    }
}
