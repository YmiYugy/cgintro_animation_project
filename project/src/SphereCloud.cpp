//
// Created by trist on 19/06/2020.
//

#include "SphereCloud.h"

void SphereCloud::render() {
    glUseProgram(program);
    glPointSize(5.0f);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 100);
}

void SphereCloud::updateUBOs(float delta) {
    glUseProgram(program);
    GLint projLoc = glGetUniformLocation(program, "projectionView");
    int width, height;
    glm::mat4 projView = *reinterpret_cast<glm::mat4 *>(UBOs[1]) * reinterpret_cast<Camera *>(UBOs[0])->GetViewMatrix();
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projView));
}
