#pragma once
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <unordered_map>

#include "Tests/TestClearColor.h"
//#include "Tests/TestTexture2D.h"
#include "Gamesystem/DebugData.h"

class MainGui {

public:
	MainGui();
	~MainGui();

	void InitImGui(GLFWwindow* window);
	void Gui_NewFrame();
	void Gui_Present();
	void Gui_Render();
	void Gui_RegisterTests();

	std::unordered_map<const char*, float> debug_data;
private:
	float f;
	int counter;

	test::Test* currentTest = nullptr;
	test::TestMenu* testMenu = new test::TestMenu(currentTest);
};