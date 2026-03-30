#ifndef FOUNDRY_NODEAUDIOLISTENER__H_
#define FOUNDRY_NODEAUDIOLISTENER__H_

#include "Node.h"
#include "Servers/AudioServer.h"

class NodeAudioListener : public Node
{
public:
	class Proxy;

	NodeAudioListener(std::string const& name);
	~NodeAudioListener() override = default;

	void SetListenerPosition(ma_vec3f position);
	ma_vec3f GetListenerPosition();

	void SetListenerDirection(ma_vec3f position);
	ma_vec3f GetListenerDirection();

	virtual void OnUpdate(double delta) override;

	static ISerializable* CreateInstance();

protected:

private:

};

REGISTER_ISERIALIZABLE(NodeAudioListener, NodeAudioListener::CreateInstance);

#include "Scripting/Proxies/NodeAudioListenerProxy.inl"

#endif