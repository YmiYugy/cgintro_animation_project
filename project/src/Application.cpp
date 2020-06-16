//
// Created by trist on 15/06/2020.
//

#include <stdexcept>
#include <vector>
#include <fstream>
#include "Application.h"
#include "Helper.h"
#include "Boids.h"

float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
};

unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};


Application &Application::create_app() {
    static Application app;
    return app;
}

Application::Application() {
    window = initWindow();
    setupGL();
    loadScene();
    loadShaders();
    createNodes();
}

Application::~Application() {
    terminateWindow(window);
}

void Application::run() {

    while (!glfwWindowShouldClose(window)) {
        processInput();

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow *Application::initWindow() {
    if (!glfwInit()) throw std::runtime_error("failed to init GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    auto window = glfwCreateWindow(800, 600, "Underwater World", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("failed to create window");
    } else {
        glfwMakeContextCurrent(window);
        return window;
    }
}

void Application::terminateWindow(GLFWwindow *window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::loadGL() {
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("failed to initialize GLAD");
    }
}

void Application::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Application::setupGL() {
    loadGL();
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void Application::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for(auto& node_pair : nodes) {
        auto node = node_pair.second;
        glUseProgram(node->program);
        glBindVertexArray(node->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void Application::loadScene() {
    vertexBuffers["main"] = createBufferWithData(GL_ARRAY_BUFFER ,vertices, sizeof(vertices), GL_STATIC_DRAW);
    elementBuffers["main"] = createBufferWithData(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), GL_STATIC_DRAW);
}

void Application::loadShaders() {
    GLuint vsh = compileShader(loadFile("assets/shaders/vert.glsl"), GL_VERTEX_SHADER);
    GLuint fsh = compileShader(loadFile("assets/shaders/frag.glsl"), GL_FRAGMENT_SHADER);
    std::vector<GLuint> sh = {vsh, fsh};
    GLuint program = linkShader(sh);
    shaders["main"] = program;
    glDeleteShader(vsh);
    glDeleteShader(fsh);
}

void Application::createNodes() {
    std::vector<VertexInput> input = {{
            .location=0,
            .size=3,
            .type=GL_FLOAT,
            .stride=3*sizeof(float),
            .VBO = vertexBuffers["main"],
            .instanced = false
    }};

    GL_FLOAT_MAT4

    Boids node(elementBuffers["main"], shaders["main"], {}, input);
    nodes.insert(std::make_pair("main", std::make_shared<RenderNode>(node)));
}


