#pragma once


class UBO {
public:
	UBO();
	~UBO();

	void CreateNamedUniformBlock(const char* blockName, unsigned int program, unsigned int num);
	void FreeUniformBlockBuffer(); // Only use where swapping/destroying buffers during lifespan of the derived class, the destructor does the same thing
	void Bind();
	void Unbind();

	inline unsigned char* getBuffer() { return blockBuffer; }
	inline int getBlockSize() { return blockSize; }
	inline unsigned int getID() { return m_UboId; }

private:
	unsigned int m_UboId;
	int blockSize;
	unsigned int ubo_index;
	unsigned char* blockBuffer{nullptr};
};