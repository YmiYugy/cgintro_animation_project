//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_HELPER_H
#define UNDERWATER_WORLD_HELPER_H

#include <string>
#include <glad/glad.h>
#include <vector>

struct VertexInput {
    GLuint location;
    GLint size;
    GLenum type;
    GLsizei stride;
    GLuint VBO;
    bool instanced;
};

std::vector<unsigned char> loadFile(const std::string& path);
GLuint createBufferWithData(GLenum target, void *data, size_t size, GLenum usage);
GLint compileShader(std::vector<unsigned char> source, GLenum type);
GLuint linkShader(std::vector<GLuint>& shaders);




#endif //UNDERWATER_WORLD_HELPER_H
