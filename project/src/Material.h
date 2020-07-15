
#ifndef UNDERWATER_WORLD_MATERIAL_H
#define UNDERWATER_WORLD_MATERIAL_H

#include "Prototypes.h"

struct TextureMaterial {
    entt::resource_handle<Texture> diffuseTexture;
};

struct TextureMaterialLoader final : entt::resource_loader<TextureMaterialLoader, TextureMaterial> {
    std::shared_ptr<TextureMaterial> load(tinyobj::material_t material, Scene &scene) const;
};

using TextureMaterialCache = entt::resource_cache<TextureMaterial>;

struct ColorMaterial {
};

struct ColorMaterialLoader final : entt::resource_loader<ColorMaterialLoader, ColorMaterial> {
    static std::shared_ptr<ColorMaterial> load(tinyobj::material_t material) {
        return std::make_shared<ColorMaterial>(ColorMaterial{});
    }
};

using ColorMaterialCache = entt::resource_cache<ColorMaterial>;


#endif //UNDERWATER_WORLD_MATERIAL_H
