class AudioServer::Proxy
{
public:
    struct ProxyBinding;
    static bool Init() { return AudioServer::Init(); }
    static void Shutdown() { AudioServer::Shutdown(); }
    static AudioChannel* CreateChannel(const std::string& name) { return AudioServer::CreateChannel(name); }
    static void SetMasterVolume(float volume) { AudioServer::SetMasterVolume(volume); }
    static float GetMasterVolume() { return AudioServer::GetMasterVolume(); }
    static void SetGroupVolume(AudioChannel* channel, float v) { AudioServer::SetGroupVolume(channel, v); }
    static float GetGroupVolume(AudioChannel* channel) { return ma_sound_group_get_volume(&channel->soundGroup); }
};

BindProxy(AudioServer::Proxy, binder.BindClass<AudioChannel>("AudioChannel");
return binder.BindSingleton<AudioServer::Proxy>("AudioServer",
    "Init", BIND_STATIC(Init),
    "Shutdown", BIND_STATIC(Shutdown),
    "CreateChannel", BIND_STATIC(CreateChannel),
    "SetMasterVolume", BIND_STATIC(SetMasterVolume),
    "GetMasterVolume", BIND_STATIC(GetMasterVolume),
    "SetGroupVolume", BIND_STATIC(SetGroupVolume),
    "GetGroupVolume", BIND_STATIC(GetGroupVolume)
);
)
REGISTER_PROXY(AudioServer::Proxy::ProxyBinding, AudioServerProxy);