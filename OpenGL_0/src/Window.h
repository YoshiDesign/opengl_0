#pragma once
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <string>

	class Window {
		std::string windowName;
		GLFWwindow* window_device;

		bool framebufferResized = false;
		int width;
		int height;

	public:

		Window();
		~Window();

		int InitWindow(int w, int h, std::string name);

		// Removal of copy construction
		//Window(const Window&) = delete;
		//Window& operator=(const Window&) = delete;

		bool shouldClose();

		bool wasWindowResized() { return framebufferResized; }

		void resetWindowResizedFlag() { framebufferResized = false; }

		GLFWwindow* getGLFWwindow() const { return window_device; }

	private:
		static void framebufferResizedCallback(GLFWwindow* window, int width, int height);
		

	};
