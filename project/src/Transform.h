
#ifndef UNDERWATER_WORLD_TRANSFORM_H
#define UNDERWATER_WORLD_TRANSFORM_H

#include "Prototypes.h"

struct Transform {
    glm::quat rotation{};
    glm::vec3 translation{};
    glm::vec3 scale{};

    Transform();
    [[nodiscard]] glm::mat4 toMat4() const;
};


#endif //UNDERWATER_WORLD_TRANSFORM_H
