//
// Created by trist on 08/07/2020.
//

#ifndef UNDERWATER_WORLD_SCENE_H
#define UNDERWATER_WORLD_SCENE_H

#include "Prototypes.h"
#include "Texture.h"
#include "Material.h"
#include "Model.h"
#include "Shader.h"

struct Scene {

    Scene();
    void run();

    entt::registry registry;
    TextureCache textureCache;
    TextureMaterialCache textureMaterialCache;
    ColorMaterialCache colorMaterialCache;
    ObjectFileCache objectFileCache;
    ModelCache modelCache;
    RendershaderCache renderShaderCache;
    ComputeShaderCache computeShaderCache;

private:
    float lastFrame;

    void update();
    void render();
};


#endif //UNDERWATER_WORLD_SCENE_H
