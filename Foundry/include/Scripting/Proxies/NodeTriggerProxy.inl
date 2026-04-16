#include "Nodes/NodeRigidBody.h"

class NodeTrigger::Proxy : public Node3D::Proxy
{
public:
    struct ProxyBinding;

    Proxy(Node& node);

    std::function<void(NodeRigidBody::Proxy& rb)> OnTriggerEnter;
    std::function<void(NodeRigidBody::Proxy& rb)> OnTriggerStay;
    std::function<void(NodeRigidBody::Proxy& rb)> OnTriggerLeave;

private:
    NodeTrigger* m_pNodeTrigger;
};

BindProxy(NodeTrigger::Proxy,
    return binder.BindClass<NodeTrigger::Proxy>("nodetrigger",
        sol::base_classes, sol::bases<Node::Proxy, Node3D::Proxy>(),
        sol::meta_function::garbage_collect, BIND(GCNodeProxy),
        sol::meta_function::new_index, StoreUserData(),
        sol::meta_function::index, LoadUserData(),
        "OnTriggerEnter", &NodeTrigger::Proxy::OnTriggerEnter,
        "OnTriggerStay", &NodeTrigger::Proxy::OnTriggerStay,
        "OnTriggerLeave", &NodeTrigger::Proxy::OnTriggerLeave
    );
)