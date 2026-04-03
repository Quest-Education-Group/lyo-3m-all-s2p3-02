
class NodeBoxCollider::Proxy : public NodeCollider::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : NodeCollider::Proxy(node) {}

	static Proxy* CreateNodeBoxColliderProxy(std::string const& name);

	void SetShape(const glm::vec3& halfExtents) { m_pNode->SetShape(halfExtents); }
private:
	NodeBoxCollider* m_pNode;
};

BindProxy(NodeBoxCollider::Proxy,
	binder.BindFunction("CreateNodeBoxCollider", &NodeBoxCollider::Proxy::CreateNodeBoxColliderProxy);
	return binder.BindClass<NodeBoxCollider::Proxy>("nodeboxcollider",
		"SetShape", BIND(SetShape)
	);
)

REGISTER_PROXY(NodeBoxCollider::Proxy::ProxyBinding, NodeBoxColliderProxy);


class NodeSphereCollider::Proxy : public NodeCollider::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : NodeCollider::Proxy(node) {}

	static Proxy* CreateNodeSphereColliderProxy(std::string const& name);

	void SetShape(float radius) { m_pNode->SetShape(radius); }
private:
	NodeSphereCollider* m_pNode;
};

BindProxy(NodeSphereCollider::Proxy,
		binder.BindFunction("CreateNodeSphereCollider", &NodeSphereCollider::Proxy::CreateNodeSphereColliderProxy);
	return binder.BindClass<NodeSphereCollider::Proxy>("nodespherecollider",
		"SetShape", BIND(SetShape)
	);
)

REGISTER_PROXY(NodeSphereCollider::Proxy::ProxyBinding, NodeSphereColliderProxy);


class NodeCapsuleCollider::Proxy : public NodeCollider::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : NodeCollider::Proxy(node) {}

	static Proxy* CreateNodeCapsuleColliderProxy(std::string const& name);

	void SetShape(float radius, float height) { m_pNode->SetShape(radius, height); }
private:
	NodeCapsuleCollider* m_pNode;
};

BindProxy(NodeCapsuleCollider::Proxy,
	binder.BindFunction("CreateNodeCapsuleCollider", &NodeCapsuleCollider::Proxy::CreateNodeCapsuleColliderProxy);
	return binder.BindClass<NodeCapsuleCollider::Proxy>("nodecapsulecollider",
		"SetShape", BIND(SetShape)
	);
)

REGISTER_PROXY(NodeCapsuleCollider::Proxy::ProxyBinding, NodeCapsuleColliderProxy);