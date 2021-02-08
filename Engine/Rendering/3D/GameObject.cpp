#include "GameObject.h"

GameObject::GameObject(Model* _model) : model(_model) {}

GameObject::~GameObject() {
	if (model) {
		delete model;
	}
	model = nullptr;
}

void GameObject::Render() {
	if (model) {
		model->Render();
	}
}