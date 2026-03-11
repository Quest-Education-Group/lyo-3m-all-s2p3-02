#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <sstream>

Shader::Shader(std::string const& vertBinaryPath, std::string const& fragBinaryPath)
{
    std::string vertexBinary;
    std::string fragmentBinary;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // open files
    vShaderFile.open(vertBinaryPath);
    fShaderFile.open(fragBinaryPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();		
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexBinary = vShaderStream.str();
    fragmentBinary = fShaderStream.str();	

    uint32 vertex, fragment;
    glShaderBinary(1, &vertex, GL_SHADER_BINARY_FORMAT_SPIR_V, vertexBinary.c_str(), vertexBinary.size() * sizeof(char));
    glShaderBinary(1, &fragment, GL_SHADER_BINARY_FORMAT_SPIR_V, fragmentBinary.c_str(), vertexBinary.size() * sizeof(char));

    m_programId = glCreateProgram();
    glAttachShader(m_programId, vertex);
    glAttachShader(m_programId, fragment);

    glLinkProgram(m_programId);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::SetBool(std::string const& name, bool value)
{
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int) value);
}

void Shader::SetInt(std::string const& name, int value)
{
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::SetFloat(std::string const& name, float value)
{
    glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}

void Shader::SetVec2(std::string const& name, glm::vec2 const& value)
{
    glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(std::string const& name, glm::vec3 const& value)
{
    glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(std::string const& name, glm::vec4 const& value)
{
    glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}

void Shader::SetMat2(std::string const& name, glm::mat2 const& value)
{
    glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat3(std::string const& name, glm::mat3 const& value)
{
    glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(std::string const& name, glm::mat4 const& value)
{
    glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
