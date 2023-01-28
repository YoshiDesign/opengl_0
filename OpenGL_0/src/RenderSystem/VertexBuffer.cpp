#include "VertexBuffer.h"
#include "Renderer.h"
#include "GameSystem/Model3D.h"
VertexBuffer::VertexBuffer(/*const void* data, unsigned int size */)
{
    GLCall(glGenBuffers(1, &m_RendererID));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::UpdateData(const void* data, unsigned int size)
{
    //std::cout << "Num Vertices: " << size << std::endl;
    GLCall(glBufferData(GL_ARRAY_BUFFER, size * sizeof(Model3D::Vertex), data, GL_STATIC_DRAW));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
