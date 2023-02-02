#include "UBO.h"
#include "Renderer.h"

UBO::UBO()
{
	glGenBuffers(1, &m_uboId);
}

UBO::~UBO()
{
    if (blockBuffer) {
        FreeUniformBlockBuffer();
    }
}

void UBO::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_uboId);
}

/*
 * TODO: Make CreateNamedUniformBlock a static builder that returns a unique ptr to a UBO
 *       Dynamic name lookups
 */
void UBO::CreateNamedUniformBlock(const char* blockName, unsigned int program, unsigned int num)
{
    // This uniform block already has memory. Don
    if (blockBuffer) {
        free(blockBuffer);
        throw std::runtime_error("[Error] UBO::CreateUniformBlock - A buffer with this name is already allocated.");
    }

    // Find the Index of the Named block
    ubo_index = glGetUniformBlockIndex(program, "Transforms");
    
    // Find the size of this uniform block
    GLCall(glGetActiveUniformBlockiv(program, ubo_index, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize));

    // Create our temporary buffer for copying data into our shader's uniform 
    blockBuffer = (unsigned char*)malloc(blockSize);

    // Look up the indices within the uniform block
    const char* names[] = { "Transforms.viewMatrix", "Transforms.projectionMatrix", "Transforms.modelMatrix" };
    
    GLCall(glGetUniformIndices(program, num, &names[0], indices));

    /*
   TODO - Validate indices. Make sure they exist - As unsigned ints their value will be MAX_INTEGER. Use std::numeric_limits<int>::max()
    */

    // Find the byte offsets of our uniform block
    
    GLCall(glGetActiveUniformsiv(program, num, indices, GL_UNIFORM_OFFSET, offsets));

}

//void UBO::PushBufferSegment(int type, int size)
//{
//    
//}

void UBO::FreeUniformBlockBuffer()
{
    if(blockBuffer) free(blockBuffer);
}

void UBO::Unbind()
{

}