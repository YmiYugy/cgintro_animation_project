#include "Application.h"

int main() {
    Application::create_app().run();
    /*std::vector<Object> parsedObjects;
    bool res = loadOBJ("assets/models/texturedCube.obj", parsedObjects);
    std::cout << parsedObjects.size() << std::endl;
    /*
    for (int i = 0; i < parsedObjects[0].uvs.size(); i++) {
        std::cout << parsedObjects[0].uvs[i].x << " " << parsedObjects[0].uvs[i].y << std::endl;
    }
    std::cout << parsedObjects[0].vertices.size() << std::endl;

    for (int i = 0; i < parsedObjects[0].vertex_indices.size(); i++) {
        std::cout << parsedObjects[0].vertex_indices[i]<< std::endl;
    }
    */
    return 0;
}