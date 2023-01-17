#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "Tests/TestClearColor.h"
#include "Tests/TestTexture2D.h"

class MainGui {

public:
	MainGui(GLFWwindow* window);
	~MainGui();

	void Gui_NewFrame();
	void Gui_Present();
	void Gui_Render();
	void Gui_RegisterTests();

private:
	float f;
	int counter;
	test::TestClearColor ccTest;
	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
};