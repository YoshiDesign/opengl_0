#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "ShaderSystem.h"
#include "Renderer.h"

ShaderSystem::ShaderSystem(const std::string& filepath)
	:	m_Filepath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexShaderSource, source.FragmentShaderSource);

}

ShaderSystem::ShaderSystem(const std::string& vertShader, const std::string& fragShader)
{
}

ShaderSystem::~ShaderSystem()
{
    glDeleteProgram(m_RendererID);
}


unsigned int ShaderSystem::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error Checking
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ")
            << "shader" << std::endl;
        std::cout << "Message: " << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

ShaderProgramSource ShaderSystem::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    
    // Since we're compiling shaders from 1 file, we'll look for the beginning of each program
    // and parse from there.
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }

    }

    return {
        ss[(int)ShaderType::VERTEX].str(),
        ss[(int)ShaderType::FRAGMENT].str()
    };

}

unsigned int ShaderSystem::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

void ShaderSystem::Bind() const
{
    glUseProgram(m_RendererID);
}

void ShaderSystem::Unbind() const
{
    glUseProgram(0);
}

void ShaderSystem::SetUniform1i(const std::string& name, int val)
{
    glUniform1i(GetUniformLocation(name), val);
}

void ShaderSystem::SetUniform1f(const std::string& name, float v1)
{
    glUniform1f(GetUniformLocation(name), v1);
}

void ShaderSystem::SetUniform2f(const std::string& name, const glm::vec2& val)
{
    glUniform2f(GetUniformLocation(name), val.x, val.y);
}

void ShaderSystem::SetUniform3f(const std::string& name, const glm::vec3& val)
{
    glUniform3f(GetUniformLocation(name), val.x, val.y, val.z);
}

void ShaderSystem::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void ShaderSystem::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE , &mat[0][0]);
}

int ShaderSystem::GetUniformLocation(const std::string& name)
{
    // Check the cache first
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    // Find the uniform's target variable within the shader program
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) 
    {
        std::cout << "Uniform " << name << " doesn't exist.";
    }
    
    // Cache location even when location == -1
    m_UniformLocationCache[name] = location;
    return location;
}
