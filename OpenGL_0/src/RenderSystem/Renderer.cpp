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

	// Create the Uniform Block in a temporary buffer. Same as memcpy
	*((glm::mat4*)(frame_content.ubo.getBuffer() + frame_content.ubo.offsets[0])) = frame_content.camera.getView();
	*((glm::mat4*)(frame_content.ubo.getBuffer() + frame_content.ubo.offsets[1])) = frame_content.camera.getProjection();

	// int i = 0;
	for (auto& obj : frame_content.appObjects) {

		obj.second.transform.rotation = glm::vec3(1.0) * ((float)glfwGetTime() * glm::radians(20.0f));

		*((glm::mat4*)(frame_content.ubo.getBuffer() + frame_content.ubo.offsets[2])) = obj.second.transform._mat4();

		glBufferData(GL_UNIFORM_BUFFER, frame_content.ubo.getBlockSize(), frame_content.ubo.getBuffer(), GL_DYNAMIC_DRAW);

		glBindBufferBase(GL_UNIFORM_BUFFER, 0, frame_content.ubo.getID());

		vb.UpdateData(obj.second.model->getVerticesv(), obj.second.model->getNumVertices()); // TODO repeatedly calling getNumVertices... like a noob.
		ib.UpdateData(obj.second.model->getIndicesv(), obj.second.model->getNumIndices());

		// TODO - GL_UNSIGNED_INT is a hardcoded way to typeify our data. It works for an index with a high upper bound. We could be using unsigned short if things remain low-poly.
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));  // nullptr because the index buffer is already bound
	}
	
}