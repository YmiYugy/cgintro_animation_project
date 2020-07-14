
#include "Buffer.h"

Buffer::Buffer(std::vector<unsigned char> data, GLenum usage) {
    Buffer(data.data(), data.size(), usage);
}

Buffer::Buffer(void *data, GLuint size, GLenum usage) {
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_COPY_WRITE_BUFFER, buffer);
    glBufferData(GL_COPY_WRITE_BUFFER, size, data, usage);
}

Buffer::Buffer(GLuint size, GLenum usage) {
    Buffer(nullptr, size, usage);
}

