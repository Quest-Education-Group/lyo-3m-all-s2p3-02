#ifndef NODE_CHUNK__H_
#define NODE_CHUNK__H_

//Chunk of node for multithreading
struct NodeChunk
{
    class Node* Nodes[128] {};
};

#endif
