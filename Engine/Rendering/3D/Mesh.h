#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "../ShaderHandler.h"
#include "../../Camera/Camera.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uvCoords;
	glm::vec3 rgbValue;
};

class Mesh {
private:
	GLuint vao, vbo;
	GLuint shader, modelLoc, viewLoc, projectionLoc;
	GLuint textureID, textureLoc;
	GLuint cameraPosLoc, lightPosLoc, lightAmbiLoc, lightDiffLoc, lightSpecLoc, lightColourLoc;
	std::vector<Vertex> vertices;
public:
	Mesh(std::vector<Vertex>& _vertexlist, GLuint _shader, GLuint _texture);
	~Mesh();
	//Draw the mesh to the screen
	void Render(const glm::mat4 transform, const Camera* camera);

private:

	void GenerateBuffers();
};

#endif