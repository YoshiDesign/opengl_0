#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class ShaderSystem {

private:

	int GetUniformLocation(const std::string& name);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);

public:
	// All shaders in 1 file
	ShaderSystem(const std::string& filepath);
	// Separate shader files
	ShaderSystem(const std::string& vertShader, const std::string& fragShader);

	~ShaderSystem();

	void Bind() const;	// We call it Bind even though OpenGL uses the "glUseProgram" convention
	void Unbind() const;	// Again, just being consistent with our Buffer/Array class methods

	// Set uniforms
	void SetUniform1i(const std::string& name, int val);	// Int Uniform Buffer
	void SetUniform1f(const std::string& name, float v1);	// Float Uniform Buffer
	void SetUniform2f(const std::string& name, const glm::vec2& val);
	void SetUniform3f(const std::string& name, const glm::vec3& val);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3); // Useful as Image Sampler
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat); // Used for projection matrix

private:
	unsigned int m_RendererID;
	const std::string m_Filepath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

};