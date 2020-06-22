//
// Created by trist on 16/06/2020.
//

#ifndef UNDERWATER_WORLD_BOIDS_H
#define UNDERWATER_WORLD_BOIDS_H

#include "Helper.h"
#include "RenderNode.h"
#include "Camera.h"

struct Boid {
    glm::vec4 pos;
    glm::vec4 dir;
};

class Boids : public RenderNode {
public:
    Boids(GLuint EBO, GLuint program, std::vector<void *> UBOs, const std::vector<VertexInput> &vertexInputs,
          GLuint vertexCount, GLuint instanceCount);

    void render() override;

    void updateUBOs(float delta) override;

private:
    GLuint boids;
    GLuint compProgram;
    GLuint vertexCount;
    GLuint instanceCount;
    Camera *camera;
    glm::mat4 *projection;

};


#endif //UNDERWATER_WORLD_BOIDS_H
