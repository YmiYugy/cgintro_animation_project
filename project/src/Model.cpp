//
// Created by trist on 08/07/2020.
//


#define TINYOBJLOADER_IMPLEMENTATION

#include "Model.h"
#include "Scene.h"
#include "Mesh.h"
#include "Name.h"

std::shared_ptr<ObjectFile> ObjectFileLoader::load(const std::filesystem::path &path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.generic_string().c_str(),
                                default_model_folder.generic_string().c_str());

    if (!warn.empty()) {
        std::cerr << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        throw std::runtime_error("failed to load " + path.generic_string());
    }

    return std::make_shared<ObjectFile>(ObjectFile{
            path.filename().generic_string(),attrib, shapes, materials
    });
}

//std::shared_ptr<Model> ModelLoader::load(std::string objectFileName, std::string shape_name, Scene &scene) {
//    auto objectFile = scene.objectFileCache.handle(entt::hashed_string(objectFileName.c_str()));
//    for(size_t i = 0; i < objectFile->shapes.size(); i++) {
//        if(objectFile->shapes[i].name.compare(shape_name) == 0) {
//            return load(objectFileName, i, scene);
//        }
//    }
//    throw std::runtime_error("failed to load model.");
//}

std::shared_ptr<Model> ModelLoader::load(const ObjectFile &objectFile, uint32_t shape_index, Scene &scene) const {
    auto shape = objectFile.shapes[shape_index];
    auto attrib = objectFile.attrib;
    auto materials = objectFile.materials;


    std::unordered_map<int, TexturedMesh> texturedMeshes;
    std::unordered_map<int, std::unordered_map<TextureVertex, GLuint>> uniqueTextureVertices;
    std::unordered_map<int, ColoredMesh> coloredMeshes;
    std::unordered_map<int, std::unordered_map<ColorVertex, GLuint>> uniqueColorVertices;

    size_t index_offset = 0;
    for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
        int fv = shape.mesh.num_face_vertices[f];
        int materialIndex = shape.mesh.material_ids[f];
        for (size_t v = 0; v < fv; v++) {
            tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
            if (materials[materialIndex].diffuse_texname.empty()) {
                ColorVertex vertex = {};
                vertex.pos = {
                        attrib.vertices[3 * idx.vertex_index + 0],
                        attrib.vertices[3 * idx.vertex_index + 1],
                        attrib.vertices[3 * idx.vertex_index + 2],
                        1.0f
                };
                vertex.normal = {
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2],
                        0.0f
                };
                vertex.color = {
                        attrib.colors[3 * idx.vertex_index + 0],
                        attrib.colors[3 * idx.vertex_index + 1],
                        attrib.colors[3 * idx.vertex_index + 2],
                        1.0f
                };

                if (!uniqueColorVertices[materialIndex].contains(vertex)) {
                    uniqueColorVertices[materialIndex][vertex] = static_cast<GLuint>(coloredMeshes[materialIndex].vertices.size());
                    coloredMeshes[materialIndex].vertices.push_back(vertex);
                }
                coloredMeshes[materialIndex].indices.push_back(uniqueColorVertices[materialIndex][vertex]);
            } else {
                TextureVertex vertex = {};
                vertex.pos = {
                        attrib.vertices[3 * idx.vertex_index + 0],
                        attrib.vertices[3 * idx.vertex_index + 1],
                        attrib.vertices[3 * idx.vertex_index + 2],
                        1.0f
                };
                vertex.normal = {
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2],
                        0.0f
                };
                vertex.texCoord = {
                        attrib.texcoords[2 * idx.texcoord_index + 0],
                        attrib.texcoords[2 * idx.texcoord_index + 1],
                };

                if (!uniqueTextureVertices[materialIndex].contains(vertex)) {
                    uniqueTextureVertices[materialIndex][vertex] = static_cast<GLuint>(texturedMeshes[materialIndex].vertices.size());
                    texturedMeshes[materialIndex].vertices.push_back(vertex);
                }
                texturedMeshes[materialIndex].indices.push_back(uniqueTextureVertices[materialIndex][vertex]);
            }
        }
        index_offset += fv;
    }

    std::vector<std::pair<TexturedMesh, entt::resource_handle<TextureMaterial>>> texturedMeshesModel;
    std::vector<std::pair<ColoredMesh, entt::resource_handle<ColorMaterial>>> coloredMeshesModel;

    texturedMeshesModel.reserve(texturedMeshes.size());
    for (const auto&[materialIndex, mesh] : texturedMeshes) {
        texturedMeshesModel.emplace_back(mesh, scene.textureMaterialCache.load<TextureMaterialLoader>(
                entt::hashed_string((objectFile.fileName + "/" + shape.name + "/" + std::to_string(materialIndex)).c_str()),
                materials[materialIndex], scene));
    }

    coloredMeshesModel.reserve(coloredMeshes.size());
    for (const auto&[materialIndex, mesh] : coloredMeshes) {
        coloredMeshesModel.emplace_back(mesh, scene.colorMaterialCache.load<ColorMaterialLoader>(
                entt::hashed_string((objectFile.fileName + "/" + shape.name + "/" + std::to_string(materialIndex)).c_str()),
                materials[materialIndex]));
    }

    return std::make_shared<Model>(Model {objectFile.fileName + "/" + shape.name ,texturedMeshesModel, coloredMeshesModel});
}

std::pair<std::vector<entt::entity>, std::vector<entt::entity>> Model::instantiate(Scene &scene) {
    std::vector<entt::entity> texEntities;
    for(const auto& [mesh, material] : texturedMeshes) {
        auto entity = scene.registry.create();
        scene.registry.emplace<TexturedMesh>(entity, mesh);
        scene.registry.emplace<entt::resource_handle<TextureMaterial>>(entity, material);
        scene.registry.emplace<Name>(entity, name);
        scene.registry.emplace<Renderable>(entity);
        texEntities.push_back(entity);
    }

    std::vector<entt::entity> colorEntities;
    for(const auto& [mesh, material] : coloredMeshes) {
        auto entity = scene.registry.create();
        scene.registry.emplace<ColoredMesh>(entity, mesh);
        scene.registry.emplace<entt::resource_handle<ColorMaterial>>(entity, material);
        scene.registry.emplace<Name>(entity, name);
        scene.registry.emplace<Renderable>(entity);
        colorEntities.push_back(entity);
    }

    return std::make_pair(texEntities, colorEntities);
}
