#include "AudioEngine.h" // need to make node and server instead
#include "Define.h" //temp


int main(int argc, char** argv)
{
    if (argv) 
    {
        AudioEngine newAudioEngine;
        newAudioEngine.PlayAudio(argv[1]);
    }
    else
    {
        std::cout << "test";
    }


    return 0;
}