//
// Created by trist on 08/07/2020.
//

#ifndef UNDERWATER_WORLD_CAMERA_H
#define UNDERWATER_WORLD_CAMERA_H

#include "Prototypes.h"

struct Camera {
    glm::vec3 eye = glm::vec3(0.0, 10.0, 10.0);
    glm::vec3 target = glm::vec3(0.0, 5.0, 0.0);
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);

    float fovy = 90.0;
    float aspect = 1.0;
    float zNear = 0.1;
    float zFar = 200.0;

    [[nodiscard]] glm::mat4 projection_matrix() const;

    explicit Camera(const entt::registry& registry);
};


#endif //UNDERWATER_WORLD_CAMERA_H
