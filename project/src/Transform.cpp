//
// Created by trist on 08/07/2020.
//

#include "Transform.h"

Transform::Transform() {
    rotation = glm::quat(1.0, 0.0, 0.0, 0.0);
    translation = glm::vec3(0.0);
    scale = glm::vec3(1.0);
}

glm::mat4 Transform::toMat4() const {
    glm::mat4 model(1.0);
    model = glm::scale(model, scale);
    model = glm::toMat4(rotation) * model;
    model = glm::translate(model, translation);
    return model;
}

