
#include "Mesh.h"
#include "CollisionEnvironment.h"
#include "Transform.h"

std::pair<CollisionMesh, CollisionEnvironmentObjects> CollisionMesh::fromCollidables(const entt::registry &registry) {
    std::vector<CollisionVertex> vertices;
    std::vector<GLuint> indices;
    std::vector<CollisionObject> collisionObjects;
    std::unordered_map<CollisionVertex, GLuint> uniqueVertices;
    registry.view<const Transform, const TexturedMesh, const Collidable>().each([&](const auto entity, const Transform &transform, const TexturedMesh& mesh) {
        collisionObjects.push_back(CollisionObject{
                .model = transform.toMat4(),
                .index_offset = static_cast<GLuint>(indices.size()),
                .triangle_count = static_cast<GLuint>(mesh.indices.size() / 3),
                .padding_0 = glm::vec2()
        });
        for (const auto &index : mesh.indices) {
            CollisionVertex vertex = {
                    .pos = mesh.vertices[index].pos
            };

            if (!uniqueVertices.contains(vertex)) {
                uniqueVertices[vertex] = vertices.size();
                vertices.push_back(vertex);
            }
            indices.push_back(uniqueVertices[vertex]);
        }
    });

    registry.view<const Transform, const ColoredMesh, const Collidable>().each([&](const auto entity, const Transform &transform, const ColoredMesh& mesh) {
        collisionObjects.push_back(CollisionObject{
                .model = transform.toMat4(),
                .index_offset = static_cast<GLuint>(indices.size()),
                .triangle_count = static_cast<GLuint>(mesh.indices.size() / 3),
                .padding_0 = glm::vec2()
        });
        for (const auto &index : mesh.indices) {
            CollisionVertex vertex = {
                    .pos = mesh.vertices[index].pos
            };

            if (!uniqueVertices.contains(vertex)) {
                uniqueVertices[vertex] = vertices.size();
                vertices.push_back(vertex);
            }
            indices.push_back(uniqueVertices[vertex]);
        }
    });

    return std::make_pair(CollisionMesh{
            vertices, indices
    }, CollisionEnvironmentObjects{
            collisionObjects
    });
}
