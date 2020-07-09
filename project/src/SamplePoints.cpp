//
// Created by trist on 08/07/2020.
//

#include "SamplePoints.h"
#include "Shader.h"

SamplePoints::SamplePoints(GLuint num_pts) {
    std::vector<float> indices(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        indices[i] = i;
    }

    std::vector<float> phi(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        phi[i] = acosf(1 - 2.0f * indices[i] / static_cast<float>(num_pts));
    }

    std::vector<float> theta(num_pts);

    float sqrt5 = sqrtf(5);
    for (size_t i = 0; i < num_pts; i++) {
        theta[i] = M_PI * (1.0f + sqrt5) * indices[i];
    }

    std::vector<float> x(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        x[i] = cosf(phi[i]);
    }

    std::vector<float> y(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        y[i] = sinf(theta[i]) * sinf(phi[i]);
    }

    std::vector<float> z(num_pts);
    for (size_t i = 0; i < num_pts; i++) {
        z[i] = cosf(theta[i]) * sinf(phi[i]);
    }

    points = std::vector<glm::vec4> (num_pts + 1);
    points[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    for (size_t i = 0; i < num_pts; i++) {
        points[i + 1] = glm::vec4(x[i], y[i], z[i], 1.0f);
    }
}

void SamplePoints::updateUniforms(ComputeShader shader) {
    shader.use();
    shader.setUint("sample_count", points.size());
}

SamplePointsBuffer::SamplePointsBuffer(SamplePoints points) : Buffer(points.points.data(), points.points.size() * sizeof(GLuint), GL_STATIC_DRAW) {
}
