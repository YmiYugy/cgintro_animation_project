//
// Created by trist on 15/06/2020.
//

#include "RenderNode.h"

RenderNode::RenderNode(GLuint EBO, GLuint program, std::vector<void *> UBOs,
                       const std::vector<VertexInput> &vertexInputs, GLuint num_vertices, GLuint num_elements,
                       GLuint num_instances)
        : EBO(EBO), program(program), VAO(0), UBOs(std::move(UBOs)), num_vertices(num_vertices),
          num_elements(num_elements), num_instances(num_instances) {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    for (auto &input : vertexInputs) {
        glBindBuffer(GL_ARRAY_BUFFER, input.VBO);
        glEnableVertexAttribArray(input.location);
        glVertexAttribPointer(input.location, input.size, input.type, GL_FALSE, input.stride, (void *) input.offset);
        if (input.instanced) {
            glVertexAttribDivisor(input.location, 1);
        }
    }
    glBindVertexArray(0);
}

