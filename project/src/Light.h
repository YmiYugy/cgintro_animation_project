//
// Created by trist on 14/07/2020.
//

#ifndef UNDERWATER_WORLD_LIGHT_H
#define UNDERWATER_WORLD_LIGHT_H

#include "Prototypes.h"

struct Light {
    glm::vec3 dir;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    void updateUniforms(RenderShader shader) const;

    glm::mat4
    shadowView(glm::vec3 target, float zNear, float zFar, float left, float top, float right, float bottom) const;
};


#endif //UNDERWATER_WORLD_LIGHT_H
