
class NodeRigidBody::Proxy : public Node::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : Node::Proxy(node) {}
	void Test() {};

private:
	NodeRigidBody* m_pNode;
};

BindProxy(NodeRigidBody::Proxy,
	return binder.BindClass<NodeRigidBody::Proxy>("noderigidbody",
		"Test", BIND(Test));
)

REGISTER_PROXY(NodeRigidBody::Proxy::ProxyBinding, NodeRigidBodyProxy);