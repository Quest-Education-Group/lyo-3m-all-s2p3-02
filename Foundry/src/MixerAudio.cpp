#include "MixerAudio.h"
#include <algorithm>

bool MixerAudio::Init()
{
    return true;
}

void MixerAudio::Shutdown()
{
    for (auto& [ch, entry] : m_delays) 
    {
        if (entry.active) 
        {
            ma_delay_node_uninit(&entry.node, NULL);
        }
    }

    m_delays.clear();
}

void MixerAudio::AddDelay(AudioChannel* channel, float delaySeconds, float decay, float wet)
{
    if (!channel || m_delays.count(channel)) return;

    ma_engine& engine = AudioServer::GetSoundEngine();

    ma_uint32 sampleRate = ma_engine_get_sample_rate(&engine);
    ma_uint32 frames = (ma_uint32)(delaySeconds * sampleRate);

    ma_delay_node_config cfg = ma_delay_node_config_init(2, sampleRate, frames, decay);
    DelayEntry entry{};

    if (ma_delay_node_init(ma_engine_get_node_graph(&engine), &cfg, NULL, &entry.node) != MA_SUCCESS)
    {
        printf("[MixerAudio] AddDelay failed on '%s'\n", channel->name.c_str());
        return;
    }

    ma_delay_node_set_wet(&entry.node, wet);
    ma_delay_node_set_dry(&entry.node, 1.0f);

    ma_node_attach_output_bus(&channel->soundGroup, 0, &entry.node, 0);
    ma_node_attach_output_bus(&entry.node, 0, ma_engine_get_endpoint(&engine), 0);

    entry.active = true;
    m_delays[channel] = std::move(entry);
}

void MixerAudio::SetDelayWet(AudioChannel* channel, float wet)
{
    auto it = m_delays.find(channel);
    if (it == m_delays.end() || !it->second.active) return;
    ma_delay_node_set_wet(&it->second.node, std::clamp(wet, 0.0f, 1.0f));
}

void MixerAudio::RemoveDelay(AudioChannel* channel)
{
    auto it = m_delays.find(channel);
    if (it == m_delays.end()) return;
    if (it->second.active) ma_delay_node_uninit(&it->second.node, NULL);

    ma_node_attach_output_bus(&channel->soundGroup, 0, ma_engine_get_endpoint(&AudioServer::GetSoundEngine()), 0);

    m_delays.erase(it);
}

void MixerAudio::FadeTo(AudioChannel* channel, float targetVolume, float durationSeconds)
{
    if (!channel || durationSeconds <= 0.0f) return;

    float current = ma_sound_group_get_volume(&channel->soundGroup);

    // Met à jour un fade existant sur ce channel s'il y en a un
    for (auto& f : m_fades)
    {
        if (f.channel == channel) 
        {
            f.current = current;
            f.target = std::clamp(targetVolume, 0.0f, 1.0f);
            f.speed = fabsf(f.target - f.current) / durationSeconds;
            f.active = true;
            return;
        }
    }

    FadeEntry f{};
    f.channel = channel;
    f.current = current;
    f.target = std::clamp(targetVolume, 0.0f, 1.0f);
    f.speed = fabsf(f.target - f.current) / durationSeconds;
    f.active = true;
    m_fades.push_back(f);
}

void MixerAudio::Update(float delta)
{
    for (auto& f : m_fades)
    {
        if (!f.active) continue;

        float dir = (f.target > f.current) ? 1.0f : -1.0f;
        f.current += dir * f.speed * delta;

        if ((dir > 0.0f && f.current >= f.target) || (dir < 0.0f && f.current <= f.target))
        {
            f.current = f.target;
            f.active = false;
        }

        AudioServer::SetGroupVolume(f.channel, f.current);
    }
}