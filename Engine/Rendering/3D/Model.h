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
public:
	Model(GLuint _shader, std::string objPath, std::string matPath);
	//Model(GLuint _shader, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);
	~Model();

	//Draw all meshes to the screen
	void Render(const Camera* camera);

	//Add a mesh to the model
	void AddMesh(Mesh* _mesh);

	unsigned int CreateInstance(glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);

	void UpdateInstance(unsigned int index, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);

	glm::mat4 GetTransform(const unsigned int index) const;

	inline GLuint GetShader() const { return shader; }

private:
	glm::mat4 CreateTransform(glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale);
	void LoadModel();
};

#endif //MODEL_H