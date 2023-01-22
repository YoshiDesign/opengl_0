#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <GLEW/glew.h>

// Specifies the Vertex Buffer Layout's attributes
struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	// These are the supported types of our VertexArray.
	// They will determine the byte offsets of our data
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:   return 4;
			case GL_UNSIGNED_BYTE:  return 1;
			// default:				return sizeof(Model3D::Vertex);
		}
		// TODO - ASSERT(false) Throw error if no types match
		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout()
	: m_Stride(0) {};

	template<typename T>
	void Push(unsigned int count) {
		std::runtime_error(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		std::cout << "Pushing float" << std::endl;
		// TODO - Assert size of GL_FLOAT == sizeof float on system
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		std::cout << "Pushing unsigned int" << std::endl;
		// TODO - Assert size of GLuint == sizeof unsigned int on system
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		std::cout << "Pushing unsigned Char" << std::endl;
		// TODO - Assert size of GLbyte == sizeof unsigned char on system
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}	
	
	void PushVertex(unsigned int size)
	{
		std::cout << "Pushing Vertex descriptor" << std::endl;
		// This needs to match our Vertex objects members
		// glm::vec3 position{};	
		// glm::vec3 color{};		
		// glm::vec3 normal{};		
		// glm::vec2 texCoord{};	
		m_Elements.push_back({ GL_FLOAT, 3, GL_TRUE });
		m_Elements.push_back({ GL_FLOAT, 3, GL_TRUE });
		m_Elements.push_back({ GL_FLOAT, 3, GL_TRUE });
		m_Elements.push_back({ GL_FLOAT, 2, GL_TRUE });
		m_Stride += size;
	}

	inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }

private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;
};