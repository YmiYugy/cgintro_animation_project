//
// Created by trist on 16/06/2020.
//

#include "Boids.h"

void Boids::render() {
    glUseProgram(program);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, even ? boids : debugBuffer);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Boid), (void *) offsetof(Boid, pos));
    glVertexAttribDivisor(1, 1);
    glEnable(GL_DEPTH_TEST);
    glDrawElementsInstanced(GL_TRIANGLES, num_elements, GL_UNSIGNED_INT, nullptr, num_instances);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Boids::updateUBOs(float delta) {
    glUseProgram(program);
    GLint projLoc = glGetUniformLocation(program, "projectionView");
    glm::mat4 projView = *projection * camera->GetViewMatrix();
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projView));

    glBindBuffer(GL_ARRAY_BUFFER, boids);
    std::vector<Boid> boidVec(num_instances);
    char *data = static_cast<char *>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY));
    memcpy(boidVec.data(), data, sizeof(Boid) * num_instances);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glUseProgram(compProgram);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, even ? boids : debugBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, sceneInfo.elementBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, sceneInfo.vertexBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, samples.vertexBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, even ? debugBuffer : boids);

    GLint deltaLoc = glGetUniformLocation(compProgram, "delta");
    glUniform1f(deltaLoc, delta * 0.6);

    GLint triangleCountLoc = glGetUniformLocation(compProgram, "triangle_count");
    glUniform1ui(triangleCountLoc, sceneInfo.primitiveCount);

    GLint boidCountLoc = glGetUniformLocation(compProgram, "boid_count");
    glUniform1ui(boidCountLoc, boid_count);

    GLint sampleCountLoc = glGetUniformLocation(compProgram, "sample_count");
    glUniform1ui(sampleCountLoc, samples.primitiveCount);

    glDispatchCompute(num_instances / 1024, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
    even = !even;
}

Boids::Boids(GLuint EBO, GLuint program, std::vector<void *> UBOs, const std::vector<VertexInput> &vertexInputs,
             SceneInfo sceneInfo, SceneInfo samples, GLuint num_vertices, GLuint num_elements, GLuint num_instances)
        : RenderNode(EBO, program, UBOs, vertexInputs, num_vertices, num_elements, num_instances),
          boids(vertexInputs[1].VBO), camera(static_cast<Camera *>(UBOs[0])),
          projection(static_cast<glm::mat4 *>(UBOs[1])), sceneInfo(sceneInfo), samples(samples),
          boid_count(num_instances) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexInputs[1].VBO);
    auto pBoid = static_cast<Boid *>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
    for (size_t i = 0; i < num_instances; i++) {
        Boid &boid = pBoid[i];
        boid.pos = glm::vec4(glm::linearRand(glm::vec3(1.5f), glm::vec3(8.5f)), 1.0f);
        boid.dir = glm::vec4(glm::ballRand(1.0f), 0.0f);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);


    debugBuffer = createBufferWithData(GL_ARRAY_BUFFER, nullptr, sizeof(Boid) * num_instances, GL_DYNAMIC_DRAW);
    pBoid = static_cast<Boid *>(glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));
    for (size_t i = 0; i < num_instances; i++) {
        Boid &boid = pBoid[i];
        boid.pos = glm::vec4(0.0f);
        boid.dir = glm::vec4(0.0f);
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);


    auto compCode = loadFile("assets/shaders/boids.comp");
    std::vector<GLuint> compShader = std::vector{compileShader(compCode, GL_COMPUTE_SHADER)};
    compProgram = linkShader(compShader);
    glDeleteShader(compShader[0]);
}