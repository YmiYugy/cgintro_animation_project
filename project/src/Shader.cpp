#include "Shader.h"

static GLuint compileShader(std::vector<unsigned char> source, GLenum type) {
    GLint size = source.size();
    const auto *const data = reinterpret_cast<const GLchar *const>(source.data());
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &data, &size);
    glCompileShader(shader);
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }
    return shader;
}

static GLuint linkShader(std::vector<GLuint> shaders) {
    GLuint shaderProgram = glCreateProgram();
    for (auto &shader : shaders) {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }
    return shaderProgram;
}

std::shared_ptr<RenderShader>
RenderShaderLoader::load(const std::filesystem::path &vs, const std::filesystem::path &fs) {
    {
        std::vector<GLuint> modules(2);
        modules[0] = compileShader(loadFile(vs.generic_string()), GL_VERTEX_SHADER);
        modules[1] = compileShader(loadFile(fs.generic_string()), GL_FRAGMENT_SHADER);

        GLuint program = linkShader(modules);

        glDeleteShader(modules[0]);
        glDeleteShader(modules[1]);

        return std::make_shared<RenderShader>(RenderShader{program});
    }
}

void Shader::use() {
    glUseProgram(shaderID);
}

GLuint Shader::getUniformLocation(const std::string &name) {
    return glGetUniformLocation(shaderID, name.c_str());
}

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string &name, float x, float y) const {
    glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string &name, const glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
    glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUint(const std::string &name, unsigned int value) const {
    glUniform1ui(glGetUniformLocation(shaderID, name.c_str()), value);
}


std::shared_ptr<ComputeShader> ComputeShaderLoader::load(const std::filesystem::path &sh) {
    return std::make_shared<ComputeShader>(ComputeShader{
            linkShader(std::vector<GLuint>{compileShader(loadFile(sh.generic_string()), GL_COMPUTE_SHADER)})});
}


