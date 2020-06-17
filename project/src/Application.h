//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_APPLICATION_H
#define UNDERWATER_WORLD_APPLICATION_H

#include "Helper.h"
#include "Boids.h"

class Application {
public:
    static Application& create_app();
    void run();
    Application(Application const&)     = delete;
    void operator=(Application const&)  = delete;

private:
    GLFWwindow* window;
    std::map<std::string, GLuint> vertexBuffers;
    std::map<std::string, GLuint> elementBuffers;
    std::map<std::string, GLuint> shaders;
    std::map<std::string, std::shared_ptr<RenderNode>> nodes;

    Application();
    ~Application();

    static GLFWwindow* initWindow();
    static void terminateWindow(GLFWwindow* window);
    static void loadGL();
    void setupGL();
    void loadScene();
    void loadShaders();
    void createNodes();

    void processInput();
    void render();
};



#endif //UNDERWATER_WORLD_APPLICATION_H
