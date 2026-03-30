#ifndef FOUNDRY_NODEAUDIOEMITTER__H_
#define FOUNDRY_NODEAUDIOEMITTER__H_

#include "Node.h"
#include "Servers/AudioServer.h"

class NodeAudioEmitter : public Node
{
public:
	class Proxy;

	NodeAudioEmitter(std::string const& name);
	~NodeAudioEmitter() override = default;

	bool Load(const char* filePath, AudioChannel* channel);

	void Play();
	void Stop();
	void SetLoop(bool value);

	void SetSourcePosition(ma_vec3f position);
	ma_vec3f GetSourcePosition();

	bool IsPlaying() { return m_isPlaying; };

	virtual void OnUpdate(double delta) override;

	static ISerializable* CreateInstance();

protected:
	ma_sound m_sound{};
	bool m_isPlaying = false;
private:

};

REGISTER_ISERIALIZABLE(NodeAudioEmitter, NodeAudioEmitter::CreateInstance);

#include "Scripting/Proxies/NodeAudioEmitterProxy.inl"

#endif