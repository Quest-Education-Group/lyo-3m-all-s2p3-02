#ifndef MIXER_AUDIO__H_
#define MIXER_AUDIO__H_

#include "Servers/AudioServer.h"

struct DelayEntry
{
    ma_delay_node node;
    bool active = false;
};

struct FadeEntry
{
    AudioChannel* channel = nullptr;
    float current = 1.0f;
    float target = 0.0f;
    float speed = 1.0f;
    bool active = false;
};

class MixerAudio
{
public:
    bool Init();
    void Shutdown();

    void AddDelay(AudioChannel* channel, float delaySeconds, float decay, float wet = 0.5f);
    void SetDelayWet(AudioChannel* channel, float wet);
    void RemoveDelay(AudioChannel* channel);

    void FadeTo(AudioChannel* channel, float targetVolume, float durationSeconds);
    void Update(float delta);

protected:
    std::unordered_map<AudioChannel*, DelayEntry> m_delays;
    std::vector<FadeEntry> m_fades;

private:

};

#endif