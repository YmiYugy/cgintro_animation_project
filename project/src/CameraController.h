

#ifndef UNDERWATER_WORLD_CAMERACONTROLLER_H
#define UNDERWATER_WORLD_CAMERACONTROLLER_H


#include "Prototypes.h"

struct CameraController {
public:
    float velocity = 3.0;
    float velocity_factor = 1.0;
    float sensitivity = 10.0;

    CameraController() = default;
    explicit CameraController(const WindowAbstraction& window);
    void update(float delta, Scene& scene);

private:
    bool grab_cursor = false;
    bool cursor_grabbable = true;
    float lastX{};
    float lastY{};

    void setVelFactor(float f);
    void updateCamera(float delta, glm::vec3 posMovement, glm::vec2 rotMovement, Camera& camera) const;
};


#endif //UNDERWATER_WORLD_CAMERACONTROLLER_H
