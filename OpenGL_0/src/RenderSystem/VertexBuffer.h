#pragma once

class VertexBuffer {

public:	

	VertexBuffer(/*const void* data, unsigned int size*/);
	~VertexBuffer();

	void Bind() const;
	void UpdateData(const void* data, unsigned int size);
	void Unbind() const;

private: 
	// The 'name' of our buffer. This needs to be an array of n unsigned int's if we're allocating n vertex buffers from here. Right now it's just 1
	unsigned int m_RendererID;

};