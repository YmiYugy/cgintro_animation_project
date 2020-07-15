

#include "Scene.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"


std::shared_ptr<TextureMaterial> TextureMaterialLoader::load(tinyobj::material_t material, Scene &scene) const {
    auto diffuseFileName = std::filesystem::path(material.diffuse_texname).filename();
    glm::vec3 ambient(material.ambient[0], material.ambient[1], material.ambient[2]);
    glm::vec3 diffuse(material.diffuse[0], material.diffuse[1], material.diffuse[2]);
    glm::vec3 specular(material.specular[0], material.specular[1], material.specular[2]);
    float shininess = material.shininess;

    return std::make_shared<TextureMaterial>(TextureMaterial{
            .diffuseTexture = scene.textureCache.load<TextureLoader>(
                    entt::hashed_string(diffuseFileName.generic_string().c_str()),
                    default_texture_folder / diffuseFileName),
            .specular = specular,
            .shininess = shininess
    });
}

void TextureMaterial::updateUniforms(RenderShader shader) const {
    shader.setVec3("material.specular", specular);
    shader.setFloat("material.shininess", shininess);
}
