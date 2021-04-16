#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

struct Plane {
	glm::vec3 normal;
	float d;

	Plane() : normal(0.0f, 1.0f, 0.0f), d(0.0f) {}
	Plane(float x_, float y_, float z_, float _d) : normal(x_, y_, z_), d(_d) {
		normal = glm::normalize(normal);
	}
	Plane(glm::vec4 comp) : normal(comp.x, comp.y, comp.z), d(comp.w) {
		normal = glm::normalize(normal);
	}
	
	~Plane() {}

	float DistanceToPoint(glm::vec3 point) {
		return (normal.x * point.x) + (normal.y * point.y) + (normal.z * point.z) + d;
	}
};

#endif //PLANE_H