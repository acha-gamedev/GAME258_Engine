#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
#include "BoundingBox.h"
#include "CollisionDetection.h"

struct Ray {
	glm::vec3 origin;
	glm::vec3 direction;
	float intersection;

	Ray() : origin(0.0f, 0.0f, 0.0f), direction(0.0f, 0.0f, 0.0f), intersection(0.0f) {}
	Ray(glm::vec3 _origin, glm::vec3 _direction) : origin(_origin), direction(_direction), intersection(0.0f) {}

	Ray& operator=(const Ray& other) {
		origin = other.origin;
		direction = other.direction;
		intersection = 0.0f;
	}

	bool TestCollision(const BoundingBox* bBox) {
		intersection = -1.0f;
		return CollisionDetection::RayBBoxIntersection(this, bBox);
	}
};

#endif //RAY_H
