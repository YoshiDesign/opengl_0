#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "RenderSystem/Renderer.h"
#include "RenderSystem/VertexBuffer.h"
#include "RenderSystem/IndexBuffer.h"
#include "RenderSystem/VertexArray.h"
#include "RenderSystem/ShaderSystem.h"
#include "RenderSystem/VertexBufferLayout.h"
#include "RenderSystem/Texture.h"
#include "RenderSystem/GUI/MainGui.h"
#include "Tests/TestClearColor.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#define BUGGER 1

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!glewInit() == GLEW_OK) {
        std::cout << "Glew is not ok!" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
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

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //unsigned int vao;
        //GLCall(glGenVertexArrays(1, &vao));
        //GLCall(glBindVertexArray(vao));

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

        Renderer renderer;
        MainGui gui(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            //glfwPollEvents();

            /* Render here */
            renderer.Clear();

            gui.Gui_NewFrame();

            shader.Bind();
            shader.SetUniform4f("u_Color", 0.4f, 0.6f, 0.9f, 1.0f);

            renderer.Draw(va, ib, shader);

            gui.Gui_Present();
            gui.Gui_Render();

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }

    }
    glfwTerminate();
    return 0;
}