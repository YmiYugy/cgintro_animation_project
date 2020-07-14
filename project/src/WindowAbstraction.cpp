

#include "WindowAbstraction.h"
#include "Camera.h"

WindowAbstraction::WindowAbstraction(int width, int height, const std::string &title, entt::registry &registry) {
    if(num_windows == 0) {
        if (!glfwInit())
            throw std::runtime_error("failed to init GLFW");
    }
    num_windows++;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("failed to create window");
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window, &registry);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("failed to initialize GLAD");
    }
    glViewport(0, 0, width, height);
}

WindowAbstraction::~WindowAbstraction() {
    if(window != nullptr) {
        glfwDestroyWindow(window);
        if(--num_windows == 0) {
            glfwTerminate();
        }
    }
}

void WindowAbstraction::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    auto* registry = static_cast<entt::registry*>(glfwGetWindowUserPointer(window));
    registry->ctx<Camera>().aspect = static_cast<float>(width)/static_cast<float>(height);
}
