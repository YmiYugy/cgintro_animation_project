//
// Created by trist on 22/06/2020.
//

#include "SimpleMesh.h"

void SimpleMesh::render() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, num_elements, GL_UNSIGNED_INT, nullptr);
}

void SimpleMesh::updateUBOs(float delta) {
    glUseProgram(program);
    GLint projLoc = glGetUniformLocation(program, "projectionView");
    glm::mat4 projView = *reinterpret_cast<glm::mat4 *>(UBOs[1]) * reinterpret_cast<Camera *>(UBOs[0])->GetViewMatrix();
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projView));

    GLint modelLoc = glGetUniformLocation(program, "model");
    glm::mat4 model = *reinterpret_cast<glm::mat4 *>(UBOs[2]);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    GLuint textureID = glGetUniformLocation(program, "textureSampler");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(textureID, 0);
}
