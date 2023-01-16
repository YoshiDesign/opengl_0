#pragma once
#include "VertexBuffer.h"

class VertexArray {

public:

	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout);

private:

};