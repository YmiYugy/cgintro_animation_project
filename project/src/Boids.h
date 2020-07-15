
#ifndef UNDERWATER_WORLD_BOIDS_H
#define UNDERWATER_WORLD_BOIDS_H

#include "Prototypes.h"
#include "Buffer.h"

const GLuint boids_per_thread = 64;

struct Boid {
    glm::vec4 pos{};
    glm::vec4 dir{};

    Boid(glm::vec3 center, float radius, float speed);
};

struct Boids {
    std::vector<Boid> boids;

    Boids(size_t num_boids, glm::vec3 center, float radius, float speed);

    void updateUniforms(ComputeShader shader);
};

struct BoidBuffers {
    Buffer boid_buffer1{};
    Buffer boid_buffer2{};

    void bind(ComputeShader shader, GLuint position1, GLuint position2);
};






#endif //UNDERWATER_WORLD_BOIDS_H
