//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_RENDERNODE_H
#define UNDERWATER_WORLD_RENDERNODE_H

#include <glad/glad.h>
#include <vector>
#include "Helper.h"

struct RenderNode {
    GLuint VBO;
    GLuint EBO;
    GLuint program;
    GLuint VAO;

    RenderNode(GLuint VBO, GLuint EBO, GLuint program, const std::vector<VertexInput>& vertexInputs);
};


#endif //UNDERWATER_WORLD_RENDERNODE_H
