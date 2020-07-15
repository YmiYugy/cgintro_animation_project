
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
#include "Light.h"

Scene::Scene() {
    std::srand(std::time(nullptr));

    registry.set<WindowAbstraction>(1200, 1000, "Underwater World", registry);
    registry.set<Camera>(registry);
    registry.set<CameraController>();
    registry.set<Light>(Light{
            .dir = glm::vec3(-0.2f, -1.0f, -0.3f),
            .ambient = glm::vec3(2.0 / 255.0, 123.0 / 255.0, 150.0 / 255.0),
            .diffuse = glm::vec3(194.0 / 255.0, 229.0 / 255.0, 237.0 / 255.0),
            .specular = glm::vec3(1.0)
    });

    auto rocks = objectFileCache.load<ObjectFileLoader>(entt::hashed_string("rock_formation.obj"),
                                                        std::filesystem::path("assets/models/rock_formation.obj"));
    auto rocksMesh = modelCache.load<ModelLoader>(entt::hashed_string("rock_formation.obj"), rocks, 0,
                                                  *this)->instantiate(*this).first[0];

    auto ship = objectFileCache.load<ObjectFileLoader>(entt::hashed_string("ship.obj"),
                                                       std::filesystem::path("assets/models/ship.obj"));
    auto shipMesh = modelCache.load<ModelLoader>(entt::hashed_string("ship.obj"), ship, 0, *this)->instantiate(
            *this).first[0];

    auto corals = objectFileCache.load<ObjectFileLoader>(entt::hashed_string("coral_2d_formation.obj"),
                                                         std::filesystem::path("assets/models/coral_2d_formation.obj"));
    auto coralsMesh = modelCache.load<ModelLoader>(entt::hashed_string("coral_2d_formation.obj"), corals, 0,
                                                   *this)->instantiate(*this).first[0];

    auto cube = objectFileCache.load<ObjectFileLoader>(entt::hashed_string("ground.obj"),
                                                       std::filesystem::path("assets/models/ground.obj"));
    auto cubeMesh = modelCache.load<ModelLoader>(entt::hashed_string("ground.obj"), cube, 0, *this)->instantiate(
            *this).first[0];

    modelCache.load<ModelLoader>(entt::hashed_string("ground.obj"), cube, 0, *this)->instantiate(
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

    registry.get<Transform>(cubeMesh).scale *= glm::vec3(20.0, 20.0, 20.0);
    registry.remove<Renderable>(cubeMesh);


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

        auto &boidsData = registry.emplace<Boids>(boids, 128 * 40, glm::vec3(0, 10, 0), 5.0f, 3.0f);
        auto &boidBuffers = registry.emplace<BoidBuffers>(boids);
        boidBuffers.boid_buffer1 = Buffer(boidsData.boids.data(), boidsData.boids.size() * sizeof(Boid),
                                          GL_STATIC_DRAW);
        boidBuffers.boid_buffer2 = Buffer(boidsData.boids.data(), boidsData.boids.size() * sizeof(Boid),
                                          GL_STATIC_DRAW);

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

        auto &samples = registry.emplace<SamplePoints>(boids, 15);
        auto &samplesBuffer = registry.emplace<SamplePointsBuffer>(boids, samples);

        auto &simParam = registry.emplace<BoidSimulationParameters>(boids);
        auto &simParamBuffer = registry.emplace<BoidsSimulationParametersBuffer>(boids, simParam);


        auto &computeShader = registry.emplace<entt::resource_handle<ComputeShader>>(boids,
                                                                                     computeShaderCache.load<ComputeShaderLoader>(
                                                                                             entt::hashed_string(
                                                                                                     "boids_compute"),
                                                                                             "assets/shaders/boids.comp"));
    }

    {
        const GLuint shadowMapWidth = 1024, shadowMapHeight = 1024;
        glGenFramebuffers(1, &depthFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                               textureCache.load<DepthTextureLoader>(entt::hashed_string("shadow_map"), shadowMapWidth,
                                                                     shadowMapHeight)->texture, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
                //glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
                //glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);
                std::swap(boidBuffers.boid_buffer1, boidBuffers.boid_buffer2);

                shader->use();
                vao.boidAttribute(boidBuffers.boid_buffer1);
            });
}

void Scene::render() {
    glm::mat4 projView = registry.ctx<Camera>().projection_matrix();
    renderShaderCache.each([&](RenderShader &shader) {
        shader.use();
        shader.setMat4("projectionView", projView);
        shader.setVec3("cameraEye", registry.ctx<Camera>().eye);
        registry.ctx<Light>().updateUniforms(shader);
    });


    glm::vec3 clearColor = registry.ctx<Light>().ambient;
    glClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    registry.view<entt::resource_handle<RenderShader>, Transform, VertexAttribute, Renderable>()
            .each([&](auto entity, auto &shader, auto &transform, auto &vao) {
                GLuint index_count = static_cast<GLuint>(registry.has<TexturedMesh>(entity) ?
                                                         registry.get<TexturedMesh>(entity).indices.size() :
                                                         (registry.has<ColoredMesh>(entity) ?
                                                          registry.get<ColoredMesh>(entity).indices.size() : 0));

                glEnable(GL_DEPTH_TEST);
                shader->use();
                shader->setMat4("model", transform.toMat4());
                shader->setMat4("normalModel", glm::transpose(glm::inverse(transform.toMat4())));
                vao.bind();
                if (registry.has<entt::resource_handle<TextureMaterial>>(entity)) {
                    auto &mat = registry.get<entt::resource_handle<TextureMaterial>>(entity);
                    mat->updateUniforms(shader);
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, mat->diffuseTexture->texture);
                }
                if (registry.has<Wireframe>(entity)) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                } else {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                if (registry.has<Instanced>(entity) && registry.has<Boids>(entity)) {
                    glDrawElementsInstanced(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr,
                                            registry.get<Boids>(entity).boids.size());
                } else {
                    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
                }
            });

    glfwSwapBuffers(registry.ctx<WindowAbstraction>().window);
}

