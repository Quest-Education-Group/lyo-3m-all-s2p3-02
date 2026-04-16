#ifndef FOUNDRY_NODETRIGGER__H_
#define FOUNDRY_NODETRIGGER__H_

#include "Node3D.h"
#include "CollisionData.h"

#include <reactphysics3d/reactphysics3d.h>

class NodeRigidBody;

class NodeTrigger : public Node3D
{
public:
    class Proxy;

    NodeTrigger(std::string const& name);

    void Serialize(SerializedObject &datas) const override;
    void Deserialize(SerializedObject const &datas) override;
    void AttachScriptDeserialize(uptr<LuaScriptInstance>& script) override;
    uptr<Node> Clone() override;

    void OnUpdate(double delta) override;

    static ISerializable* CreateInstance();

    CollisionData const& AsCollisionData() const { return m_collisionData; }

    Event<void(NodeRigidBody const& body)> OnTriggerEnter;
    Event<void(NodeRigidBody const& body)> OnTriggerStay;
    Event<void(NodeRigidBody const& body)> OnTriggerLeave;

private:
    rp3d::RigidBody* m_pRigidBody;
    rp3d::Collider* m_pCollider;
    CollisionData m_collisionData {this, CollisionData::TRIGGER};
};

REGISTER_ISERIALIZABLE(NodeTrigger, NodeTrigger::CreateInstance);

#include "Scripting/Proxies/NodeTriggerProxy.inl"

#endif