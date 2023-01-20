#include "Game1.h"
#include "RenderSystem/VertexBuffer.h"
#include "RenderSystem/IndexBuffer.h"
#include "RenderSystem/VertexArray.h"
#include "RenderSystem/ShaderSystem.h"
#include "RenderSystem/VertexBufferLayout.h"
#include "RenderSystem/Texture.h"
#include "Tests/TestClearColor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"


Game1::Game1()
{
	Setup();
	Load3DModels();
}

Game1::~Game1()
{

}

void Game1::Setup()
{

    window.InitWindow(WIDTH, HEIGHT, "Game1");

    if (!glewInit() == GLEW_OK) {
        std::runtime_error("Glew is not ok!");
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    gui.InitImGui(window.getGLFWwindow());

}

int Game1::run()
{

    // Leaving this scope will clean up stack allocations while a GL Context still exists
    {
        float vertices[16] = {
             0.0f,   100.0f, 0.0f, 0.0f,
             200.0f, 100.0f, 1.0f, 0.0f,
             200.0f, 200.0f, 1.0f, 1.0f,
             0.0f,   200.0f, 0.0f, 1.0f
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(vertices, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(-100.f, 0.f, 0.f));
        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(200.f, 200.f, 0.0f));
        glm::mat4 mvp = proj * view * model;

        ShaderSystem shader("resource/shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.2f, 0.8f, 0.8f, 1.0f);
        shader.SetUniformMat4f("u_MVP", mvp);

        Texture texture("resource/textures/textest.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window.getGLFWwindow()))
        {
            //glfwPollEvents();

            /* Render here */
            renderer.Clear();

            gui.Gui_NewFrame();

            shader.Bind();

            renderer.Draw(va, ib, shader);

            gui.Gui_Present();
            gui.Gui_Render();

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window.getGLFWwindow()));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

    }
    glfwTerminate();
    return 0;
}

void Game1::Load3DModels()
{
	//auto ship = Entity::createAppObject(THEME_1);
	//ship.model = AvengModel::createModelFromFile("3D/ship_demo.obj");
	//ship.transform.translation = { 0.f, 0.f, 0.f };
	//appObjects.emplace(ship.getId(), std::move(ship));
}