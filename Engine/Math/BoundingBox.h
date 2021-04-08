#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <glm/glm.hpp>

struct BoundingBox {
	glm::vec3 minVertex;
	glm::vec3 maxVertex;
	glm::mat4 transform;

	BoundingBox() : minVertex(0.0f, 0.0f, 0.0f), maxVertex(0.0f, 0.0f, 0.0f), transform() {}
	BoundingBox(glm::vec3 _minVertex, glm::vec3 _maxVertex, glm::mat4 _transform) : 
		minVertex(_minVertex), maxVertex(_maxVertex), transform(_transform) {}
};

#endif //BOUNDINGBOX_H