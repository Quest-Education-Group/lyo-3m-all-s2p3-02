#include "GameLoop.h"
#include "SceneTree.h"
#include <Nodes/NodeWindow.h>

#include <windows.h>

#include "Nodes/NodeAudioEmitter.h"
#include "Nodes/NodeAudioListener.h"
#include "MixerAudio.h"
#include "Define.h"

//main v1 moteur

int main()
{
	// --- Audio Server ---
	AudioServer::Init();

	AudioChannel* music = AudioServer::CreateChannel("Music");
	AudioChannel* sfx = AudioServer::CreateChannel("Sfx");

	// --- Mixer ---
	MixerAudio mixer;

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

	printf("audio1 x:%.6f\n", audioEm->GetSourcePosition().x);
	printf("audio2 x:%.6f\n", audioEm2->GetSourcePosition().x);
	printf("listener x:%.6f\n", audioListen->GetListenerPosition().x);

	while (true)
	{
		if (GetAsyncKeyState('P') & 0x8000)
		{
			if (audioEm->IsPlaying()) 
			{
				audioEm->Stop();
				std::cout << "Pause\n";
			}
			else
			{
				audioEm->Play();
				std::cout << "Play\n";
			}
			Sleep(200);
		}

		else if (GetAsyncKeyState(VK_ADD) & 0x8000)
		{
			//Group volume
			float next = AudioServer::GetGroupVolume(*sfx) + 0.01f;
			AudioServer::SetGroupVolume(sfx, next);
			printf("GroupVolume: %.6f\n", AudioServer::GetGroupVolume(*sfx));
		}
		else if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)
		{
			//Group volume
			float next = AudioServer::GetGroupVolume(*sfx) - 0.01f;
			AudioServer::SetGroupVolume(sfx, next);
			printf("GroupVolume: %.6f\n", AudioServer::GetGroupVolume(*sfx));
		}
		else if (GetAsyncKeyState('T') & 0x8000)
		{
			//Master volume
			float next = AudioServer::GetMasterVolume() + 0.05f;
			AudioServer::SetMasterVolume(next);
			printf("MasterVolume: %.6f\n", AudioServer::GetMasterVolume());
		}
		else if (GetAsyncKeyState('Y') & 0x8000)
		{
			//Master volume
			float next = AudioServer::GetMasterVolume() - 0.05f;
			AudioServer::SetMasterVolume(next);
			printf("MasterVolume: %.6f\n", AudioServer::GetMasterVolume());
		}

		else if (GetAsyncKeyState('W') & 0x8000) //PositionAudio3D Emitter
		{
			audioListen->SetListenerPosition({ 0,0,0 });
		}
		else if (GetAsyncKeyState('X') & 0x8000)
		{
			audioEm->SetSourcePosition({ 50,0,0 });
		}

		else if (GetAsyncKeyState('Z') & 0x8000) //PositionAudio3D Listener
		{
			glm::vec3 newPos = audioListen->GetListenerPosition();
			newPos.y += 0.1f;

			audioListen->SetListenerPosition(newPos);
		}
		else if (GetAsyncKeyState('Q') & 0x8000)
		{
			glm::vec3 newPos = audioListen->GetListenerPosition();
			newPos.x -= 0.1f;

			audioListen->SetListenerPosition(newPos);
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			glm::vec3 newPos = audioListen->GetListenerPosition();
			newPos.y -= 0.1f;

			audioListen->SetListenerPosition(newPos);
		}
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			glm::vec3 newPos = audioListen->GetListenerPosition();
			newPos.x += 0.1f;

			audioListen->SetListenerPosition(newPos);
		}

		Sleep(1);
	}

	mixer.Shutdown();
	AudioServer::Shutdown();

	return 0;
}

//main v2 lua

//int main(int argc, char** argv)
//{
//    uptr<Node> root = Node::CreateNode<NodeWindow>("Root");
//    uptr<Node> scene = Node::CreateNode<Node>("Scene");    //Load this with the default .st file
//    root->AddChild(scene);
//    SceneTree defaultSceneTree(root);
//
//    //audio code
//
//    //end audio code
//
//    GameLoop loop;
//    loop.StartGame(defaultSceneTree);
//
//
//    return 0;
//}
