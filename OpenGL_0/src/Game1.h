#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "RenderSystem/Renderer.h"
#include "RenderSystem/GUI/MainGui.h"
#include "Window.h"

class Game1 {
public:
	Game1();
	~Game1();

	Game1(const Game1&) = delete;
	Game1& operator=(const Game1&) = delete;

	void Setup();
	int run();
	void Load3DModels();

private:
	static constexpr int WIDTH = 640;
	static constexpr int HEIGHT = 480;

	Renderer renderer;
	Window window;
	MainGui gui;

};