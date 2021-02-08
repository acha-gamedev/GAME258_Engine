#include "Model.h"

Model::Model() : meshes(std::vector<Mesh*>()) {}

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
	for (auto m : meshes) {
		m->Render();
	}
}

void Model::AddMesh(Mesh* _mesh) {
	meshes.push_back(_mesh);
}
