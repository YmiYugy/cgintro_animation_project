

#ifndef UNDERWATER_WORLD_VERTEXATTRIBUTE_H
#define UNDERWATER_WORLD_VERTEXATTRIBUTE_H

#include "Prototypes.h"

struct VertexAttribute {
    GLuint vao;

    static VertexAttribute texturedVertices(Buffer indexBuffer, Buffer vertexBuffer);
    void bind();
    void boidAttribute(Buffer boids);
};


#endif //UNDERWATER_WORLD_VERTEXATTRIBUTE_H
