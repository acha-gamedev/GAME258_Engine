#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "ObjModelLoader.h"
#include <string>

class Model {
private:
	GLuint shader;
	std::vector<Mesh*> meshes;
	std::vector<glm::mat4> instances;
	ObjModelLoader* modelLoader;
	BoundingBox boundBox;
public:
	Model(GLuint _shader, std::string objPath, std::string matPath);
	//Model(GLuint _shader, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);
	~Model();

	//Draw all meshes to the screen
	void Render(const Camera* camera);

	//Add a mesh to the model
	void AddMesh(Mesh* _mesh);
	//Generates a transform matrix for a new instance of the model
	unsigned int CreateInstance(glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);
	//Updates the matrix for an existing instance of the model
	void UpdateInstance(unsigned int index, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);
	//Returns the transform matrix for an existing instance of the model
	glm::mat4 GetTransform(const unsigned int index) const;

	inline GLuint GetShader() const { return shader; }

	inline BoundingBox GetBoundingBox() const { return boundBox; }
private:
	glm::mat4 CreateTransform(glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);
	void LoadModel();
};

#endif //MODEL_H