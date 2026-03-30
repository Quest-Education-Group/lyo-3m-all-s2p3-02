
class NodeAudioListener::Proxy : public Node::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : Node::Proxy(node) {}

	void SetListenerPosition(ma_vec3f position) { return m_pNode->SetListenerPosition(position); }
	ma_vec3f GetListenerPosition() { return m_pNode->GetListenerPosition(); }

	void SetListenerDirection(ma_vec3f position) { return m_pNode->SetListenerDirection(position); }
	ma_vec3f GetListenerDirection() { return m_pNode->GetListenerDirection(); }

private:
	NodeAudioListener* m_pNode;
};

BindProxy(NodeAudioListener::Proxy,
	return binder.BindClass<NodeAudioListener::Proxy>("nodeaudiolistener",
		"SetListenerPosition", BIND(SetListenerPosition),
		"GetListenerPosition", BIND(GetListenerPosition),
		"SetListenerDirection", BIND(SetListenerDirection),
		"GetListenerDirection", BIND(GetListenerDirection)
	);
)

REGISTER_PROXY(NodeAudioListener::Proxy::ProxyBinding, NodeAudioListenerProxy);