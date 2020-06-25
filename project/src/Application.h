//
// Created by trist on 15/06/2020.
//

#ifndef UNDERWATER_WORLD_APPLICATION_H
#define UNDERWATER_WORLD_APPLICATION_H


#include "Helper.h"
#include "Boids.h"
#include "RenderNode.h"
#include "Camera.h"
#include "SphereCloud.h"
#include "SimpleMesh.h"

class Application {
public:
    static Application &create_app();

    void run();

    Application(Application const &) = delete;

    void operator=(Application const &) = delete;

private:
    const int BOID_NUM = 200 * 64;
    GLFWwindow *window;
    std::map<std::string, GLuint> vertexBuffers;
    std::map<std::string, GLuint> elementBuffers;
    std::map<std::string, GLuint> shaders;
    std::map<std::string, std::shared_ptr<RenderNode>> nodes;
    glm::mat4 projection;
    Camera camera;
    glm::mat4 cubeModel;
    bool firstMouse = false;
    float lastX = 1200 / 2;
    float lastY = 1000 / 2;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    Application();

    ~Application();

    void initWindow();

    static void terminateWindow(GLFWwindow *window);

    static void loadGL();

    void setupGL();

    void loadScene();

    void loadShaders();

    void createNodes();

    void processInput();

    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    void render();
};


#endif //UNDERWATER_WORLD_APPLICATION_H
