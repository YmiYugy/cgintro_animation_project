
#ifndef UNDERWATER_WORLD_NAME_H
#define UNDERWATER_WORLD_NAME_H

#include <utility>

#include "Prototypes.h"

struct Name {
    explicit Name(std::string name) : name(std::move(name)) {}

    std::string name;
};


#endif //UNDERWATER_WORLD_NAME_H
