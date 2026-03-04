#include "EventManager.h"
#include "Logger.hpp"

Event<void(GamepadId)> EventManager::gamepadConnected = Event<void(GamepadId)>();
Event<void(GamepadId)> EventManager::gamepadDisconnected = Event<void(GamepadId)>();

bool EventManager::GetKey(Window window, EventInput key, EventAction event)
{
	int state = glfwGetKey(window.GetWindow(), (int)key);
	if (state == (int)event)
	{
		Logger::LogWithLevel(LogLevel::DEBUG, (char)key);
		return true;
	}
	return false;
}

bool EventManager::GetMouseKey(Window window, EventInput key, EventAction event)
{
	int state = glfwGetMouseButton(window.GetWindow(), (int)key);
	if (state == (int)event)
	{
		Logger::LogWithLevel(LogLevel::DEBUG, (int)key);
		return true;
	}
	return false;
}

GamepadId EventManager::CheckGamepad()
{
	int present = glfwJoystickPresent(GLFW_JOYSTICK_2);
	Logger::LogWithLevel(LogLevel::DEBUG, present);
	return GamepadId();
}

void EventManager::JoystickCallback(int jId, int event)
{
	if (event == GLFW_CONNECTED)
		EventManager::gamepadConnected((GamepadId)jId);
	if (event == GLFW_DISCONNECTED)
		EventManager::gamepadDisconnected((GamepadId)jId);
}

std::string_view EventManager::GetGamepadName(GamepadId id)
{
	const char* name = glfwGetGamepadName((int)id);
	std::string_view gamepadName(name);
	Logger::LogWithLevel(LogLevel::DEBUG, gamepadName);
	return gamepadName;
}

std::vector<float> EventManager::GetGamepadAxes(GamepadId id)
{
	int axesCount;
	const float* axes = glfwGetJoystickAxes((int)id, &axesCount);
	//Logger::LogWithLevel(LogLevel::DEBUG, axesCount);
	Logger::LogWithLevel(LogLevel::DEBUG, axes[0]);
	Logger::LogWithLevel(LogLevel::DEBUG, axes[1]);
	Logger::LogWithLevel(LogLevel::DEBUG, axes[2]);
	Logger::LogWithLevel(LogLevel::DEBUG, axes[3]);
	Logger::LogWithLevel(LogLevel::DEBUG, axes[4]);
	Logger::LogWithLevel(LogLevel::DEBUG, axes[5]);
	return std::vector<float>();
}

bool EventManager::GetButton(GamepadId id, EventInput button)
{
	GLFWgamepadstate state;

	if (glfwGetGamepadState((int)id, &state))
	{
		if (state.buttons[(int)button])
		{
			Logger::LogWithLevel(LogLevel::DEBUG, (int)button);
			return true;
		}
	}
}

