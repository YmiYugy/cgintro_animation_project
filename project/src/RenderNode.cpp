//
// Created by trist on 15/06/2020.
//

#include "RenderNode.h"

RenderNode::RenderNode(GLuint VBO, GLuint EBO, GLuint program, const std::vector<VertexInput> &vertexInputs)
        : VBO(VBO), EBO(EBO), program(program), VAO(0) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    for (auto &input : vertexInputs) {
        glEnableVertexAttribArray(input.location);
        glVertexAttribPointer(input.location, input.size, input.type, GL_FALSE, input.stride, (void *) 0);
    }
    glBindVertexArray(0);
}
