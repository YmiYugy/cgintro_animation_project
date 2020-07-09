//
// Created by trist on 08/07/2020.
//

#include "Boids.h"
#include "Shader.h"

Boid::Boid(glm::vec3 center, float radius, float speed) {
    pos = glm::vec4(glm::ballRand(radius) + center, 1.0);
    dir = glm::vec4(glm::sphericalRand(speed), 0.0);
}

Boids::Boids(size_t num_boids, glm::vec3 center, float radius, float speed) {
    for(size_t i = 0; i < num_boids; i++) {
        boids.push_back(Boid(center, radius, speed));
    }
}

void Boids::updateUniforms(ComputeShader shader) {
    shader.use();
    shader.setUint("boid_count", boids.size());
}

void BoidBuffers::bind(ComputeShader shader, GLuint position1, GLuint position2) {
    shader.use();
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, position1, boid_buffer1.buffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, position2, boid_buffer2.buffer);
}
