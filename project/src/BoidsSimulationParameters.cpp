
#include "BoidsSimulationParameters.h"

BoidsSimulationParametersBuffer::BoidsSimulationParametersBuffer(BoidSimulationParameters parameters) : Buffer(
        &parameters, sizeof(BoidSimulationParameters), GL_DYNAMIC_DRAW) {}

void BoidsSimulationParametersBuffer::bind(ComputeShader shader, GLuint position) {
    shader.use();
    glBindBufferBase(GL_UNIFORM_BUFFER, position, buffer);
}
