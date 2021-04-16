#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glew.h>
#include <vector>
#include "../FX/LightSource.h"
using namespace glm;

class Camera {
private:
	vec3 position;
	mat4 perspectiveMatrix;
	mat4 orthographicMatrix;
	mat4 viewMatrix;
	float fovAngle;
	float yaw, pitch;
	float nearPlane, farPlane;
	vec3 forward, up, right;
	vec3 worldUp;
	std::vector<LightSource*> lights;
public:
	Camera();
	virtual ~Camera();
	//Set the position of the camera
	//PARAMS: _position: the new position
	void SetPosition(const vec3 _position);
	//Set the orientation of the camera
	//PARAMS: _yaw: the new yaw(y-axis); _pitch: the new pitch(x-axis)
	void SetRotation(const float _yaw, const float _pitch);
	//Returns the view matrix (4x4)
	inline mat4 GetViewMatrix() const { return viewMatrix; }
	//Returns the perspective matrix (4x4)
	inline mat4 GetPerspectiveMatrix() const { return perspectiveMatrix; }
	//Returns the orthographic matrix (4x4)
	inline mat4 GetOrthographicMatrix() const { return orthographicMatrix; }
	//Adds a light source
	//PARAMS: _light: the light source to add
	void AddLight(LightSource* _light);
	//Returns the list of light sources
	inline std::vector<LightSource*> GetLights() const { return lights; }
	//Returns the position of the camera
	inline vec3 GetPosition() const { return position; }
	//Returns the near plane
	inline float GetNearPlane() const { return nearPlane; }
	//Returns the far plane
	inline float GetFarPlane() const { return farPlane; }
	//Handles mouse movement
	//PARAMS: offset: the amount the mouse has been moved
	void MouseMovement(const glm::ivec2 offset);
	//Handles scrolling
	//PARAMS: amount: the amount the scroll whell has been moved
	void MouseScroll(const int amount);
private:
	void UpdateVectors();
};

#endif //CAMERA_H