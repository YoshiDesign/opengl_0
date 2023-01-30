#pragma once
#include "Renderer.h"
#include <unordered_map>

class Texture 
{
public:
	Texture();
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	void Add3DTexture(const std::string& path);
	void Add2DTexture(const std::string& path);

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererID;
	int m_Width, m_Height, m_BPP;
	unsigned char* m_TextureID; // This always gets allocated and then freed from the same routine. We don't need more than 1 right now

};