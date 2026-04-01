#include "Nodes/NodeCamera.h"

#include "MathUtils.h"
#include "Nodes/NodeViewport.h"
#include "Servers/GraphicServer.h"

NodeCamera::NodeCamera(std::string const &name) : Node3D(name)
{
    SetFOV(45);
    m_camera.SetWorldUp({0.0f, 1.0f, 0.0f});
    OnHierarchyChanged += [&](){ TryAttachToViewport(); };

    m_camera.SetYaw(-90);
    m_camera.SetPosition({0.0f, 0.0f, 50.0f});
    m_camera.UpdateVectors();
    //m_camera.SetPitch(m_transform.GetPitch());
    //m_camera.SetRoll(m_transform.GetRoll());
}

void NodeCamera::OnUpdate(double delta)
{
    bool need_update = IsTransformDirty();
    Node3D::OnUpdate(delta);

    if (need_update)
    {
        m_camera.SetYaw(-90);
        //m_camera.SetPitch(m_transform.GetPitch());
        //m_camera.SetRoll(m_transform.GetRoll());
        m_camera.SetPosition({0.0f, 0.0f, 5.0f});
        m_camera.UpdateVectors();
    }
}

void NodeCamera::Serialize(SerializedObject &datas) const
{
    Node3D::Serialize(datas);
}

void NodeCamera::Deserialize(SerializedObject const &datas)
{
    Node3D::Deserialize(datas);
}

ISerializable* NodeCamera::CreateInstance()
{
    return CreateNode<NodeCamera>("NodeCamera").release();
}

void NodeCamera::TryAttachToViewport()
{
    if ( const auto viewport = FindFirstParentOfType<NodeViewport>())
        GraphicServer::AttachToViewport(this, &viewport->get());
}

void NodeCamera::UpdateCameraOwner(NodeViewport& newOwner)
{
    if (m_pCurrentViewport) m_pCurrentViewport->SetCamera(nullptr);
    m_pCurrentViewport = &newOwner;
    newOwner.SetCamera(this);
}
