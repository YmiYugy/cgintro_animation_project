

#ifndef UNDERWATER_WORLD_WINDOWABSTRACTION_H
#define UNDERWATER_WORLD_WINDOWABSTRACTION_H

#include "Prototypes.h"


struct WindowAbstraction {
    GLFWwindow* window;

    WindowAbstraction(int width, int height, const std::string& title, entt::registry& registry);

    ~WindowAbstraction();

private:
    inline static int num_windows = 0;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};


#endif //UNDERWATER_WORLD_WINDOWABSTRACTION_H
