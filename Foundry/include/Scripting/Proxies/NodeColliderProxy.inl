

class NodeCollider::Proxy : public Node::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : Node::Proxy(node) {}
	void Test();

private:
	NodeCollider* m_pNode;
};

BindProxy(NodeCollider::Proxy,
	return binder.BindClass<NodeCollider::Proxy>("nodecollider",
		"Test", BIND(Test));
)

REGISTER_PROXY(NodeCollider::Proxy::ProxyBinding, NodeColliderProxy);