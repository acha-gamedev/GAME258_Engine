#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

Model::Model(GLuint _shader) : meshes(std::vector<Mesh*>()), shader(_shader), 
	position(0.0f, 0.0f, 0.0f), angle(0.0f), rotation(0.0f, 1.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {}

Model::Model(GLuint _shader, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale) : 
	meshes(std::vector<Mesh*>()), shader(_shader), position(_position), angle(_angle), rotation(_rotation), scale(_scale) {}

Model::~Model() {
	if (meshes.size() > 0) {
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

void Model::Render(Camera* camera) {
	glUseProgram(shader);
	for (auto m : meshes) {
		m->Render(GetTransform(), camera);
	}
	//glUseProgram(0);
}

void Model::AddMesh(Mesh* _mesh) {
	meshes.push_back(_mesh);
}

glm::mat4 Model::GetTransform() const
{
	glm::mat4 temp;
	temp = glm::translate(temp, position);
	temp = glm::rotate(temp, angle, rotation);
	temp = glm::scale(temp, scale);
	return temp;
}