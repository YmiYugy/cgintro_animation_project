//
// Created by trist on 16/06/2020.
//


#include "Boids.h"

void Boids::render()
{
    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
}

void Boids::updateUBOs()
{
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glUseProgram(program);
    GLint projLoc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindBuffer(GL_ARRAY_BUFFER, positions);
    void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    for(auto i = 0; i < instanceCount; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(static_cast<float>(glfwGetTime()*100) + i*20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 modelView = view * model;
        memcpy(static_cast<char*>(ptr) + i*sizeof(modelView), glm::value_ptr(modelView), sizeof(modelView));
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

Boids::Boids(GLuint EBO, GLuint program, std::vector<void *> UBOs, const std::vector<VertexInput> &vertexInputs, GLuint vertexCount, GLuint instanceCount)
    : RenderNode(EBO, program, UBOs, vertexInputs), positions(vertexInputs[1].VBO), vertexCount(vertexCount), instanceCount(instanceCount)
{
}