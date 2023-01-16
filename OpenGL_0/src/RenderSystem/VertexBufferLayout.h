#pragma once
#include <vector>
#include <GLEW/glew.h>

// Specifies the Vertex Buffer Layout's attributes
struct VertexBufferElement {
	unsigned int count;
	unsigned int type;
	bool normalized;
};

class VertexBufferLayout {
public:
	VertexBufferLayout()
	: m_Stride(0) {};

	template <typename T>
	void Push(int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(int count)
	{
		// TODO - Assert size of GL_FLOAT == sizeof float on system
		VertexBufferElement el = { GL_FLOAT, count, false };
		m_Elements.push_back(el);
		m_Stride += sizeof(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(int count)
	{
		// TODO - Assert size of GLuint == sizeof unsigned int on system
		VertexBufferElement el = { GL_UNSIGNED_INT, count, false };
		m_Elements.push_back(el);
		m_Stride += sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(int count)
	{
		// TODO - Assert size of GLbyte == sizeof unsigned char on system
		VertexBufferElement el = { GL_UNSIGNED_BYTE, count, true };
		m_Elements.push_back(el);
		m_Stride += sizeof(GLbyte);
	}


	inline const std::vector<VertexBufferElement> getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }

private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;
};