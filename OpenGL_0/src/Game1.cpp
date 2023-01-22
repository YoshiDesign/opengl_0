//#include "vcorepch.h"
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

Game1::Game1()
{
	Setup();
	//Load3DModels();
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    std::cout << glGetString(GL_VERSION) << std::endl;

    gui.InitImGui(window.getGLFWwindow());

}

int Game1::run()
{

    // Leaving this scope will clean up stack allocations while a GL Context still exists
    {

        auto obj = AppObject::createAppObject(/*TODO Implement textures*/);
        obj.model = Model3D::createModelFromFile("resource/3D/ship_demo.obj");
        obj.transform.translation = { 0.f, 0.f, 0.f };
        // appObjects.emplace(obj.getId(), std::move(obj));

        VertexArray va;
        VertexBuffer vb;
        vb.UpdateData(obj.model->getVerticesv(), obj.model->getSizeVertices());

        VertexBufferLayout layout;
        layout.PushVertex(sizeof(Model3D::Vertex));

        va.AddBuffer(vb, layout, sizeof(Model3D::Vertex));

        IndexBuffer ib(obj.model->getIndicesv(), obj.model->getSizeIndices());

        // World space definition
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        // The viewing vantage point
        glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(-100.f, 0.f, 0.f));
        // Model space
        glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(200.f, 200.f, 0.0f));
        // 
        glm::mat4 mvp = proj * view * model;

        ShaderSystem shader("resource/shaders/Simple_3D.shader");
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

            shader.SetUniformMat4f("u_MVP", mvp);
            //glUniformMatrix4fv(0, 1, GL_FALSE, &mvp[0][0]);

            //for (auto& obj : appObjects) {
            
                renderer.Draw(va, ib, shader);

            //}

            gui.Gui_Present();
            gui.Gui_Render();

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window.getGLFWwindow()));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

    }
    //glDeleteProgram();
    //glDeleteVertexArrays();
    glfwTerminate();
    return 0;
}

//void Game1::Load3DModels()
//{
//	auto ship = AppObject::createAppObject(/*TODO Implement textures*/);
//	ship.model = Model3D::createModelFromFile("resource/3D/ship_demo.obj");
//	ship.transform.translation = { 0.f, 0.f, 0.f };
//	appObjects.emplace(ship.getId(), std::move(ship));
//}