#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "Texture.h"

Texture::Texture()
	: m_RendererID(0), m_TextureID(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Add3DTexture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	m_TextureID = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// These first 4 parameters are required
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	  // Don't extend the texture's area
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	  // Don't tile the texture

	// Describe the memory layout to be allocated on the GPU
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, m_Width / 16, m_Height / 16, 0, 16, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureID);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_TextureID)
		stbi_image_free(m_TextureID);
}

void Texture::Add2DTexture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	m_TextureID = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	// These first 4 parameters are required
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	  // Don't extend the texture's area
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	  // Don't tile the texture

	// Describe the memory layout to be allocated on the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_TextureID);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_TextureID)
		stbi_image_free(m_TextureID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	// Designate the texture we want to render
	glActiveTexture(GL_TEXTURE0 + slot);	// We can add slot because the GL_TEXTUREN slots are sequentially enumerated
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
}