//
// Created by trist on 08/07/2020.
//

#ifndef UNDERWATER_WORLD_BUFFER_H
#define UNDERWATER_WORLD_BUFFER_H

#include "Prototypes.h"

struct Buffer {
    GLuint buffer;
    GLuint size;

    Buffer() = default;
    Buffer(std::vector<unsigned char> data, GLenum usage);
    Buffer(void* data, GLuint size, GLenum usage);
    Buffer(GLuint size, GLenum usage);
};


#endif //UNDERWATER_WORLD_BUFFER_H
