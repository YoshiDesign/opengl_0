#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, ShaderSystem& shaderSystem, FrameContent& frame_content) const
{
	frame_content.ubo.Bind();
	glNamedBufferData(frame_content.ubo.getID(), frame_content.ubo.getBlockSize(), NULL, GL_DYNAMIC_DRAW);
	*((glm::mat4*)(frame_content.ubo.getBuffer() + frame_content.ubo.offsets[0])) = frame_content.camera.getView();
	*((glm::mat4*)(frame_content.ubo.getBuffer() + frame_content.ubo.offsets[1])) = frame_content.camera.getProjection();
	/*int x;
	glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_USAGE, &x);
	std::cout << x << std::endl;*/
	for (auto& obj : frame_content.appObjects) {

		void* ptr = glMapNamedBuffer(frame_content.ubo.m_uboId, GL_WRITE_ONLY | GL_MAP_INVALIDATE_BUFFER_BIT);

		*((glm::mat4*)(frame_content.ubo.getBuffer() + frame_content.ubo.offsets[2])) = obj.second.transform._mat4();
		memcpy(ptr, frame_content.ubo.getBuffer(), frame_content.ubo.getBlockSize());

		glUnmapNamedBuffer(frame_content.ubo.getID());
		
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, frame_content.ubo.getID());

		vb.UpdateData(obj.second.model->getVerticesv(), obj.second.model->getNumVertices()); // TODO repeatedly calling getNumVertices... like a noob.
		ib.UpdateData(obj.second.model->getIndicesv(), obj.second.model->getNumIndices());

		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));  // nullptr because the index buffer is already bound
	}

	
}