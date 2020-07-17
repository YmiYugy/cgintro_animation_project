

#ifndef UNDERWATER_WORLD_MESH_H
#define UNDERWATER_WORLD_MESH_H

#include "Prototypes.h"
#include "Buffer.h"
#include "Vertex.h"

struct TexturedMesh {
    std::vector<TextureVertex> vertices;
    std::vector<GLuint> indices;
};

struct ColoredMesh {
    std::vector<ColorVertex> vertices;
    std::vector<GLuint> indices;
};

struct CollisionMesh {
    std::vector<CollisionVertex> vertices;
    std::vector<GLuint> indices;

    static std::pair<CollisionMesh, CollisionEnvironmentObjects> fromCollidables(const entt::registry& registry);
};


struct MeshBuffers {
    Buffer indices;
    Buffer vertices;
};

struct RenderMeshBuffers : public MeshBuffers{};
struct CollisionMeshBuffers : public MeshBuffers{};

struct Renderable {
};

struct Collidable {

};

struct Instanced {

};

struct Wireframe {

};


#endif //UNDERWATER_WORLD_MESH_H
