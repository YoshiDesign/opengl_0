#pragma once
#include "Test.h"
#include <memory>
#include "RenderSystem/Renderer.h"
#include "RenderSystem/VertexBuffer.h"
#include "RenderSystem/VertexBufferLayout.h"
#include "RenderSystem/Texture.h"

namespace test {

	class TestTexture2D : public Test {
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float dt) override;
		void OnRender() override;
		void OnImguiRender() override;

	private:
		std::unique_ptr <VertexBuffer> m_VertexBuffer;
		std::unique_ptr <VertexArray>  m_VertexArray;
		std::unique_ptr <IndexBuffer>  m_IndexBuffer;
		std::unique_ptr <ShaderSystem> m_Shader;
		std::unique_ptr <Texture>	   m_Texture;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		glm::vec3 m_TranslationA, m_TranslationB;
	};
	
}