#include "GameLoop.h"
#include "SceneTree.h"
#include "Nodes/NodeCamera.h"
#include "Nodes/NodeViewport.h"
#include "Nodes/NodeWindow.h"

int main()
{
    uptr<Node> root = Node::CreateNode<NodeWindow>("Window");
    uptr<Node> viewport = Node::CreateNode<NodeViewport>("Viewport");
    uptr<Node> scene = Node::CreateNode<Node>("Scene");

    uptr<Node> camera = Node::CreateNode<NodeCamera>("Camera");
    scene->AddChild(camera);
    viewport->AddChild(scene);
    root->AddChild(viewport);

    SceneTree defaultSceneTree(root);

    GameLoop loop;
    loop.StartGame(defaultSceneTree);
}
