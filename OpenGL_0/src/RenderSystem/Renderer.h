#pragma once
#include<iostream>
#include <GLEW/glew.h>
#include "GLFW/glfw3.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderSystem.h"
#include "GameSystem/AppObject.h"
#include "FrameContent.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer {
public:
	void Clear() const;
	void Draw(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, ShaderSystem& shaderSystem, FrameContent& frame_content) const;
private:
	unsigned int m_uboID;
};