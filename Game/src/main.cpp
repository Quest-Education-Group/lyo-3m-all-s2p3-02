////////////////////////////////////////////////////
// CMake Generator by Alexandre Glatz
// https://github.com/AlexandreGlatz/cmake-generator
////////////////////////////////////////////////////

#include <Node.h>

#include <iostream>
#include <memory>
int main()
{
	std::unique_ptr<Node> node = Node::CreateNode<Node>("HelloNode");
    std::cout<<"Hello World !"<<std::endl;
}
