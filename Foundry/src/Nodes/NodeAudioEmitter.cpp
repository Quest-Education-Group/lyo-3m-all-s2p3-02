#include "Nodes/NodeAudioEmitter.h"

NodeAudioEmitter::NodeAudioEmitter(std::string const& name) : Node(name)
{
}

bool NodeAudioEmitter::Load(const char* filePath, AudioChannel* channel)
{
    ma_engine& soundEngine = AudioServer::GetSoundEngine();

    if (ma_sound_init_from_file(&soundEngine, filePath, 0, &channel->soundGroup, NULL, &m_sound) != MA_SUCCESS)
    {
        printf("Failed to load sound: %s\n", filePath);
        return false;
    }

    return true;
}

void NodeAudioEmitter::Play()
{
    if (!m_isPlaying) 
    {
        ma_sound_start(&m_sound);
        m_isPlaying = true;
    } 
}

void NodeAudioEmitter::Stop()
{
    if (m_isPlaying)
    {
        ma_sound_stop(&m_sound);
        m_isPlaying = false;
    }
}

void NodeAudioEmitter::SetLoop(bool value)
{
    ma_sound_set_looping(&m_sound, value);
}

void NodeAudioEmitter::SetSourcePosition(ma_vec3f position)
{
    ma_sound_set_position(&m_sound, position.x, position.y, position.z);
}

ma_vec3f NodeAudioEmitter::GetSourcePosition()
{
    return ma_sound_get_position(&m_sound);
}

void NodeAudioEmitter::OnUpdate(double delta)
{
	Node::OnUpdate(delta);
}

ISerializable* NodeAudioEmitter::CreateInstance()
{
	return CreateNode<NodeAudioEmitter>("NodeAudioEmitter").release();
}