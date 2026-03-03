#include "Window.h"

int main()
{
	Window window(800, 600, "ORE ORE OREORE ORE ORE OREORE OREORE");
	while (window.IsOpen())
	{
		window.Present();
	}
	window.Close();
}
