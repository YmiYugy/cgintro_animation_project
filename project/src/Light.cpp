//
// Created by trist on 14/07/2020.
//

#include "Light.h"
#include "Shader.h"
#include "Scene.h"

void Light::updateUniforms(RenderShader shader) const {
    shader.setVec3("light.dir", dir);
    shader.setVec3("light.ambient", ambient);
    shader.setVec3("light.diffuse", diffuse);
    shader.setVec3("light.specular", specular);
}

glm::mat4
Light::shadowView(glm::vec3 target, float zNear, float zFar, float left, float top, float right, float bottom) const {
    glm::mat4 proj = glm::ortho(left, right, bottom, top, zNear, zFar);
    glm::mat4 view = glm::lookAt(target + glm::normalize(dir) * ((zFar - zNear) / 2.0f), target, glm::vec3(0, 1, 0));
    return proj * view;
}


