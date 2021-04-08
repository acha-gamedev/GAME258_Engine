#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

Model::Model(GLuint _shader, std::string objPath, std::string matPath) : meshes(std::vector<Mesh*>()), shader(_shader),
	instances(std::vector<glm::mat4>()) {
	meshes.reserve(10);
	instances.reserve(5);
	modelLoader = new ObjModelLoader();
	modelLoader->LoadOBJ(objPath, matPath);
	LoadModel();
	delete modelLoader;
	modelLoader = nullptr;
}

//Model::Model(GLuint _shader, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale) : 
//	meshes(std::vector<Mesh*>()), shader(_shader), position(_position), angle(_angle), rotation(_rotation), scale(_scale) {}

Model::~Model() {
	if (meshes.size() > 0) {
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

unsigned int Model::CreateInstance(glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale) {
	instances.push_back(CreateTransform(_position, _angle, _rotation, _scale));
	return (instances.size() - 1);
}

void Model::UpdateInstance(unsigned int index, glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale) {
	instances[index] = CreateTransform(_position, _angle, _rotation, _scale);
}

void Model::Render(const Camera* camera) {
	glUseProgram(shader);
	for (auto m : meshes) {
		m->Render(instances, camera);
	}
	//glUseProgram(0);
}

void Model::AddMesh(Mesh* _mesh) {
	meshes.push_back(_mesh);
}

glm::mat4 Model::GetTransform(const unsigned int index) const {
	return instances[index];
}

glm::mat4 Model::CreateTransform(glm::vec3 _position, float _angle, glm::vec3 _rotation, glm::vec3 _scale) {
	glm::mat4 temp;
	temp = glm::translate(temp, _position);
	temp = glm::rotate(temp, _angle, _rotation);
	temp = glm::scale(temp, _scale);
	return temp;
}

void Model::LoadModel() {
	if (modelLoader) {
		int submeshCount = modelLoader->GetSubMeshes().size();
		for (int i = 0; i < submeshCount; i++) {
			meshes.push_back(new Mesh(modelLoader->GetSubMeshes()[i], shader));
		}
		boundBox = modelLoader->GetBoundingBox();
	}
}