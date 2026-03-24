#include "Nodes/NodeAudioEmitter.h"

NodeAudioEmitter::NodeAudioEmitter(std::string const& name) : Node(name)
{

}

void NodeAudioEmitter::AudioSetFile(const char* filePath)
{
	m_audio.SetAudioFile(filePath);
}

void NodeAudioEmitter::AudioPlay()
{
	m_audio.Play();
}

void NodeAudioEmitter::AudioStop()
{
	m_audio.Stop();
}

void NodeAudioEmitter::AudioSetLoop(bool value)
{
	m_audio.SetLoop(value);
}

void NodeAudioEmitter::OnUpdate(double delta)
{
	Node::OnUpdate(delta);
	m_audio.Update();
}

ISerializable* NodeAudioEmitter::CreateInstance()
{
	return CreateNode<NodeAudioEmitter>("NodeAudioEmitter").release();
}