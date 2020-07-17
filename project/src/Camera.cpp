
#include "Camera.h"
#include "WindowAbstraction.h"

glm::mat4 Camera::projection_matrix() const  {
    return glm::perspective(glm::radians(fovy), aspect, zNear, zFar) * glm::lookAt(eye, target, up);
}

Camera::Camera(const entt::registry &registry)  {
    GLFWwindow* window = registry.ctx<WindowAbstraction>().window;
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    aspect= static_cast<float>(width)/static_cast<float>(height);
}
