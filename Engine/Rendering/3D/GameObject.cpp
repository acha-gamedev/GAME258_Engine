#include "GameObject.h"

GameObject::GameObject(Model* _model) : position(0.0f, 0.0f, 0.0f), model(_model), modelInstance(0),
	angle(0.0f), scale(0.0f, 0.0f, 0.0f), rotation(0.0f, 1.0f, 0.0f), tag("") {
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::GameObject(glm::vec3 _position, Model* _model) : position(_position), model(_model), modelInstance(0),
	angle(0.0f), scale(0.0f, 0.0f, 0.0f), rotation(0.0f, 1.0f, 0.0f), tag("") {
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::~GameObject() {
	//if (model) {
	//	delete model;
	//}
	model = nullptr;
}

void GameObject::Render(const Camera* camera) {
	//if (model) {
	//	model->Render(camera, modelInstance);
	//}
}

void GameObject::Update(const float dTime) {
	SetAngle(angle + 0.005f);
}

void GameObject::SetPosition(const glm::vec3 _position) {
	position = _position;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetRotation(const glm::vec3 _rotation) {
	rotation = _rotation;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetAngle(const float _angle) {
	angle = _angle;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetScale(const glm::vec3 _scale) {
	scale = _scale;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}