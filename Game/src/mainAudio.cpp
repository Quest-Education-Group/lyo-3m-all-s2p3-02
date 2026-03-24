#include "Nodes/NodeAudioEmitter.h"
#include "Define.h"

int main()
{
    auto audioEm = Node::CreateNode<NodeAudioEmitter>("AudioEmitter");
    audioEm->AudioSetFile("C:/Users/psolat/Documents/GitHub/lyo-3m-all-s2p3-02/res/bass-wiggle.mp3"); // TEST ONLY (replace with your file)
    audioEm->AudioSetLoop(true);

    auto audioEm2 = Node::CreateNode<NodeAudioEmitter>("AudioEmitter2");
    audioEm2->AudioSetFile("C:/Users/psolat/Documents/GitHub/lyo-3m-all-s2p3-02/res/applause.mp3"); // TEST ONLY (replace with your file)
    audioEm2->AudioSetLoop(true);

    audioEm->AudioPlay();
    audioEm2->AudioPlay();

    while (true)
    {
        
    }

    return 0;
}