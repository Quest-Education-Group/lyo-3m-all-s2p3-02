#include "Nodes/NodeAudioListener.h"

NodeAudioListener::NodeAudioListener(std::string const& name) : Node(name)
{
}

void NodeAudioListener::SetListenerPosition(ma_vec3f position)
{
	ma_engine& soundEngine = AudioServer::GetSoundEngine();

	ma_engine_listener_set_position(&soundEngine, 0, position.x, position.y, position.z);
}

ma_vec3f NodeAudioListener::GetListenerPosition()
{
	ma_engine& soundEngine = AudioServer::GetSoundEngine();

	return ma_engine_listener_get_position(&soundEngine, 0); //TODO: index0 could cause problem, need to automatize index
}

void NodeAudioListener::SetListenerDirection(ma_vec3f position)
{
	ma_engine& soundEngine = AudioServer::GetSoundEngine();

	ma_engine_listener_set_direction(&soundEngine, 0, position.x, position.y, position.z);
}

ma_vec3f NodeAudioListener::GetListenerDirection()
{
	ma_engine& soundEngine = AudioServer::GetSoundEngine();

	return ma_engine_listener_get_direction(&soundEngine, 0);
}

void NodeAudioListener::OnUpdate(double delta)
{
	Node::OnUpdate(delta);
}

ISerializable* NodeAudioListener::CreateInstance()
{
	return CreateNode<NodeAudioListener>("NodeAudioListener").release();
}