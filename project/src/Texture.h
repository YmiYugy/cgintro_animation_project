
#ifndef UNDERWATER_WORLD_TEXTURE_H
#define UNDERWATER_WORLD_TEXTURE_H

#include "Prototypes.h"

static const std::filesystem::path default_texture_folder = "assets/textures/";

struct Texture {
    GLuint texture;
    int width;
    int height;
};

struct TextureLoader final: entt::resource_loader<TextureLoader, Texture> {
    std::shared_ptr<Texture> load(const std::filesystem::path& path) const;
};

using TextureCache = entt::resource_cache<Texture>;


#endif //UNDERWATER_WORLD_TEXTURE_H
