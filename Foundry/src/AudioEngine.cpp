#define MINIAUDIO_IMPLEMENTATION

#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
}

void AudioEngine::Data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount)
{
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    if (pDecoder == NULL) {
        return;
    }

    ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    (void)pInput;
}

void AudioEngine::SetAudioFile(const char* filePath)
{
    m_filePath = filePath;
}

void AudioEngine::Play()
{
    ma_result result;
    //ma_decoder decoder;
    ma_device_config deviceConfig;
    //ma_device device;

    result = ma_decoder_init_file(m_filePath, NULL, &m_decoder);
    if (result != MA_SUCCESS)
    {
        printf("Could not load file: %s\n", m_filePath);
        return;
    }

    if (m_loop) ma_data_source_set_looping(&m_decoder, MA_TRUE);

    deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format = m_decoder.outputFormat;
    deviceConfig.playback.channels = m_decoder.outputChannels;
    deviceConfig.sampleRate = m_decoder.outputSampleRate;
    deviceConfig.dataCallback = AudioEngine::Data_callback;
    deviceConfig.pUserData = &m_decoder;

    //ma_sound_set_volume();

    if (ma_device_init(NULL, &deviceConfig, &m_device) != MA_SUCCESS)
    {
        printf("Failed to open playback device.\n");
        ma_decoder_uninit(&m_decoder);
        return;
    }

    if (ma_device_start(&m_device) != MA_SUCCESS)
    {
        printf("Failed to start playback device.\n");
        ma_device_uninit(&m_device);
        ma_decoder_uninit(&m_decoder);
        return;
    }

    m_isPlaying = true;
}

void AudioEngine::Stop()
{
    ma_device_uninit(&m_device);
    ma_decoder_uninit(&m_decoder);

    m_isPlaying = false;
}

void AudioEngine::Update()
{
    if (m_isPlaying) 
    {

    }
}

void AudioEngine::SetLoop(bool value) 
{
    m_loop = value;
}