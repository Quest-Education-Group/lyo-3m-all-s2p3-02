#include <windows.h>

#include "Nodes/NodeAudioEmitter.h"
#include "Nodes/NodeAudioListener.h"
#include "MixerAudio.h"
#include "Define.h"

int main()
{
	// --- Audio Server ---
	AudioServer::Init();

	AudioChannel* music = AudioServer::CreateChannel("Music");
	AudioChannel* sfx = AudioServer::CreateChannel("Sfx");

	// --- Mixer ---
	MixerAudio mixer;
	mixer.Init();

	//mixer.AddDelay(sfx, 0.3f, 0.4f, 0.3f);
	mixer.FadeTo(sfx, 0.0f, 2.0f);

	// --- Audio Emitter ---
	auto audioEm = Node::CreateNode<NodeAudioEmitter>("AudioEmitter");
	auto audioEm2 = Node::CreateNode<NodeAudioEmitter>("AudioEmitter2");
	auto audioEm2_bis = Node::CreateNode<NodeAudioEmitter>("AudioEmitter2_bis");

	audioEm2->SetSourcePosition({ 0,0,0 });

	//audioEm->Load("res/freeman.mp3", music);
	audioEm2->Load("res/applause.mp3", sfx);
	//audioEm2->Load("res/applause.mp3", chSfx->audioChannel);
	
	//audioEm2_bis->Load("res/bass-wiggle.mp3", sfx);

	audioEm2->SetLoop(true);
	//audioEm2_bis->SetLoop(true);

	//audioEm->Play();
	audioEm2->Play();
	//audioEm2_bis->Play();


	// --- Audio Listener ---
	auto audioListen = Node::CreateNode<NodeAudioListener>("AudioListener");
	audioListen->SetListenerPosition({ 0,0,0 });

	while (true)
	{
		mixer.Update(0.001f);

		if (GetAsyncKeyState('P') & 0x8000)
		{
			if (audioEm2->IsPlaying()) 
			{
				audioEm2->Stop();
				std::cout << "Pause\n";
			}
			else
			{
				audioEm2->Play();
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
			audioEm2->SetSourcePosition({ 0,0,0 });
		}
		else if (GetAsyncKeyState('X') & 0x8000)
		{
			audioEm2->SetSourcePosition({ 50,0,0 });
		}

		else if (GetAsyncKeyState('Z') & 0x8000) //PositionAudio3D Listener
		{
			ma_vec3f newPos = audioListen->GetListenerPosition();
			newPos.y += 1;

			audioListen->SetListenerPosition(newPos);
		}
		else if (GetAsyncKeyState('Q') & 0x8000)
		{
			ma_vec3f newPos = audioListen->GetListenerPosition();
			newPos.x -= 1;

			audioListen->SetListenerPosition(newPos);
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			ma_vec3f newPos = audioListen->GetListenerPosition();
			newPos.y -= 1;

			audioListen->SetListenerPosition(newPos);
		}
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			ma_vec3f newPos = audioListen->GetListenerPosition();
			newPos.x += 1;

			audioListen->SetListenerPosition(newPos);
		}

		//Mixer
		//else if (GetAsyncKeyState('E') & 0x8000)
		//{
		//	delayWet = std::clamp(delayWet + 0.05f, 0.0f, 1.0f);
		//	mixer.SetSendWet("Music", "echo", delayWet);
		//	printf("Delay wet: %.2f\n", delayWet);
		//}
		//else if (GetAsyncKeyState('R') & 0x8000)
		//{
		//	delayWet = std::clamp(delayWet - 0.05f, 0.0f, 1.0f);
		//	mixer.SetSendWet("Music", "echo", delayWet);
		//	printf("Delay wet: %.2f\n", delayWet);
		//}

		Sleep(1);
	}

	mixer.Shutdown();
	AudioServer::Shutdown();

	return 0;
}