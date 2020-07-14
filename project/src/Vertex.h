

#ifndef UNDERWATER_WORLD_VERTEX_H
#define UNDERWATER_WORLD_VERTEX_H

#include "Prototypes.h"

struct TextureVertex {
    glm::vec4 pos;
    glm::vec4 normal;
    glm::vec2 texCoord;

    bool operator==(const TextureVertex& other) const {
        return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
    }
};

namespace std {
    template<> struct hash<TextureVertex> {
        size_t operator()(TextureVertex const& vertex) const {
            return ((hash<glm::vec4>()(vertex.pos) ^
                     (hash<glm::vec4>()(vertex.normal) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

struct ColorVertex {
    glm::vec4 pos;
    glm::vec4 normal;
    glm::vec4 color;

    bool operator==(const ColorVertex& other) const {
        return pos == other.pos && normal == other.normal && color == other.color;
    }
};

namespace std {
    template<> struct hash<ColorVertex> {
        size_t operator()(ColorVertex const& vertex) const {
            return ((hash<glm::vec4>()(vertex.pos) ^
                     (hash<glm::vec4>()(vertex.normal) << 1)) >> 1) ^
                   (hash<glm::vec4>()(vertex.color) << 1);
        }
    };
}

struct CollisionVertex {
    glm::vec4 pos;

    bool operator==(const CollisionVertex& other) const {
        return pos == other.pos;
    }
};

namespace std {
    template<> struct hash<CollisionVertex> {
        size_t operator()(CollisionVertex const& vertex) const {
            return ((hash<glm::vec4>()(vertex.pos)));
        }
    };
}



#endif //UNDERWATER_WORLD_VERTEX_H
