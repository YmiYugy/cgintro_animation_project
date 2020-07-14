//
// Created by trist on 08/07/2020.
//

#include "Scene.h"
#include "WindowAbstraction.h"
#include "Camera.h"
#include "CameraController.h"
#include "Transform.h"
#include "Mesh.h"
#include "VertexAttribute.h"
#include "CollisionEnvironment.h"
#include "SamplePoints.h"
#include "Boids.h"
#include "BoidsSimulationParameters.h"

Scene::Scene() {
    std::srand(std::time(nullptr));

    registry.set<WindowAbstraction>(1200, 1000, "Underwater World", registry);
    registry.set<Camera>(registry);
    registry.set<CameraController>();

    auto towerobj = objectFileCache.load<ObjectFileLoader>(entt::hashed_string("wooden_watch_tower2.obj"),
                                                         std::filesystem::path("assets/models/wooden_watch_tower2.obj"));
    auto tower = modelCache.load<ModelLoader>(entt::hashed_string("wooden_watch_tower2.obj"), towerobj, 0, *this)->instantiate(*this).first[0];

    auto cube = objectFileCache.load<ObjectFileLoader>(entt::hashed_string("texturedCube.obj"),
                                                       std::filesystem::path("assets/models/texturedCube.obj"));
    auto cubeMesh = modelCache.load<ModelLoader>(entt::hashed_string("texturedCube.obj"), cube, 0, *this)->instantiate(
            *this).first[0];
    modelCache.load<ModelLoader>(entt::hashed_string("texturedCube.obj"), cube, 0, *this)->instantiate(
            *this);

    renderShaderCache.load<RenderShaderLoader>(entt::hashed_string("forward_model"),
                                               "assets/shaders/forward_model.vert",
                                               "assets/shaders/forward_model.frag");

    registry.view<Renderable>().each([&](auto entity) {
        if (registry.has<TexturedMesh>(entity)) {
            TexturedMesh mesh = registry.get<TexturedMesh>(entity);
            registry.emplace<entt::resource_handle<RenderShader>>(entity, renderShaderCache.handle(
                    entt::hashed_string("forward_model")));
            RenderMeshBuffers &meshBuffers = registry.emplace<RenderMeshBuffers>(entity);
            meshBuffers.vertices = Buffer(mesh.vertices.data(), mesh.vertices.size() * sizeof(TextureVertex),
                                          GL_STATIC_DRAW);
            meshBuffers.indices = Buffer(mesh.indices.data(), mesh.indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
            registry.emplace<VertexAttribute>(entity) = VertexAttribute::texturedVertices(meshBuffers.indices,
                                                                                          meshBuffers.vertices);
        }
        registry.emplace<Transform>(entity);
        registry.emplace<Collidable>(entity);
        //registry.emplace<Wireframe>(entity);
    });

    registry.get<Transform>(cubeMesh).scale *= glm::vec3(8.0, 12.0, 8.0);
    registry.get<Transform>(cubeMesh).translation += glm::vec3(0.0f, 0.9, 0.0);
    registry.remove<Renderable>(cubeMesh);

    registry.get<Transform>(tower).scale *= 2.0;
    //registry.remove<Collidable>(tower);


    {
        auto boids = modelCache.load<ModelLoader>(entt::hashed_string("cone.obj"),
                                                  objectFileCache.load<ObjectFileLoader>(
                                                          entt::hashed_string("cone.obj"), "assets/models/cone.obj"), 0,
                                                  *this)->instantiate(*this).first[0];
        auto shader = renderShaderCache.load<RenderShaderLoader>(entt::hashed_string("forward_boid"),
                                                                 "assets/shaders/forward_boids.vert",
                                                                 "assets/shaders/forward_boids.frag");
        registry.emplace<entt::resource_handle<RenderShader>>(boids, shader);
        auto &transform = registry.emplace<Transform>(boids);
        transform.scale *= 0.1;
        transform.rotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        auto &mesh = registry.get<TexturedMesh>(boids);
        auto &meshBuffers = registry.emplace<RenderMeshBuffers>(boids);
        meshBuffers.indices = Buffer(mesh.indices.data(), mesh.indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
        meshBuffers.vertices = Buffer(mesh.vertices.data(), mesh.vertices.size() * sizeof(TextureVertex),
                                      GL_STATIC_DRAW);
        registry.emplace<VertexAttribute>(boids,
                                          VertexAttribute::texturedVertices(meshBuffers.indices, meshBuffers.vertices));
        registry.emplace<Instanced>(boids);

        auto &boidsData = registry.emplace<Boids>(boids, 128 * 75, glm::vec3(0, 10 ,0), 5.0f, 3.0f);
        auto &boidBuffers = registry.emplace<BoidBuffers>(boids);
        boidBuffers.boid_buffer1 = Buffer(boidsData.boids.data(), boidsData.boids.size() * sizeof(Boid),
                                          GL_STATIC_DRAW);
        boidBuffers.boid_buffer2 = Buffer(boidsData.boids.data(), boidsData.boids.size() * sizeof(Boid), GL_STATIC_DRAW);

        auto[envMesh, coll] = CollisionMesh::fromCollidables(registry);
        auto &collisionMesh = registry.emplace<CollisionMesh>(boids);
        collisionMesh = envMesh;
        auto &collisionMeshBuffers = registry.emplace<CollisionMeshBuffers>(boids);
        collisionMeshBuffers.indices = Buffer(collisionMesh.indices.data(),
                                              collisionMesh.indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
        collisionMeshBuffers.vertices = Buffer(collisionMesh.vertices.data(),
                                               collisionMesh.vertices.size() * sizeof(CollisionVertex), GL_STATIC_DRAW);
        auto &collisionObjects = registry.emplace<CollisionEnvironmentObjects>(boids);
        collisionObjects = coll;
        auto &collisionObjectsBuffer = registry.emplace<CollisionEnvironmentObjectsBuffer>(boids, collisionObjects);

        auto &samples = registry.emplace<SamplePoints>(boids, 25);
        auto &samplesBuffer = registry.emplace<SamplePointsBuffer>(boids, samples);

        auto &simParam = registry.emplace<BoidSimulationParameters>(boids);
        auto &simParamBuffer = registry.emplace<BoidsSimulationParametersBuffer>(boids, simParam);


        auto &computeShader = registry.emplace<entt::resource_handle<ComputeShader>>(boids,
                                                                                    computeShaderCache.load<ComputeShaderLoader>(
                                                                                            entt::hashed_string(
                                                                                                    "boids_compute"),
                                                                                            "assets/shaders/boids.comp"));
    }

    lastFrame = static_cast<float>(glfwGetTime());
}

void Scene::run() {
    while (!glfwWindowShouldClose(registry.ctx<WindowAbstraction>().window)) {
        update();
        render();
        glfwPollEvents();
    }
}

void Scene::update() {
    auto now = static_cast<float>(glfwGetTime());
    float delta = now - lastFrame;
    lastFrame = now;

    if (glfwGetKey(registry.ctx<WindowAbstraction>().window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(registry.ctx<WindowAbstraction>().window, GLFW_TRUE);
    }

    registry.ctx<CameraController>().update(delta, *this);

    glm::mat4 projView = registry.ctx<Camera>().projection_matrix();
    renderShaderCache.each([&](RenderShader &shader) {
        shader.use();
        shader.setMat4("projectionView", projView);
        shader.setVec3("CameraEye", registry.ctx<Camera>().eye);
        shader.setVec4("LightColor", glm::vec4(194.0/255.0, 229.0/255.0, 237.0/255.0, 1.0));
        shader.setVec3("LightPos", glm::vec3(3.0, 25.0, 8.0));
    });

    registry.view<Boids, BoidBuffers, CollisionEnvironmentObjects, CollisionEnvironmentObjectsBuffer,
                    CollisionMeshBuffers, SamplePoints, SamplePointsBuffer, BoidsSimulationParametersBuffer,
                    entt::resource_handle<ComputeShader>, entt::resource_handle<RenderShader>, VertexAttribute>()
            .each([&](entt::entity entity, Boids &boids, BoidBuffers &boidBuffers,
                      CollisionEnvironmentObjects &collEnvObjs, CollisionEnvironmentObjectsBuffer &collEnvObjBuffers,
                      CollisionMeshBuffers &collMeshBuffers, SamplePoints &samples, SamplePointsBuffer &sampleBuffer,
                      BoidsSimulationParametersBuffer &simParamBuffer,
                      entt::resource_handle<ComputeShader> &computeShader,
                      entt::resource_handle<RenderShader> &shader, VertexAttribute &vao) {
                computeShader->use();
                computeShader->setFloat("delta", delta);
                boids.updateUniforms(computeShader);
                collEnvObjs.updateUniforms(computeShader);
                samples.updateUniforms(computeShader);

                boidBuffers.bind(computeShader, 0, 1);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, collMeshBuffers.indices.buffer);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, collMeshBuffers.vertices.buffer);
                collEnvObjBuffers.bind(computeShader, 4);
                glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 5, sampleBuffer.buffer);
                simParamBuffer.bind(computeShader, 0);
                glDispatchCompute(boids.boids.size() / 128, 1, 1);
                glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
                glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
                std::swap(boidBuffers.boid_buffer1, boidBuffers.boid_buffer2);

                shader->use();
                vao.boidAttribute(boidBuffers.boid_buffer1);
            });
}

void Scene::render() {
    glClearColor(2.0/255.0, 123.0/255.0, 150.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto entity : registry.view<entt::resource_handle<RenderShader>, Transform, VertexAttribute, TexturedMesh, entt::resource_handle<TextureMaterial>, Renderable>(
            entt::exclude<Instanced>)) {
        auto &shader = registry.get<entt::resource_handle<RenderShader>>(entity);
        auto &transform = registry.get<Transform>(entity);
        auto &vao = registry.get<VertexAttribute>(entity);
        auto &mesh = registry.get<TexturedMesh>(entity);
        auto &mat = registry.get<entt::resource_handle<TextureMaterial>>(entity);
        glEnable(GL_DEPTH_TEST);
        shader->use();
        shader->setMat4("model", transform.toMat4());
        vao.bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mat->diffuseTexture->texture);
        if(registry.has<Wireframe>(entity)) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(2.0);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
    }

    registry.view<entt::resource_handle<RenderShader>, Transform, VertexAttribute, TexturedMesh, entt::resource_handle<TextureMaterial>, Boids, Renderable, Instanced>()
            .each([&](auto entity, auto &shader, auto &transform, auto &vao, auto &mesh, auto &mat, auto &boids) {
                glEnable(GL_DEPTH_TEST);
                shader->use();
                shader->setMat4("model", transform.toMat4());
                vao.bind();
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, mat->diffuseTexture->texture);
                if(registry.has<Wireframe>(entity)) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                } else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                glDrawElementsInstanced(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, nullptr,
                                        boids.boids.size());
            });

    glfwSwapBuffers(registry.ctx<WindowAbstraction>().window);
}

