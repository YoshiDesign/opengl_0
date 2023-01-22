#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

//class VertexBufferLayout;

class VertexArray {

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout, unsigned int elem_size);
	void Bind() const;
	void Unbind() const;

private:

	unsigned int m_RendererID;

};