#include "ObjLoader.h"

bool loadOBJ(
	const char* path,
	std::vector<Object>& parsedObjects

) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE* file = fopen(path, "r");
	if (file == NULL) {
		printf("Wrong path.\n");
		getchar();
		return false;
	}

	bool first_o = true;
	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			Object object;
			object.vertices = temp_vertices;
			object.normals = temp_normals;
			object.uvs = temp_uvs;
			object.vertex_indices = vertexIndices;
			parsedObjects.push_back(object);
			break; // EOF = End Of File. Quit the loop.
		}
				

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			GLuint vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			vertexIndex[0] -= 1; vertexIndex[1] -= 1; vertexIndex[2] -= 1;	//indices start at 0
			if (matches != 9) {
				printf("File can't be read. Try exporting with other options\n");
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);			//not used yet
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);	//not used yet
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else if (strcmp(lineHeader, "o") == 0) {
			if (first_o) first_o = false;
			else {
				Object object;
				object.vertices = temp_vertices;
				object.normals = temp_normals;
				object.uvs = temp_uvs;
				object.vertex_indices = vertexIndices;
				parsedObjects.push_back(object);
				temp_vertices.clear();
				temp_normals.clear();
				temp_uvs.clear();
				vertexIndices.clear();
			}
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}


	fclose(file);
	return true;
}