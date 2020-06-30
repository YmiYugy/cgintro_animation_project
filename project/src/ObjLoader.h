#include "Helper.h"

bool loadOBJ(
	const char* path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<unsigned int>& out_indices,
	std::vector<glm::vec3>& out_normals,
	std::vector<glm::vec2>& out_uvs
);