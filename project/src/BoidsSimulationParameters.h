//
// Created by trist on 08/07/2020.
//

#ifndef UNDERWATER_WORLD_BOIDSSIMULATIONPARAMETERS_H
#define UNDERWATER_WORLD_BOIDSSIMULATIONPARAMETERS_H

#include "Prototypes.h"
#include "Buffer.h"
#include "Shader.h"

struct BoidSimulationParameters {
    float max_steer_force = 5;
    float max_speed = 10.0;
    float min_speed = 6.0;
    float view_radius = 5.0;
    float avoid_radius = 1.0;
    float align_weight = 4;
    float cohesion_weight = 4;
    float separate_weight = 6;
    float collisions_avoid_dst = 2.5;
    float avoid_collision_weight = 20;
    float collision_avoid_force_dst = 0.2;
    float padding = 0.0;
};

struct BoidsSimulationParametersBuffer : public Buffer {
    explicit BoidsSimulationParametersBuffer(BoidSimulationParameters parameters);
    void bind(ComputeShader shader, GLuint position);
};


#endif //UNDERWATER_WORLD_BOIDSSIMULATIONPARAMETERS_H
