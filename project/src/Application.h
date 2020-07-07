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
#include "ObjLoader.h"

class Application {
public:
    static Application &create_app();

    void run();

    Application(Application const &) = delete;

    void operator=(Application const &) = delete;

private:
    const int BOID_NUM = 15 * Boids::BOIDS_PER_WORK_GROUP;
    GLFWwindow *window;
    std::map<std::string, GLuint> vertexBuffers;
    std::map<std::string, GLuint> elementBuffers;
    std::map<std::string, GLuint> uvBuffers;
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
    double lastSample = 0;
    uint32_t framesSinceSample = 0;
    std::vector<Object> parsedObjects;
    std::vector<GLuint> vBuffers;
    std::vector<GLuint> eBuffers;
    std::vector<GLuint> uBuffers;

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

    void showFPS();

    void render();

    SimpleMesh Application::createParsedObjectNode(int i);
};


#endif //UNDERWATER_WORLD_APPLICATION_H
