#ifndef FOUNDRY_AUDIOENGINE__H_
#define FOUNDRY_AUDIOENGINE__H_

#include "Define.h"
#include "miniaudio.h"

#include <iostream>

class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine() = default;
	
	void SetAudioFile(const char* filePath);

	void Play();
	void Stop();

	void Update();

	void SetLoop(bool value);

protected:
	bool m_isPlaying = false;
	bool m_loop = false;
	float m_volume = 1.f;

	const char* m_filePath = nullptr; // TODO : Make an audio file class instead

	ma_decoder m_decoder;
	ma_device m_device;
	ma_uint32 m_channelsCount = 0;

private:
	static void Data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);
};

#endif