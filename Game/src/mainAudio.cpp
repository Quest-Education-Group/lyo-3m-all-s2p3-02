#include "AudioEngine.h" // need to make node and server instead
#include "Define.h" //temp


int main(int argc, char** argv)
{
    if (argc > 1) 
    {
        AudioEngine newAudioEngine;
        newAudioEngine.PlayAudio(argv[1]);
    }
    else
    {
        printf("Empty filepath\n");
    }


    return 0;
}