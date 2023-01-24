#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "RenderSystem/Renderer.h"
#include "RenderSystem/GUI/MainGui.h"
#include "Window.h"
#include "GameSystem/AppObject.h"
#include "RenderSystem/Camera.h"

class Game1 {
public:
	Game1();
	~Game1();

	Game1(const Game1&) = delete;
	Game1& operator=(const Game1&) = delete;

	void Setup();
	int run();
	void updateCamera(/*float frameTime, */AppObject& viewerObject, Camera& camera);
	//void Load3DModels();

private:
	static constexpr int WIDTH = 640;
	static constexpr int HEIGHT = 480;

	float aspect{ WIDTH / HEIGHT };

	//AppObject::Map appObjects;
	AppObject viewerObject{ AppObject::createAppObject() };
	Camera camera{};
	Renderer renderer;
	Window window;
	MainGui gui;

};