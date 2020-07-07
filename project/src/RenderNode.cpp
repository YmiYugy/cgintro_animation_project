//
// Created by trist on 15/06/2020.
//

#include "RenderNode.h"

//RenderNodes need textures and UVS now. For Shaders without textureloading insert "0"
RenderNode::RenderNode(GLuint EBO, GLuint program, std::vector<void *> UBOs,
                       const std::vector<VertexInput> &vertexInputs, GLuint num_vertices, GLuint num_elements,
                       GLuint num_instances, GLuint texture, GLuint UVs)
        : EBO(EBO), program(program), VAO(0), UBOs(std::move(UBOs)), num_vertices(num_vertices),
          num_elements(num_elements), num_instances(num_instances), texture(texture), UVs(UVs){
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    for (auto &input : vertexInputs) {
        glEnableVertexAttribArray(input.location);
        glBindBuffer(GL_ARRAY_BUFFER, input.VBO);
        glVertexAttribPointer(input.location, input.size, input.type, GL_FALSE, input.stride, (void*)(static_cast<size_t>(input.offset)));
        if (input.instanced) {
            glVertexAttribDivisor(input.location, 1);
        }
    }
    //Binding Textures to Object:
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, UVs);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //
    glBindVertexArray(0);
}

