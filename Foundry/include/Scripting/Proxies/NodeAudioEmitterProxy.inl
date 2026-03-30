
class NodeAudioEmitter::Proxy : public Node::Proxy
{
public:
	struct ProxyBinding;

	Proxy(Node& node) : Node::Proxy(node) {}

	bool Load(const char* filePath, AudioChannel* channel) { return m_pNode->Load(filePath, channel); }

	void Play() { return m_pNode->Play(); }
	void Stop() { return m_pNode->Stop(); }
	void SetLoop(bool value) { return m_pNode->SetLoop(value); }

	void SetSourcePosition(ma_vec3f position) { return m_pNode->SetSourcePosition(position); }
	ma_vec3f GetSourcePosition() { return m_pNode->GetSourcePosition(); }

	bool IsPlaying() { return m_pNode->IsPlaying(); }

private:
	NodeAudioEmitter* m_pNode;
};

BindProxy(NodeAudioEmitter::Proxy,
	return binder.BindClass<NodeAudioEmitter::Proxy>("nodeaudioemitter",
		"Load", BIND(Load),
		"Play", BIND(Play),
		"Stop", BIND(Stop),
		"SetLoop", BIND(SetLoop),
		"SetSourcePosition", BIND(SetSourcePosition),
		"GetSourcePosition", BIND(GetSourcePosition),
		"IsPlaying", BIND(IsPlaying)
	);
)

REGISTER_PROXY(NodeAudioEmitter::Proxy::ProxyBinding, NodeAudioEmitterProxy);