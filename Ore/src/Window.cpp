#include "Window.h"
#include "Logger.hpp"
#include "Define.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Window::Window(int width, int height, std::string name)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	m_width = width;
	m_height = height;
	m_name = name;

	Open();
}

Window::~Window()
{

}

bool Window::IsOpen()
{
	if (m_pWindow == nullptr)
		return false;

	return !glfwWindowShouldClose(m_pWindow);
}

void Window::Close()
{
	onCloseEvent();
	glfwTerminate();
}

void Window::Open()
{
	m_pWindow = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);

	if (m_pWindow == NULL)
	{
		Logger::LogWithLevel(LogLevel::ERROR, "Failed to create GLFW Window");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::LogWithLevel(LogLevel::ERROR, "Failed to initialize GLAD");
		return;
	}

	glfwSetFramebufferSizeCallback(m_pWindow, FrameBufferSizeCallback);

	onOpenEvent();
}

void Window::Present()
{
	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

void FrameBufferSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	glViewport(0, 0, width, height);
}