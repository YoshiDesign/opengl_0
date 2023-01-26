#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UpdateData(const unsigned int* data, unsigned int count)
{
    m_count = count;
    // This could cause incompat on certains platforms if !true
    // ASSERT(sizeof unsigned int == sizeof GLuint)
    //std::cout << "Num indices: " << count << std::endl;
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
