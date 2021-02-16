#include "Model.h"

Model::Model(GLuint _shader) : meshes(std::vector<Mesh*>()), shader(_shader) {}

Model::~Model() {
	if (meshes.size() > 0) {
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}
		meshes.clear();
	}
}

void Model::Render() {
	glUseProgram(shader);
	for (auto m : meshes) {
		m->Render();
	}
	//glUseProgram(0);
}

void Model::AddMesh(Mesh* _mesh) {
	meshes.push_back(_mesh);
}
