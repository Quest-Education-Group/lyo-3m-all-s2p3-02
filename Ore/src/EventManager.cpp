#include"EventManager.h"
#include"Window.h"
#include <GLFW/glfw3.h>

bool EventManager::GetKey(Window window, EventInput key, EventAction event)
{
	int state = glfwGetKey(window, key);
	if (state == event)
	{
		return true;
	}
	return false;
}

GamepadId EventManager::AddGamepad()
{
	return GamepadId();
}

std::string_view EventManager::GetGamepadName(GamepadId id)
{
	return std::string_view();
}

std::vector<float> EventManager::GetGamepadAxes(GamepadId)
{
	return std::vector<float>();
}

bool EventManager::GetButton(GamepadId id, EventInput button, EventAction event)
{
	return false;
}
