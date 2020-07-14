

#ifndef UNDERWATER_WORLD_SAMPLEPOINTS_H
#define UNDERWATER_WORLD_SAMPLEPOINTS_H

#include "Prototypes.h"
#include "Buffer.h"

struct SamplePoints {
    std::vector<glm::vec4> points;

    explicit SamplePoints(GLuint num_pts);

    void updateUniforms(ComputeShader shader);
};

struct SamplePointsBuffer : public Buffer {
    explicit SamplePointsBuffer(SamplePoints points);
};


#endif //UNDERWATER_WORLD_SAMPLEPOINTS_H
