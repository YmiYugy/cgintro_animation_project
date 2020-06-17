//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_RENDERNODE_H
#define UNDERWATER_WORLD_RENDERNODE_H

#include <glad/glad.h>
#include <vector>
#include "Helper.h"

struct RenderNode
{
    GLuint EBO;
    GLuint program;
    GLuint VAO;
    std::vector<void *> UBOs;

    RenderNode(GLuint EBO, GLuint program, std::vector<void *> UBOs, const std::vector<VertexInput> &vertexInputs);
    virtual void render() {}
    virtual void updateUBOs() {}
};

#endif //UNDERWATER_WORLD_RENDERNODE_H
