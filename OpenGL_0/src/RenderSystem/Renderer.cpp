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
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT););
}

void Renderer::Draw(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, const ShaderSystem& shader, FrameContent& frame_content) const
{

	//shader.Bind();
	// va.Bind();

	//frame_content.model_ubo[2] = frame_content.camera.getProjection();
	//frame_content.model_ubo[1] = frame_content.camera.getView();
	// Map UniformBuffer Range for Proj and View Transform
	//pv_transforms = &frame_content.model_ubo[1];
	// Map Uniform Buffer range for Projection and View transforms
	//glUniformMatrix4fv(0, 1, GL_FALSE, frame_content.camera.getProjectionv());
	//glUniformMatrix4fv(1, 1, GL_FALSE, frame_content.camera.getViewv());
	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);

	//glBindBufferBase(GL_UNIFORM_BUFFER, frame_content.transform_ubo_index, frame_content.blockBuffer);
	//glNamedBufferData(frame_content.blockBuffer, sizeof(glm::mat4) * 2, NULL, GL_DYNAMIC_COPY);
	//glm::mat4* pv_transforms = (glm::mat4*) glMapNamedBuffer(frame_content.blockBuffer, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
	//memcpy(blockBuffer + offset[0], innerColor, 4 * sizeof(GLfloat));

	// Create the Uniform Block in a temporary buffer. Same as memcpy
	*((glm::mat4*)(frame_content.ubo.getBuffer() + 0)) = frame_content.camera.getView();
	*((glm::mat4*)(frame_content.ubo.getBuffer() + 64)) = frame_content.camera.getProjection();

	// You are here
	//GLuint uboHandle;
	//glGenBuffers(1, &uboHandle);
	//glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);

	//memcpy(frame_content.blockBuffer + frame_content.offset[0], frame_content.camera.getViewv(), sizeof(glm::mat4));
	//memcpy(frame_content.blockBuffer + frame_content.offset[1], frame_content.camera.getProjectionv(), sizeof(glm::mat4));

	for (auto& obj : frame_content.appObjects) {

		obj.second.transform.rotation = glm::vec3(1.0) * ((float)glfwGetTime() * glm::radians(20.0f));

		//memcpy(frame_content.blockBuffer + frame_content.offset[2], &obj.second.transform._mat4()[0][0], sizeof(glm::mat4));
		*((glm::mat4*)(frame_content.ubo.getBuffer() + 128)) = obj.second.transform._mat4();

		glBufferData(GL_UNIFORM_BUFFER, frame_content.ubo.getBlockSize(), frame_content.ubo.getBuffer(), GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, frame_content.ubo.getID());

		// Add VB
		// vb.Bind();
		vb.UpdateData(obj.second.model->getVerticesv(), obj.second.model->getNumVertices());

		// Add IB
		ib.Bind();
        ib.UpdateData(obj.second.model->getIndicesv(), obj.second.model->getNumIndices());

		//frame_content.model_ubo[0] = obj.second.transform._mat4();
		//glm::mat4* m_transforms = (glm::mat4*)glMapBufferRange(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4) * 2, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
		//m_transforms = &frame_content.model_ubo[0];

		// Map Uniform Buffer Range for Model Transform

		// TODO - GL_UNSIGNED_INT is a hardcoded way to typeify our data. It works for an index with a high upper bound. We could be using unsigned short, for example
		GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));  // nullptr because the index buffer is already bound
	}
}