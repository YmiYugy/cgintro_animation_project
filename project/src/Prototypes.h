

#ifndef UNDERWATER_WORLD_PROTOTYPES_H
#define UNDERWATER_WORLD_PROTOTYPES_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/core/hashed_string.hpp>
#include <entt/resource/cache.hpp>
#include <entt/entity/registry.hpp>
#include <tiny_obj_loader.h>
#include <string>
#include <filesystem>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <set>
#include <map>
#include <array>
#include <variant>
#include <iostream>
#include <cstdlib>
#include <ctime>

struct Buffer;
struct Camera;
struct CameraController;
class CollisionEnvironment;
struct ComputeShader;
struct TextureMaterial;
struct TextureMaterialLoader;
struct ColorMaterial;
struct ColorMaterialLoader;
struct TexturedMesh;
struct ColoredMesh;
struct MeshBuffers;
struct Renderable;
struct Collidable;
struct ObjectFile;
struct ObjectFileLoader;
class Model;
class ModelLoader;
struct Name;
struct Shader;
struct RenderShaderLoader;
struct Scene;
struct Texture;
struct TextureLoader;
struct Transform;
struct TextureVertex;
struct ColorVertex;
struct CollisionVertex;
class VertexAttribute;
struct WindowAbstraction;
struct CollisionObject;
struct CollisionEnvironmentObjects;
struct CollisionEnvironmentObjectsBuffer;

#endif //UNDERWATER_WORLD_PROTOTYPES_H
