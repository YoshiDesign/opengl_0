#include "UBO.h"
#include "Renderer.h"

UBO::UBO()
{
	glGenBuffers(1, &m_UboId);
}

UBO::~UBO()
{
    if (blockBuffer) {
        FreeUniformBlockBuffer();
    }
}

void UBO::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_UboId);
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

    std::cout << "Block Size: " << blockSize << std::endl;

    // Create our temporary buffer for copying data into our shader's uniform 
    blockBuffer = (unsigned char*)malloc(blockSize);

    // Look up the indices within the uniform block
    const char* names[] = { "Transforms.viewMatrix", "Transforms.projectionMatrix", "Transforms.modelMatrix" };
    unsigned int indices[3];
    GLCall(glGetUniformIndices(program, num, &names[0], indices));
    std::cout << "Indices: " << indices[0] << ", " << indices[1] << ", " << indices[2] << std::endl;

    /*
   TODO - Validate indices. Make sure they exist - As unsigned ints their value will be MAX_INTEGER. Use std::numeric_limits<int>::max()
    */

    // Find the byte offsets of our uniform block
    int offset[3];
    GLCall(glGetActiveUniformsiv(program, num, indices, GL_UNIFORM_OFFSET, offset));

}

void UBO::FreeUniformBlockBuffer()
{
    if(blockBuffer) free(blockBuffer);
}

void UBO::Unbind()
{

}