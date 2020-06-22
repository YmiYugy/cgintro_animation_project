//
// Created by trist on 22/06/2020.
//

#ifndef UNDERWATER_WORLD_SIMPLEMESH_H
#define UNDERWATER_WORLD_SIMPLEMESH_H

#include "Helper.h"
#include "RenderNode.h"
#include "Camera.h"

class SimpleMesh : public RenderNode {
public:
    using RenderNode::RenderNode;

    void render() override;

    void updateUBOs(float delta) override;
};


#endif //UNDERWATER_WORLD_SIMPLEMESH_H
