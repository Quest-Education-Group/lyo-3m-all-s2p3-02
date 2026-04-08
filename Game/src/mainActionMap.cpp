
#include "EventManager.h"
#include "ActionMap.h"
#include "Action.h"

#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include "GameLoop.h"
#include "SceneTree.h"
#include <Nodes/NodeWindow.h>

void Test(IControl& iControl)
{
    std::cout << "je suis un test\n";
    iControl.GetControlType();
}


int main(int argc, char** argv)
{
    uptr<Node> root = Node::CreateNode<NodeWindow>("Root");
    uptr<Node> scene = Node::CreateNode<Node>("Scene");    //Load this with the default .st file


    //ActionMap map = ActionMap("DEFAULT");
    //map.CreateAction("test", ControlType::BUTTON, EventInput::KEY_SPACE);

    //map.GetAction("test").Event = Test;

    //map.GetAction("test").Event(map.GetAction("test").GetControl(0));

    uptr<LuaScriptInstance> script = std::make_unique<LuaScriptInstance>("res/test.lua");
    Node::AttachScript(script, *scene);
    root->AddChild(scene);

    SceneTree defaultSceneTree(root);

    GameLoop loop;
    loop.StartGame(defaultSceneTree);


	return 0;
}
