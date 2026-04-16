#include "Nodes/NodeTrigger.h"

#include "Servers/PhysicsServer.h"


NodeTrigger::NodeTrigger(std::string const& name)  : Node3D(name)
{
    rp3d::Transform reactTr;
    //IF PROBLEM WITH TRIGGER CHECK HERE BROTHER
    reactTr.setFromOpenGL(&m_worldTransform[0][0]);
    m_pRigidBody = PhysicsServer::GetPhysicsWorld().createRigidBody(reactTr);
    m_pRigidBody->setType(rp3d::BodyType::STATIC);

    glm::vec3 scale = m_transform.GetScale();
    rp3d::Vector3 vec {scale.x / 2.0f, scale.y / 2.0f, scale.z / 2.0f};
    rp3d::BoxShape* boxShape = PhysicsServer::GetPhysicsCommon().createBoxShape(vec);

    rp3d::Transform transform = rp3d::Transform::identity();
    m_pCollider = m_pRigidBody->addCollider(boxShape, transform);
    m_pCollider->setIsTrigger(true);
}

void NodeTrigger::Serialize(SerializedObject& datas) const
{
    Node3D::Serialize(datas);
    datas.SetType("NodeTrigger");
}

void NodeTrigger::Deserialize(SerializedObject const& datas)
{
    Node3D::Deserialize(datas);
}

void NodeTrigger::AttachScriptDeserialize(uptr<LuaScriptInstance>& script)
{
    AttachScript<NodeTrigger>(script, *this);
}

ISerializable* NodeTrigger::CreateInstance()
{
    return Node::CreateNode<NodeTrigger>("NodeTrigger").release();
}

uptr<Node> NodeTrigger::Clone()
{
    uptr<NodeTrigger> clone = Node::CreateNode<NodeTrigger>(GetName());

    SerializedObject datas;
    Serialize(datas);
    clone->Deserialize(datas);

    return clone;
}

void NodeTrigger::OnUpdate(double delta)
{
    bool need_update = IsTransformDirty();
    Node3D::OnUpdate(delta);

    if (need_update)
    {
        rp3d::Transform reactTr;
        reactTr.setFromOpenGL(&m_worldTransform[0][0]);
        m_pRigidBody->setTransform(reactTr);
    }
}