

#ifndef UNDERWATER_WORLD_SHADER_H
#define UNDERWATER_WORLD_SHADER_H

#include "Prototypes.h"
#include "Helper.h"

struct Shader {
    GLuint shaderID;

    void use();

    GLuint getUniformLocation(const std::string &name);

    void setBool(const std::string &name, bool value) const;

    void setInt(const std::string &name, int value) const;

    void setUint(const std::string &name, unsigned int value) const;

    void setFloat(const std::string &name, float value) const;

    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec2(const std::string &name, float x, float y) const;

    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w);

    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};

struct RenderShader : public Shader {

};

struct RenderShaderLoader final : entt::resource_loader<RenderShaderLoader, RenderShader> {
    static std::shared_ptr<RenderShader> load(const std::filesystem::path &vs, const std::filesystem::path &fs);
};

using RendershaderCache = entt::resource_cache<RenderShader>;

struct ComputeShader : public Shader {

};

struct ComputeShaderLoader final : entt::resource_loader<ComputeShaderLoader, ComputeShader> {
    static std::shared_ptr<ComputeShader> load(const std::filesystem::path &sh);

};

using ComputeShaderCache = entt::resource_cache<ComputeShader>;


#endif //UNDERWATER_WORLD_SHADER_H
