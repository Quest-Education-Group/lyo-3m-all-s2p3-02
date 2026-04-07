#include "Nodes/NodeAudioEmitter.h"
#include "Nodes/NodeAudioListener.h"
#include "AudioMixer.h"
#include "Define.h"

#include "ActionMap.h"
#include "Action.h"
#include "GameLoop.h"

#include <Nodes/NodeWindow.h>

int main()
{
    uptr<Node> root = Node::CreateNode<NodeWindow>("Root");
    uptr<Node> scene = Node::CreateNode<Node>("Scene");
    root->AddChild(scene);
    SceneTree defaultSceneTree(root);

	// --- Audio Server ---
	AudioServer::Init();

	AudioChannel* music = AudioServer::CreateChannel("Music");
	AudioChannel* sfx = AudioServer::CreateChannel("Sfx");

	// --- Mixer ---
    AudioMixer mixer;

	//mixer.AddDelay(sfx, 0.3f, 0.4f, 0.3f);
	mixer.AddReverb(music, 0.85f, 0.3f);

	// --- Audio Emitter ---
	auto audioEm = Node::CreateNode<NodeAudioEmitter>("AudioEmitter");
	auto audioEm2 = Node::CreateNode<NodeAudioEmitter>("AudioEmitter2");

	audioEm->Load("res/freeman.mp3", music);
	audioEm2->Load("res/applause.mp3", sfx);

	audioEm2->SetSourcePosition({ 100,0,0 }); // allways after load

	//audioEm->SetLoop(true);
	audioEm2->SetLoop(true);

	audioEm->Play();
	audioEm2->Play();

	// --- Audio Listener ---
	auto audioListen = Node::CreateNode<NodeAudioListener>("AudioListener");
	audioListen->SetListenerPosition({ 0,0,0 });

	Logger::Log("audio1 x:" + std::to_string(audioEm->GetSourcePosition().x));
	Logger::Log("audio2 x:" + std::to_string(audioEm2->GetSourcePosition().x));
	Logger::Log("listener x:" + std::to_string(audioListen->GetListenerPosition().x));

    // --- Actions ---
    ActionMap actionMap;

    uptr<Action> pauseAction = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_P);
    pauseAction.get()->Event += [&](IControl& control)
        {
            if (audioEm->IsPlaying())
            {
                audioEm->Stop();
                Logger::Log("Pause");
            }
            else
            {
                audioEm->Play();
                Logger::Log("Play");
            }
        };
    actionMap.Emplace("Pause", pauseAction.get());

    uptr<Action> volUpSfx = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_B);
    volUpSfx.get()->Event += [&](IControl& control)
        {
            float next = AudioServer::GetGroupVolume(*music) + 0.01f;
            AudioServer::SetGroupVolume(music, next);
            Logger::Log("GroupVolume: ", AudioServer::GetGroupVolume(*music));
        };
    actionMap.Emplace("VolUpSfx", volUpSfx.get());

    uptr<Action> volDownSfx = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_N);
    volDownSfx.get()->Event += [&](IControl& control)
        {
            float next = AudioServer::GetGroupVolume(*music) - 0.01f;
            AudioServer::SetGroupVolume(music, next);
            Logger::Log("GroupVolume: ", AudioServer::GetGroupVolume(*music));
        };
    actionMap.Emplace("VolDownSfx", volDownSfx.get());

    uptr<Action> masterUp = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_T);
    masterUp.get()->Event += [&](IControl& control)
        {
            float next = AudioServer::GetMasterVolume() + 0.05f;
            AudioServer::SetMasterVolume(next);
            Logger::Log("MasterVolume: ", AudioServer::GetMasterVolume());
        };
    actionMap.Emplace("MasterUp", masterUp.get());

    uptr<Action> masterDown = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_Y);
    masterDown.get()->Event += [&](IControl& control)
        {
            float next = AudioServer::GetMasterVolume() - 0.05f;
            AudioServer::SetMasterVolume(next);
            Logger::Log("MasterVolume: ", AudioServer::GetMasterVolume());
        };
    actionMap.Emplace("MasterDown", masterDown.get());

    uptr<Action> resetListener = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_W);
    resetListener.get()->Event += [&](IControl& control)
        {
            audioListen->SetListenerPosition({ 0, 0, 0 });
        };
    actionMap.Emplace("ResetListener", resetListener.get());

    uptr<Action> moveEmitter = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_X);
    moveEmitter.get()->Event += [&](IControl& control)
        {
            audioEm->SetSourcePosition({ 50, 0, 0 });
        };
    actionMap.Emplace("MoveEmitter", moveEmitter.get());

    uptr<Action> moveUp = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_Z);
    moveUp.get()->Event += [&](IControl& control)
        {
            glm::vec3 newPos = audioListen->GetListenerPosition();
            newPos.y += 0.1f;
            audioListen->SetListenerPosition(newPos);
        };
    actionMap.Emplace("MoveUp", moveUp.get());

    uptr<Action> moveLeft = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_Q);
    moveLeft.get()->Event += [&](IControl& control)
        {
            glm::vec3 newPos = audioListen->GetListenerPosition();
            newPos.x -= 0.1f;
            audioListen->SetListenerPosition(newPos);
        };
    actionMap.Emplace("MoveLeft", moveLeft.get());

    uptr<Action> moveDown = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_S);
    moveDown.get()->Event += [&](IControl& control)
        {
            glm::vec3 newPos = audioListen->GetListenerPosition();
            newPos.y -= 0.1f;
            audioListen->SetListenerPosition(newPos);
        };
    actionMap.Emplace("MoveDown", moveDown.get());

    uptr<Action> moveRight = std::make_unique<Action>(ControlType::BUTTON, EventInput::KEY_D);
    moveRight.get()->Event += [&](IControl& control)
        {
            glm::vec3 newPos = audioListen->GetListenerPosition();
            newPos.x += 0.1f;
            audioListen->SetListenerPosition(newPos);
        };
    actionMap.Emplace("MoveRight", moveRight.get());

    GameLoop loop;
    loop.StartGame(defaultSceneTree);

	mixer.Shutdown();
	AudioServer::Shutdown();

	return 0;
}