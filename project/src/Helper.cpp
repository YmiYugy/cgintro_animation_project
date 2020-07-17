

#include "Helper.h"

std::vector<unsigned char> loadFile(const std::string &path) {
    std::ifstream input(path, std::ios::binary);
    if(!input.is_open()) throw std::runtime_error("failed to open " + path);
    return std::vector<unsigned char>(std::istreambuf_iterator<char>(input), {});
}
