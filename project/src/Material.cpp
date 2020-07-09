//
// Created by trist on 08/07/2020.
//

#include "Scene.h"
#include "Material.h"
#include "Texture.h"


std::shared_ptr<TextureMaterial> TextureMaterialLoader::load(tinyobj::material_t material, Scene &scene) const {
    auto diffuseFileName = std::filesystem::path(material.diffuse_texname).filename();
    return std::make_shared<TextureMaterial>(TextureMaterial{scene.textureCache.load<TextureLoader>(
            entt::hashed_string(diffuseFileName.generic_string().c_str()), default_texture_folder/diffuseFileName)});
}