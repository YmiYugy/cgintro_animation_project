//
// Created by trist on 15/06/2020.
//


#include "Helper.h"

GLuint compileShader(std::vector<unsigned char> source, GLenum type) {
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

std::vector<unsigned char> loadFile(const std::string &path) {
    std::ifstream input(path, std::ios::binary);
    return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
}

std::vector<glm::vec4> generate_sphere_cloud() {
    float num_pts = 1000;
    std::vector<float> indices(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        indices[i] = i;
    }

    std::vector<float> phi(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        phi[i] = acosf(1 - 2.0f * indices[i] / static_cast<float>(num_pts));
    }

    std::vector<float> theta(num_pts);

    float sqrt5 = sqrtf(5);
    for (size_t i = 0; i < num_pts; i++) {
        theta[i] = M_PI * (1.0f + sqrt5) * indices[i];
    }

    std::vector<float> x(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        x[i] = cosf(phi[i]);
    }

    std::vector<float> y(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        y[i] = sinf(theta[i]) * sinf(phi[i]);
    }

    std::vector<float> z(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        z[i] = cosf(theta[i]) * sinf(phi[i]);
    }

    std::vector<glm::vec4> points(num_pts + 1);
    points[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    for (size_t i = 0; i < num_pts; i++) {
        points[i + 1] = glm::vec4(x[i], y[i], z[i], 1.0f);
    }

    return points;
}
