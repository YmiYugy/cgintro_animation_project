#include "Application.h"

int main() {
    Application::create_app().run();

    //Test:
    /*std::vector<glm::vec3> obj_vertices;
    std::vector<glm::vec3> obj_normals;
    std::vector<glm::vec2> obj_uvs;
    std::vector<unsigned int> obj_indices;
    bool res = loadOBJ("assets/models/testcube.obj", obj_vertices, obj_indices, obj_normals, obj_uvs);
    for (int i = 0; i < obj_vertices.size(); i++) {
        std::cout << obj_vertices[i].x << obj_vertices[i].y << obj_vertices[i].z << std::endl;
    }*/
    

    return 0;
}