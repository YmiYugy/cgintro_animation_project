//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_HELPER_H
#define UNDERWATER_WORLD_HELPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <string>
#include <map>
#include <iostream>
#include <random>
#include <memory>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>
#include <vector>

struct VertexInput {
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

GLuint compileShader(std::vector<unsigned char> source, GLenum type);

GLuint linkShader(std::vector<GLuint> &shaders);

std::vector<glm::vec4> generate_sphere_cloud();

#endif //UNDERWATER_WORLD_HELPER_H
