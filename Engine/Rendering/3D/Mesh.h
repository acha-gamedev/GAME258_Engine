#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "../ShaderHandler.h"
#include "../../Camera/Camera.h"
#include "../MaterialHandler.h"
#include "../../Math/BoundingBox.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uvCoords;
	//glm::vec3 rgbValue;
};

struct SubMesh {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indexList;
	Material material;
};

class Mesh {
private:
	GLuint vao, vbo;
	SubMesh submesh;
	GLuint shader, modelLoc, viewLoc, projectionLoc, textureLoc, cameraPosLoc, lightPosLoc, 
		lightAmbiLoc, lightDiffLoc, lightSpecLoc, lightColourLoc, 
		shineLoc, transparencyLoc, matAmbiLoc, matDiffLoc, matSpecLoc;
public:
	Mesh(SubMesh& _submesh, GLuint _shader);
	~Mesh();
	//Draw the mesh to the screen
	void Render(std::vector<glm::mat4> transform, const Camera* camera, const BoundingBox bBox);

private:

	void GenerateBuffers();
};

#endif