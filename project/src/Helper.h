//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_HELPER_H
#define UNDERWATER_WORLD_HELPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <map>
#include <memory>

struct VertexInput
{
    GLuint location;
    GLint size;
    GLenum type;
    GLsizei stride;
    GLuint VBO;
    GLuint offset;
    bool instanced;
};

std::vector<unsigned char> loadFile(const std::string &path);
GLuint createBufferWithData(GLenum target, void *data, size_t size, GLenum usage);
GLint compileShader(std::vector<unsigned char> source, GLenum type);
GLuint linkShader(std::vector<GLuint> &shaders);

#endif //UNDERWATER_WORLD_HELPER_H
