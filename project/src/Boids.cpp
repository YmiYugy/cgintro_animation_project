//
// Created by trist on 16/06/2020.
//

#include "Boids.h"

void Boids::render() {
    glUseProgram(program);
    glBindVertexArray(VAO);
    glDrawElementsInstanced(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
}

void Boids::updateUBOs(float delta) {
    glUseProgram(program);
    GLint projLoc = glGetUniformLocation(program, "projectionView");
    int width, height;
    glm::mat4 projView = *projection * camera->GetViewMatrix();
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projView));

//    glBindBuffer(GL_ARRAY_BUFFER, boids);
//    auto pBoid = static_cast<Boid *>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
//    for (size_t i = 0; i < instanceCount; i++) {
//        Boid& boid = pBoid[i];
//        boid.pos += (delta > 0.05 ? 0.0f : delta) * 0.8f * boid.dir;
//    }
//    glUnmapBuffer(GL_ARRAY_BUFFER);
    if (delta <= 0.05) {
        glUseProgram(compProgram);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, boids);
        GLint deltaLoc = glGetUniformLocation(compProgram, "delta");
        glUniform1f(deltaLoc, delta * 0.6);
        glDispatchCompute(instanceCount / 64, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
    }
}

Boids::Boids(GLuint EBO, GLuint program, std::vector<void *> UBOs, const std::vector<VertexInput> &vertexInputs,
             GLuint vertexCount, GLuint instanceCount)
        : RenderNode(EBO, program, UBOs, vertexInputs), boids(vertexInputs[1].VBO), vertexCount(vertexCount),
          instanceCount(instanceCount), camera(static_cast<Camera *>(UBOs[0])),
          projection(static_cast<glm::mat4 *>(UBOs[1])) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexInputs[1].VBO);
    auto pBoid = static_cast<Boid *>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
    for (size_t i = 0; i < instanceCount; i++) {
        Boid &boid = pBoid[i];
        boid.pos = glm::vec4(glm::linearRand(glm::vec3(0.0f), glm::vec3(1.0f)), 1.0f);
        boid.dir = glm::vec4(glm::ballRand(1.0f), 0.0f);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);

    auto compCode = loadFile("assets/shaders/boids.comp");
    std::vector<GLuint> compShader = std::vector{compileShader(compCode, GL_COMPUTE_SHADER)};
    compProgram = linkShader(compShader);
    glDeleteShader(compShader[0]);
}