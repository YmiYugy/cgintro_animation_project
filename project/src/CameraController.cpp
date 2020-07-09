//
// Created by trist on 08/07/2020.
//

#include "CameraController.h"
#include "WindowAbstraction.h"
#include "Camera.h"
#include "Scene.h"

CameraController::CameraController(const WindowAbstraction& window) {
    double x, y;
    glfwGetCursorPos(window.window, &x, &y);
    lastX = static_cast<float>(x);
    lastY = static_cast<float>(y);
}

void CameraController::setVelFactor(float f) {
    velocity_factor = f;
}

void CameraController::updateCamera(float delta, glm::vec3 posMovement, glm::vec2 rotMovement, Camera &camera) const {
    glm::vec3 movementDelta = delta * velocity_factor * velocity * posMovement;
    glm::vec3 dir = glm::normalize((camera.target - camera.eye));
    glm::vec3 right = glm::cross(dir, camera.up);
    glm::vec3 up = camera.up;

    camera.target += right * movementDelta.x;
    camera.eye += right * movementDelta.x;

    camera.target += up * movementDelta.y;
    camera.eye += up * movementDelta.y;

    camera.target += dir * movementDelta.z;
    camera.eye += dir * movementDelta.z;

    glm::quat pitch= glm::angleAxis(glm::radians(-rotMovement.y * 0.01f), right);
    glm::quat yaw = glm::angleAxis(glm::radians(-rotMovement.x * 0.01f), up);
    camera.target = camera.eye + glm::rotate(pitch * yaw, camera.target-camera.eye);
}

void CameraController::update(float delta, Scene& scene) {
    float forward = glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_W) == GLFW_PRESS ? 1 : 0;
    forward -= glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_S) == GLFW_PRESS ? 1 : 0;
    float right = glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_D) == GLFW_PRESS ? 1 : 0;
    right -= glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_A) == GLFW_PRESS ? 1 : 0;
    float up = glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_SPACE) == GLFW_PRESS ? 1 : 0;
    up -= glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 1 : 0;
    setVelFactor(glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ? 5 : 1);

    if(glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_G) == GLFW_PRESS && cursor_grabbable) {
        grab_cursor = !grab_cursor;
        cursor_grabbable = false;
        if(grab_cursor) {
            glfwSetInputMode(scene.registry.ctx<WindowAbstraction>().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            if (glfwRawMouseMotionSupported())
                glfwSetInputMode(scene.registry.ctx<WindowAbstraction>().window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

        } else {
            if (glfwRawMouseMotionSupported())
                glfwSetInputMode(scene.registry.ctx<WindowAbstraction>().window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
            glfwSetInputMode(scene.registry.ctx<WindowAbstraction>().window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    } else if(glfwGetKey(scene.registry.ctx<WindowAbstraction>().window, GLFW_KEY_G) == GLFW_RELEASE) {
        cursor_grabbable = true;
    }
    glm::vec2 cam_rot(0.0);
    double x, y;
    glfwGetCursorPos(scene.registry.ctx<WindowAbstraction>().window, &x, &y);
    if(grab_cursor) {
        cam_rot = sensitivity * glm::vec2(x-lastX, y-lastY);
    }
    lastX = static_cast<float>(x);
    lastY = static_cast<float>(y);

    updateCamera(delta, glm::vec3(right, up, forward), cam_rot, scene.registry.ctx<Camera>());
}