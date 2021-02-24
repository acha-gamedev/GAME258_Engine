#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glew.h>
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
private:
	void UpdateVectors();
};

#endif //CAMERA_H