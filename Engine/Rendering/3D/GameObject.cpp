#include "GameObject.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

GameObject::GameObject(Model* _model) : position(0.0f, 0.0f, 0.0f), model(_model), modelInstance(0),
	angle(0.0f), scale(0.0f, 0.0f, 0.0f), rotation(0.0f, 1.0f, 0.0f), tag("") {
	if (model) {
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
		boundingBox = model->GetBoundingBox();
		boundingBox.transform = model->GetTransform(modelInstance);
		std::cout << "MinVert: " << glm::to_string(boundingBox.minVertex) <<
			", MaxVert: " << glm::to_string(boundingBox.maxVertex) << std::endl;
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
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetRotation(const glm::vec3 _rotation) {
	rotation = _rotation;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetAngle(const float _angle) {
	angle = _angle;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);
	}
}

void GameObject::SetScale(const glm::vec3 _scale) {
	scale = _scale;
	if (model) {
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
		boundingBox.transform = model->GetTransform(modelInstance);

		if (scale.x < 1.0f) {
			boundingBox.maxVertex.x *= (scale.x / 2.0f);
			boundingBox.minVertex.x *= (scale.x / 2.0f);
		}
		else {
			boundingBox.maxVertex.x *= scale.x;
			boundingBox.minVertex.x *= scale.x;
		}

		if (scale.y < 1.0f) {
			boundingBox.maxVertex.y *= (scale.y / 2.0f);
			boundingBox.minVertex.y *= (scale.y / 2.0f);
		}
		else {
			boundingBox.maxVertex.y *= scale.y;
			boundingBox.minVertex.y *= scale.y;
		}

		if (scale.z < 1.0f) {
			boundingBox.maxVertex.z *= (scale.z / 2.0f);
			boundingBox.minVertex.z *= (scale.z / 2.0f);
		}
		else {
			boundingBox.maxVertex.z *= scale.z;
			boundingBox.minVertex.z *= scale.z;
		}
	}
}