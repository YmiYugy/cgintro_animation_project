#include "Helper.h"

struct Object {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> vertex_indices;
	std::vector<GLuint> normal_indices;
	std::vector<GLuint> uv_indices;
	std::string name;
	GLuint texture;
};

bool loadOBJ(
	const char* path,
	std::vector<Object>& parsedObjects
);

//loadDDS-File: gives texture
GLuint loadDDS(const char* imagepath);

//loadBMP-File: gives texture
GLuint loadBMP(const char* imagepath);
