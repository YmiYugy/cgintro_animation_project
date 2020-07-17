
#ifndef UNDERWATER_WORLD_MODEL_H
#define UNDERWATER_WORLD_MODEL_H

#include "Prototypes.h"

static const std::filesystem::path default_model_folder = "assets/models/";

struct ObjectFile {
    std::string fileName;
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
};

struct ObjectFileLoader final: entt::resource_loader<ObjectFileLoader, ObjectFile> {
    static std::shared_ptr<ObjectFile> load(const std::filesystem::path& path);
};

using ObjectFileCache = entt::resource_cache<ObjectFile>;

struct Model {
    std::string name;
    std::vector<std::pair<TexturedMesh, entt::resource_handle<TextureMaterial>>> texturedMeshes;
    std::vector<std::pair<ColoredMesh, entt::resource_handle<ColorMaterial>>> coloredMeshes;

    std::pair<std::vector<entt::entity>, std::vector<entt::entity>> instantiate(Scene& scene);
};

struct ModelLoader final: entt::resource_loader<ModelLoader, Model> {
    //std::shared_ptr<Model> load(std::string objectFileName, std::string shape_name, Scene& scene);
    std::shared_ptr<Model> load(const ObjectFile &objectFile, uint32_t shape_index, Scene& scene) const;
};

using ModelCache = entt::resource_cache<Model>;


#endif //UNDERWATER_WORLD_MODEL_H
