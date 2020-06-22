//
// Created by trist on 19/06/2020.
//

#include "SphereCloud.h"

void SphereCloud::render() {
    glUseProgram(program);
    glPointSize(5.0f);
    glBindVertexArray(VAO);
    glEnable(GL_DEPTH_TEST);
    glDrawArrays(GL_POINTS, 0, num_elements);
}

void SphereCloud::updateUBOs(float delta) {
    glUseProgram(program);
    GLint projLoc = glGetUniformLocation(program, "projectionView");
    glm::mat4 projView = *reinterpret_cast<glm::mat4 *>(UBOs[1]) * reinterpret_cast<Camera *>(UBOs[0])->GetViewMatrix();
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projView));
}
