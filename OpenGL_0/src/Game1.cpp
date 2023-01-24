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
#include <chrono>

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
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);
    std::cout << glGetString(GL_VERSION) << std::endl;

    gui.InitImGui(window.getGLFWwindow());

}

int Game1::run()
{

    // Leaving this scope will clean up stack allocations while a GL Context still exists
    {

        auto obj = AppObject::createAppObject(/*TODO Implement textures*/);
        obj.model = Model3D::createModelFromFile("resource/3D/cube.obj");
        obj.transform.translation.z = -22.5f;
        obj.transform.rotation.z = glm::radians(32.f);
        obj.transform.rotation.x = glm::radians(25.f);
        obj.transform.scale = { 10.f, 10.f, 10.f };
        // appObjects.emplace(obj.getId(), std::move(obj));
        

        // Initial camera position
        viewerObject.transform.rotation.y = glm::radians(180.f);
        // updateCamera(viewerObject, camera);

        VertexArray va;
        VertexBuffer vb;
        vb.UpdateData(obj.model->getVerticesv(), obj.model->getNumVertices());

        VertexBufferLayout layout;
        layout.PushVertex(sizeof(Model3D::Vertex));

        va.AddBuffer(vb, layout);

        IndexBuffer ib(obj.model->getIndicesv(), obj.model->getNumIndices());

        glm::mat4 projectionMat = camera.getProjection();
        glm::mat4 viewMat = camera.getView();
        glm::mat4 modelMat = obj.transform._mat4();
        //glm::mat4 mvp = proj * view * model;

        ShaderSystem shader("resource/shaders/Simple_3D.shader");
        //shader.Bind();
        //shader.SetUniform4f("u_Color", 0.2f, 0.8f, 0.8f, 1.0f);
        //shader.SetUniformMat4f("u_MVP", mvp);
        //glUniformMatrix4fv(0, 1, GL_FALSE, &mvp[0][0]);
        //glEnableVertexAttribArray(0);
        

        //Texture texture("resource/textures/textest.png");
        //texture.Bind();
        //shader.SetUniform1i("u_Texture", 0);

        //va.Unbind();
        //shader.Unbind();
        //vb.Unbind();
        //ib.Unbind();

        auto currentTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window.getGLFWwindow()))
        {
            glfwPollEvents();

            /* Render here */
            renderer.Clear();

            gui.Gui_NewFrame();

            // Calculate time between iterations
            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            //frameTime = glm::min(frameTime, MAX_FRAME_TIME);	// Use this to lock to a specific max frame rate

            // Updates the viewer object transform component based on key input, proportional to the time elapsed since the last frame
            updateCamera(frameTime, viewerObject, camera);

            //for (auto& obj : appObjects) {
            renderer.Draw(va, ib, shader);
            glUniformMatrix4fv(0, 1, GL_FALSE, camera.getProjectionv());
            glUniformMatrix4fv(1, 1, GL_FALSE, camera.getViewv());
            glUniformMatrix4fv(2, 1, GL_FALSE, &modelMat[0][0]);
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            //shader.SetUniformMat4f("u_MVP", mvp);
            

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

void Game1::updateCamera(float frameTime, AppObject& viewerObject, Camera& camera)
{
    cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
    camera.setViewYXZ(viewerObject.transform.translation + glm::vec3(0.f, 0.f, -.80f), viewerObject.transform.rotation + glm::vec3());
    camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 1000.f);
}

//void Game1::Load3DModels()
//{
//	auto ship = AppObject::createAppObject(/*TODO Implement textures*/);
//	ship.model = Model3D::createModelFromFile("resource/3D/ship_demo.obj");
//	ship.transform.translation = { 0.f, 0.f, 0.f };
//	appObjects.emplace(ship.getId(), std::move(ship));
//}