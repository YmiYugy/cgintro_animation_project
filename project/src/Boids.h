//
// Created by trist on 16/06/2020.
//

#ifndef UNDERWATER_WORLD_BOIDS_H
#define UNDERWATER_WORLD_BOIDS_H

#include "RenderNode.h"

struct Boids : public RenderNode {
public:
    Boids (GLuint EBO, GLuint program, std::vector<void *> UBOs, const std::vector<VertexInput> &vertexInputs, GLuint vertexCount, GLuint instanceCount);

    void render() override;
    void updateUBOs() override;

private:
    GLuint positions;
    GLuint vertexCount;
    GLuint instanceCount;
};


#endif //UNDERWATER_WORLD_BOIDS_H
