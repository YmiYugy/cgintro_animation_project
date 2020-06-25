//
// Created by trist on 19/06/2020.
//

#ifndef UNDERWATER_WORLD_SPHERECLOUD_H
#define UNDERWATER_WORLD_SPHERECLOUD_H

#include "Helper.h"
#include "RenderNode.h"
#include "Camera.h"
#include "Boids.h"

class SphereCloud : public RenderNode {
public:
    using RenderNode::RenderNode;

    void render() override;

    void updateUBOs(float delta) override;
};


#endif //UNDERWATER_WORLD_SPHERECLOUD_H
