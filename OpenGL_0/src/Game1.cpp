//#include "vcorepch.h"
#include "Game1.h"
#include "RenderSystem/VertexBuffer.h"
#include "RenderSystem/IndexBuffer.h"
#include "RenderSystem/VertexArray.h"
#include "RenderSystem/ShaderSystem.h"
#include "RenderSystem/VertexBufferLayout.h"
#include "RenderSystem/Texture.h"
#include "RenderSystem/UBO.h"
#include "RenderSystem/FrameContent.h"
#include "Tests/TestClearColor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

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
        throw std::runtime_error("Glew is not ok!");
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
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
        obj.model = Model3D::createModelFromFile("resource/3D/sphere.obj");
        obj.transform.translation.z = -22.5f;
        obj.transform.scale = { 3.f, 8.f, 3.f };
        appObjects.emplace(obj.getId(), std::move(obj));

        auto obj_2 = AppObject::createAppObject(/*TODO Implement textures*/);
        obj_2.model = Model3D::createModelFromFile("resource/3D/sphere.obj");
        obj_2.transform.translation.z = -22.5f;
        obj_2.transform.translation.x = -20.f;
        appObjects.emplace(obj_2.getId(), std::move(obj_2));
        
        // Initial camera position
        viewerObject.transform.rotation.y = glm::radians(180.f);

        // Gen VA
        VertexArray va;
        // Gen VB
        VertexBuffer vb;
        // Gen IB
        IndexBuffer ib;

        // Construct vertex shader attributes
        VertexBufferLayout layout;
        layout.PushVertex(sizeof(Model3D::Vertex));

        // Bind and add VA -- Create our vertex attribute locations
        va.AddBuffer(ib, vb, layout);

        //
        ShaderSystem shaderSystem;
        shaderSystem.AddShader("resource/shaders/03_Simple_3D.shader", "BlueShader");
        shaderSystem.AddShader("resource/shaders/01_Simple_3D.shader", "GreenShader");

        shaderSystem.Bind("BlueShader");

        //
        UBO ubo;
        ubo.CreateNamedUniformBlock("Transforms", shaderSystem.GetID("BlueShader"), 3);

        //
        FrameContent frame_content = {
          camera,
          appObjects,
          ubo
        };

        //Texture texture("resource/textures/t1.png");
        //texture.Bind();

        auto currentTime = std::chrono::high_resolution_clock::now();

        gui.debug_data.emplace("FrameTime", 0.0f);
        gui.debug_data.emplace("FPS", 1.0f);

        int m_frames = 0;
        float m_tick = 0.0f;
        float fps = 0.0f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window.getGLFWwindow()))
        {
            glfwPollEvents();

            gui.Gui_NewFrame();

            renderer.Clear();

            // Calculate time between iterations
            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;
            gui.debug_data["FrameTime"] = frameTime;

            // Calculating FPS
            m_tick += frameTime;
            //m_frames++;
            if (m_tick >= 1.0f) 
            {
                gui.debug_data["FPS"] = ImGui::GetIO().Framerate;
                m_tick = 0.0f;
                //m_frames = 0;
                //tick++;
            }

            //frameTime = glm::min(frameTime, MAX_FRAME_TIME);	// Use this to lock to a specific max frame rate

            // Updates the viewer object transform component based on key input, proportional to the time elapsed since the last frame
            updateCamera(frameTime, viewerObject, camera);

            renderer.Draw(va, vb, ib, shaderSystem, frame_content);

            gui.Gui_Present();
            gui.Gui_Render();

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window.getGLFWwindow()));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

    }

    // Exiting the anonymous scope will delete from each class destructor
    //glDeleteProgram();
    //glDeleteVertexArrays();

    glfwTerminate();
    return 0;
}

void Game1::updateCamera(float frameTime, AppObject& viewerObject, Camera& camera)
{
    cameraController.moveInPlaneXZ(window.getGLFWwindow(), frameTime, viewerObject);
    camera.setViewYXZ(viewerObject.transform.translation + glm::vec3(0.f, 0.f, 0.f), viewerObject.transform.rotation + glm::vec3());
    camera.setPerspectiveProjection(glm::radians(50.f), aspect, 2.0f, 500.f);
}

void Game1::Load3DModels()
{
	auto ship = AppObject::createAppObject(/*TODO Implement textures*/);
	ship.model = Model3D::createModelFromFile("resource/3D/sphere.obj");
	ship.transform.translation = { 0.f, 0.f, 0.f };
	appObjects.emplace(ship.getId(), std::move(ship));

    //for (int i = 0; i < 10; i++) {
    //    
    //}
}