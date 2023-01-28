#pragma once
#include "vcorepch.h"
#include <unordered_map>
#include <string>

struct ShaderProgramSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class ShaderSystem {

private:

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);

public:

	ShaderSystem();
	~ShaderSystem();

	// Shaders are in 1 file
	void AddShader(const std::string& filepath, const std::string& key);
	// Separate shader files
	void AddShader(const std::string& vertShader_filepath,
		const std::string& fragShader_filepath,
		const std::string key);

	void Bind(const std::string& key);	// We call it Bind even though OpenGL uses the "glUseProgram" convention
	void Unbind() const;// Again, just being consistent with our Buffer/Array class methods
	inline unsigned int GetID(const std::string& key) { return shaders[key]; };

	// int GetUniformLocation(const std::string& name, const std::string key);
	//void SetUniform1i(const std::string& name, int val);	// Int Uniform Buffer
	//void SetUniform1f(const std::string& name, float v1);	// Float Uniform Buffer
	//void SetUniform2f(const std::string& name, const glm::vec2& val);
	//void SetUniform3f(const std::string& name, const glm::vec3& val);
	//void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3); // Useful as Image Sampler
	//void SetUniformMat4f(const std::string& name, const glm::mat4& mat); // Used for projection matrix

private:
	//unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
	std::unordered_map <std::string, unsigned int> shaders; // <program name, program handle>

};