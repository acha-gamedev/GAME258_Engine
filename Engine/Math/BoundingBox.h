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

	bool CheckIntersection(BoundingBox other) {
		glm::vec3 minTransform = GetTransformedPoint(minVertex, transform);
		glm::vec3 maxTransform = GetTransformedPoint(maxVertex, transform);
		glm::vec3 otherMax = GetTransformedPoint(other.maxVertex, other.transform);
		glm::vec3 otherMin = GetTransformedPoint(other.minVertex, other.transform);

		int total = 0;
		total += (minTransform.x <= otherMax.x) ? 1 : 0;
		total += (minTransform.y <= otherMax.y) ? 1 : 0;
		total += (minTransform.z <= otherMax.z) ? 1 : 0;
		total += (maxTransform.x >= otherMin.x) ? 1 : 0;
		total += (maxTransform.y >= otherMin.y) ? 1 : 0;
		total += (maxTransform.z >= otherMin.z) ? 1 : 0;

		if (total >= 6) return true;
		return false;
	}

private:
	glm::vec3 GetTransformedPoint(glm::vec3 point, glm::mat4 _transform) {
		return point + glm::vec3(_transform[3]);
	}
};

#endif //BOUNDINGBOX_H