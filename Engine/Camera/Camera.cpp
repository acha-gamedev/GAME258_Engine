#include "Camera.h"
#include "../Core/CoreEngine.h"

Camera::Camera() : position(), perspectiveMatrix(), orthographicMatrix(), viewMatrix(), fovAngle(0.0f), yaw(0.0f), pitch(0.0f),
	nearPlane(0.0f), farPlane(0.0f), forward(), up(), right(), worldUp() {
	fovAngle = 45.0f;
	forward = vec3(0.0f, 0.0f, -1.0f);
	worldUp = up = vec3(0.0f, 1.0f, 0.0f);
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	perspectiveMatrix = perspective(radians(fovAngle), 
		CoreEngine::GetInstance()->GetWindowSize().x / CoreEngine::GetInstance()->GetWindowSize().y, nearPlane, farPlane);
	orthographicMatrix = ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x, 
		0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);
	UpdateVectors();
}

Camera::~Camera() {
	if (lights.size() > 0) {
		for (auto l : lights) {
			delete l;
			l = nullptr;
		}
	}
	lights.clear();
}

void Camera::SetPosition(const vec3 _position) {
	position = _position;
	UpdateVectors();
}

void Camera::SetRotation(const float _yaw, const float _pitch) {
	yaw = _yaw;
	pitch = _pitch;
	UpdateVectors();
}

void Camera::AddLight(LightSource* _light) {
	lights.push_back(_light);
}

void Camera::UpdateVectors() {
	forward.y = sinf(radians(pitch));
	float temp = cosf(radians(pitch));
	forward.x = cosf(radians(yaw)) * temp;
	forward.z = sinf(radians(yaw)) * temp;
	normalize(forward);
	right = normalize(cross(forward, worldUp));
	up = normalize(cross(right, forward));
	viewMatrix = lookAt(position, position + forward, up);
}

void Camera::MouseMovement(const glm::ivec2 offset) {
	float sensitivity = 0.10f;
	yaw += offset.x * sensitivity;
	pitch += offset.y * sensitivity;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	else if (yaw < 0.0f) {
		yaw += 360.0f;
	}

	UpdateVectors();
}

void Camera::MouseScroll(const int amount) {
	if (abs(amount) > 0) {
		position += forward * (amount * 2.0f);
	}
	UpdateVectors();
}