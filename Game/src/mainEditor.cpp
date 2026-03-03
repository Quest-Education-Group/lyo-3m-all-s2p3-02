////////////////////////////////////////////////////
// CMake Generator by Alexandre Glatz
// https://github.com/AlexandreGlatz/cmake-generator
////////////////////////////////////////////////////

#include <Editor.h>
#include <iostream>

bool Quit = false;


int main() {
	Editor editor;
	editor.init();

	while (!WindowShouldClose() && !Quit)    // Detect window close button or ESC key
	{
		std::cout << "yes" << std::endl;
	}



}