#include "Window.h"
#include <iostream>
//#include <stdexcept>

Window::Window(){}

Window::~Window()
{
	glfwDestroyWindow(window_device);
	glfwTerminate();
}

/**
* Initialize the window
*
*/
int Window::InitWindow(int w, int h, std::string name) 
{

	if (!glfwInit())
		return -1;

	window_device = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
	if (!window_device)
	{
		glfwTerminate();
		return -1;
	}

	// Open in windowed mode - Since we're using Vulkan we need to handle window resizing in a different way
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	// The parent Window object is 'this'
	glfwSetWindowUserPointer(window_device, this);

	// Whenever our window is resized, this callback is executed with the args in the callback's signature (new width and height)
	glfwSetFramebufferSizeCallback(window_device, framebufferResizedCallback);

	glfwMakeContextCurrent(window_device);
	glfwSwapInterval(1);

}

bool Window::shouldClose() { return glfwWindowShouldClose(window_device); }

void Window::framebufferResizedCallback(GLFWwindow* window, int width, int height)
{
	auto _window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	_window->framebufferResized = true;
	_window->width = width;
	_window->height = height;
}
