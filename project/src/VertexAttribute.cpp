

#include "VertexAttribute.h"
#include "Vertex.h"
#include "Buffer.h"
#include "Boids.h"

VertexAttribute VertexAttribute::texturedVertices(Buffer indexBuffer, Buffer vertexBuffer) {
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer.buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.buffer);
    glVertexAttribPointer(0, 4, GL_FLOAT, false, sizeof(TextureVertex), (void*)offsetof(TextureVertex, pos));
    glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(TextureVertex), (void*)offsetof(TextureVertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(TextureVertex), (void*)offsetof(TextureVertex, texCoord));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return VertexAttribute {
        vao
    };
}

void VertexAttribute::bind() {
    glBindVertexArray(vao);
}

void VertexAttribute::boidAttribute(Buffer boids) {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, boids.buffer);
    glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(Boid), (void*)offsetof(Boid, pos));
    glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(Boid), (void*)offsetof(Boid, dir));
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
