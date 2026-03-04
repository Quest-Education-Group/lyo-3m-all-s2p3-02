#include "Window.h"
#include "EventManager.h"
int main()
{

	Window window(800, 600, "ORE ORE OREORE ORE ORE OREORE OREORE");
	Window window2(500, 200, "oui oui baguette");
	while (window.IsOpen())
	{
		window.Present();
		window2.Present();
	}
	window.Close();
	window2.Close();
}
