#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uvCoords;
	glm::vec3 rgbValue;
};

class Mesh {
private:
	GLuint vao, vbo;
	std::vector<Vertex> vertices;
public:
	Mesh(std::vector<Vertex>& _vertexlist);
	~Mesh();
	//Draw the mesh to the screen
	void Render();

private:

	void GenerateBuffers();
};

#endif