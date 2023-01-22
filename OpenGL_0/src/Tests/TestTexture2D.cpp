#include "vcorepch.h"
#include "TestTexture2D.h"
#include "imgui/imgui.h"


namespace test {

	TestTexture2D::TestTexture2D()
		: m_TranslationA(200, 200, 0), m_TranslationB(400, 200, 0),
		m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.f), glm::vec3(-100.f, 0.f, 0.f)))
		
	{
		/*float vertices[16] = {
			-50.0f, -50.0f, 0.0f, 0.0f,
			 50.0f, -50.0f, 1.0f, 0.0f,
			 50.0f,  50.0f, 1.0f, 1.0f,
			-50.0f,  50.0f, 0.0f, 1.0f
		};

		unsigned int indices[6] = {
			0,1,2,
			2,3,0
		};

		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<ShaderSystem>("resource/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.2f, 0.8f, 0.8f, 1.0f);

		m_Texture = std::make_unique<Texture>("resource/textures/textest.png");
		m_Shader->SetUniform1i("u_Texture", 0);*/

	}

	TestTexture2D::~TestTexture2D()
	{
	
	}

	void TestTexture2D::OnUpdate(float dt)
	{
	}

	void TestTexture2D::OnRender()
	{
		/*glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Texture->Bind();

		Renderer renderer;

		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp); 
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}*/

	}

	// Any ImGui elements for this test
	void TestTexture2D::OnImguiRender()
	{
		ImGui::SliderFloat3("TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
		
	}
}