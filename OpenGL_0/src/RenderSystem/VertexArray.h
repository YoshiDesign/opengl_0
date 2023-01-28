#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

//class VertexBufferLayout;

class VertexArray {

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(IndexBuffer& ib, VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;

private:

	unsigned int m_RendererID;

};