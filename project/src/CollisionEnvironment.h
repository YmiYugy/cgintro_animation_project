

#ifndef UNDERWATER_WORLD_COLLISIONENVIRONMENT_H
#define UNDERWATER_WORLD_COLLISIONENVIRONMENT_H

#include "Prototypes.h"
#include "Buffer.h"

struct CollisionObject {
    glm::mat4 model;
    GLuint index_offset;
    GLuint triangle_count;
    glm::vec2 padding_0;
};

struct CollisionEnvironmentObjects {
    std::vector<CollisionObject> collisionObjects;
    void updateUniforms(ComputeShader shader);
};

struct CollisionEnvironmentObjectsBuffer : public Buffer {
    explicit CollisionEnvironmentObjectsBuffer(CollisionEnvironmentObjects objects);
    void bind(ComputeShader shader, GLuint position);
};


#endif //UNDERWATER_WORLD_COLLISIONENVIRONMENT_H
