//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_RENDERNODE_H
#define UNDERWATER_WORLD_RENDERNODE_H

#include "Helper.h"

struct RenderNode {
    GLuint EBO;
    GLuint program;
    GLuint VAO;
    std::vector<void *> UBOs;
    GLuint num_vertices;
    GLuint num_elements;
    GLuint num_instances;
    GLuint texture;
    GLuint UVS;

    RenderNode(GLuint EBO, GLuint program, std::vector<void *> UBOs, const std::vector<VertexInput> &vertexInputs,
               GLuint num_vertices, GLuint num_elements, GLuint num_instances, GLuint texture, GLuint UVS);

    virtual void render() {}

    virtual void updateUBOs(float delta) {}
};

#endif //UNDERWATER_WORLD_RENDERNODE_H
