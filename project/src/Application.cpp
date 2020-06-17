//
// Created by trist on 15/06/2020.
//

#include <stdexcept>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Application.h"
#include "Helper.h"
#include "Boids.h"

float vertices[] = {
    1.0f, 1.0f, 0.0f,   // top right
    1.0f, -1.0f, 0.0f,  // bottom right
    -1.0f, -1.0f, 0.0f, // bottom left
    -1.0f, 1.0f, 0.0f   // top left
};

unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

Application &Application::create_app()
{
    static Application app;
    return app;
}

Application::Application()
{
    window = initWindow();
    setupGL();
    loadScene();
    loadShaders();
    createNodes();
}

Application::~Application()
{
    terminateWindow(window);
}

void Application::run()
{

    while (!glfwWindowShouldClose(window))
    {
        processInput();

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

GLFWwindow *Application::initWindow()
{
    if (!glfwInit())
        throw std::runtime_error("failed to init GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    auto window = glfwCreateWindow(800, 600, "Underwater World", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("failed to create window");
    }
    else
    {
        glfwMakeContextCurrent(window);
        return window;
    }
}

void Application::terminateWindow(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::loadGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("failed to initialize GLAD");
    }
}

void Application::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Application::setupGL()
{
    loadGL();
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

void Application::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto &node_pair : nodes)
    {
        node_pair.second->updateUBOs();
        node_pair.second->render();
    }
}

void Application::loadScene()
{
    vertexBuffers["main"] = createBufferWithData(GL_ARRAY_BUFFER, vertices, sizeof(vertices), GL_STATIC_DRAW);
    glm::mat4 model = glm::mat4(1);
    vertexBuffers["boid_positions"] = createBufferWithData(GL_ARRAY_BUFFER, glm::value_ptr(model), sizeof(model), GL_DYNAMIC_DRAW);
    elementBuffers["main"] = createBufferWithData(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices), GL_STATIC_DRAW);
}

void Application::loadShaders()
{
    GLuint vsh = compileShader(loadFile("assets/shaders/boids.vert"), GL_VERTEX_SHADER);
    GLuint fsh = compileShader(loadFile("assets/shaders/main.frag"), GL_FRAGMENT_SHADER);
    std::vector<GLuint> sh = {vsh, fsh};
    GLuint program = linkShader(sh);
    shaders["main"] = program;
    glDeleteShader(vsh);
    glDeleteShader(fsh);
}

void Application::createNodes()
{
    std::vector<VertexInput> input = {
        {
            .location = 0,
            .size = 3,
            .type = GL_FLOAT,
            .stride = 3 * sizeof(GLfloat),
            .VBO = vertexBuffers["main"],
            .instanced = false,
            .offset = 0,
        },
        {
            .location = 1,
            .size = 4,
            .type = GL_FLOAT,
            .stride = 16 * sizeof(GLfloat),
            .VBO = vertexBuffers["boid_positions"],
            .instanced = true,
            .offset = 0 * sizeof(GLfloat),
        },
        {
            .location = 2,
            .size = 4,
            .type = GL_FLOAT,
            .stride = 16 * sizeof(GLfloat),
            .VBO = vertexBuffers["boid_positions"],
            .instanced = true,
            .offset = 4 * sizeof(GLfloat),
        },
        {
            .location = 3,
            .size = 4,
            .type = GL_FLOAT,
            .stride = 16 * sizeof(GLfloat),
            .VBO = vertexBuffers["boid_positions"],
            .instanced = true,
            .offset = 8 * sizeof(GLfloat),
        },
        {
            .location = 4,
            .size = 4,
            .type = GL_FLOAT,
            .stride = 16 * sizeof(GLfloat),
            .VBO = vertexBuffers["boid_positions"],
            .instanced = true,
            .offset = 12 * sizeof(GLfloat),
        },
    };

    Boids node(elementBuffers["main"], shaders["main"], {}, input, 6, 1);
    nodes.insert(std::make_pair("main", std::make_shared<Boids>(node)));
}
