#ifndef FOUNDRY_NODEAUDIOLISTENER__H_
#define FOUNDRY_NODEAUDIOLISTENER__H_

#include "Node.h"
#include "Servers/AudioServer.h"
#include "Transform3D.h"

class NodeAudioListener : public Node
{
public:
	class Proxy;

	NodeAudioListener(std::string const& name);
	~NodeAudioListener() override = default;

	void SetListenerPosition(glm::vec3 position);
	glm::vec3 GetListenerPosition();

	void SetListenerDirection(glm::vec3 position);
	glm::vec3 GetListenerDirection();

	virtual void OnUpdate(double delta) override;

	static ISerializable* CreateInstance();

protected:

private:

};

REGISTER_ISERIALIZABLE(NodeAudioListener, NodeAudioListener::CreateInstance);

#include "Scripting/Proxies/NodeAudioListenerProxy.inl"

#endif