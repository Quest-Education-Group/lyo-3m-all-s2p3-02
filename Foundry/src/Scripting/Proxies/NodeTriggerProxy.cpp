#include "Nodes/NodeTrigger.h"

NodeTrigger::Proxy::Proxy(Node& node) : Node3D::Proxy(node), m_pNodeTrigger(static_cast<NodeTrigger*>(&node))
{
    m_pNodeTrigger->OnTriggerEnter += [&](NodeRigidBody const& rb){  OnTriggerEnter(static_cast<NodeRigidBody::Proxy&>(rb.GetNodeProxy())); };
    m_pNodeTrigger->OnTriggerStay  += [&](NodeRigidBody const& rb){  OnTriggerStay( static_cast<NodeRigidBody::Proxy&>(rb.GetNodeProxy())); };
    m_pNodeTrigger->OnTriggerLeave += [&](NodeRigidBody const& rb){  OnTriggerLeave(static_cast<NodeRigidBody::Proxy&>(rb.GetNodeProxy())); };
}
