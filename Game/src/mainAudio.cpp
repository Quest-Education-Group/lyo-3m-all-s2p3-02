#include <windows.h>

#include "Nodes/NodeAudioEmitter.h"
#include "Define.h"

int main()
{
	AudioServer::Init();

	AudioChannel* music = AudioServer::CreateChannel("Music");
	AudioChannel* sfx = AudioServer::CreateChannel("Sfx");

	auto audioEm = Node::CreateNode<NodeAudioEmitter>("AudioEmitter");
	auto audioEm2 = Node::CreateNode<NodeAudioEmitter>("AudioEmitter2");
	auto audioEm2_bis = Node::CreateNode<NodeAudioEmitter>("AudioEmitter2_bis");

	audioEm->Load("res/freeman.mp3", music);
	audioEm2->Load("res/applause.mp3", sfx);
	audioEm2_bis->Load("res/bass-wiggle.mp3", sfx);

	audioEm2->SetLoop(true);
	audioEm2_bis->SetLoop(true);

	audioEm->Play();
	audioEm2->Play();
	audioEm2_bis->Play();

	while (true)
	{
		if (GetAsyncKeyState('P') & 0x8000)
		{
			audioEm->Play();
			std::cout << "testplay";
		}
		else if (GetAsyncKeyState('S') & 0x8000)
		{
			audioEm->Stop();
			std::cout << "teststop";
		}
		else if (GetAsyncKeyState(VK_ADD) & 0x8000)
		{
			//group volume
			float next = AudioServer::GetGroupVolume(*sfx) + 0.01f;
			AudioServer::SetGroupVolume(sfx, next);
			printf("GroupVolume: %.6f\n", AudioServer::GetGroupVolume(*sfx));
		}
		else if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)
		{
			//group volume
			float next = AudioServer::GetGroupVolume(*sfx) - 0.01f;
			AudioServer::SetGroupVolume(sfx, next);
			printf("GroupVolume: %.6f\n", AudioServer::GetGroupVolume(*sfx));
		}
		else if (GetAsyncKeyState('T') & 0x8000)
		{
			float next = AudioServer::GetMasterVolume() + 0.05f;
			AudioServer::SetMasterVolume(next);
			printf("MasterVolume: %.6f\n", AudioServer::GetMasterVolume());
		}
		else if (GetAsyncKeyState('Y') & 0x8000)
		{
			float next = AudioServer::GetMasterVolume() - 0.05f;
			AudioServer::SetMasterVolume(next);
			printf("MasterVolume: %.6f\n", AudioServer::GetMasterVolume());
		}
		Sleep(1);
	}

	AudioServer::Shutdown();

	return 0;
}