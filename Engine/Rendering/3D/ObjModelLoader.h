#ifndef OBJMODELLOADER_H
#define OBJMODELLOADER_H

#include "Mesh.h"
#include "../TextureHandler.h"
#include <sstream>
#include <memory>

class ObjModelLoader {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoords;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> normalIndices;
	std::vector<unsigned int> uvIndices;
	std::vector<Vertex> vertexObjects;
	std::vector<SubMesh> submeshes;
	GLuint textureID;

public:
	ObjModelLoader();
	~ObjModelLoader();
	void LoadOBJ(std::string _objFilepath, std::string _matFilepath);
	std::vector<SubMesh> GetSubMeshes();

private:
	void LoadModel(std::string _objFilepath);
	void LoadMaterial(std::string _matFilepath);
	void LoadTexture(std::string _texName);
	void PostProcess();
};

#endif //OBJMODELLOADER_H