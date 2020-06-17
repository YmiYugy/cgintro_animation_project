//
// Created by trist on 15/06/2020.
//


#include "Helper.h"

GLint compileShader(std::vector<unsigned char> source, GLenum type)
{
    GLint size = source.size();
    const auto *const data = reinterpret_cast<const GLchar *const>(source.data());
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &data, &size);
    glCompileShader(shader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }
    return shader;
}

GLuint linkShader(std::vector<GLuint> &shaders)
{
    GLuint shaderProgram = glCreateProgram();
    for (auto &shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }
    return shaderProgram;
}

GLuint createBufferWithData(GLenum target, void *data, size_t size, GLenum usage)
{
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(target, VBO);
    glBufferData(target, size, data, usage);
    return VBO;
}

std::vector<unsigned char> loadFile(const std::string &path)
{
    std::ifstream input(path, std::ios::binary);
    return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
}