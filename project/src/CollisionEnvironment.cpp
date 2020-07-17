

#include "CollisionEnvironment.h"
#include "Shader.h"

CollisionEnvironmentObjectsBuffer::CollisionEnvironmentObjectsBuffer(CollisionEnvironmentObjects objects) : Buffer(
        objects.collisionObjects.data(), sizeof(CollisionObject) * objects.collisionObjects.size(), GL_STATIC_DRAW) {}

void CollisionEnvironmentObjectsBuffer::bind(ComputeShader shader, GLuint position) {
    shader.use();
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, position, buffer);
}

void CollisionEnvironmentObjects::updateUniforms(ComputeShader shader) {
    shader.use();
    shader.setUint("model_count", collisionObjects.size());
}
