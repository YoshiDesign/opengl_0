#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class ShaderSystem {

private:

	unsigned int GetUniformLocation(const std::string& name);
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
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	unsigned int m_RendererID;
	const std::string m_Filepath;
	std::unordered_map<std::string, int> m_UniformLocationCache;

};