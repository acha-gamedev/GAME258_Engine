#include "CollisionDetection.h"
#include "Ray.h"
#include "../Core/CoreEngine.h"

Ray CollisionDetection::ScreenPosToRay(glm::vec2 mousePos, glm::vec2 screenSize, Camera* camera) {
	glm::vec4 startNDC = glm::vec4(((mousePos.x / screenSize.x) - 0.5f) * 2.0f, ((mousePos.y / screenSize.y) - 0.5f) * 2.0f, -1.0f, 1.0f);
	glm::vec4 endNDC = glm::vec4(((mousePos.x / screenSize.x) - 0.5f) * 2.0f, ((mousePos.y / screenSize.y) - 0.5f) * 2.0f, 0.0f, 1.0f);
	glm::mat4 projectionView = glm::inverse(camera->GetPerspectiveMatrix() * camera->GetViewMatrix());
	startNDC = projectionView * startNDC;
	startNDC = startNDC / startNDC.w;
	endNDC = projectionView * endNDC;
	endNDC = endNDC / endNDC.w;
	glm::vec3 Worlddir = glm::vec3(endNDC - startNDC);
	glm::normalize(Worlddir);
	return Ray(glm::vec3(startNDC), Worlddir);
}

bool CollisionDetection::RayBBoxIntersection(Ray* ray, const BoundingBox* bBox) {
	glm::mat4 model = bBox->transform;
	glm::vec3 start = ray->origin;
	glm::vec3 dir = ray->direction;
	glm::vec3 minPoint = bBox->minVertex;
	glm::vec3 maxPoint = bBox->maxVertex;
	float tMin = CoreEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = CoreEngine::GetInstance()->GetCamera()->GetFarPlane();
	glm::vec3 boxWorld = glm::vec3(model[3].x, model[3].y, model[3].z);
	glm::vec3 delta = boxWorld - start;
	float storage = 0.0f;

	glm::vec3 xAxis = glm::vec3(model[0].x, model[0].y, model[0].z);
	float dotDelta = glm::dot(delta, xAxis);
	float dotDir = glm::dot(dir, xAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + minPoint.x) / dotDir;
		float t2 = (dotDelta + maxPoint.x) / dotDir;
		if (t1 > t2) {
			storage = t1;
			t1 = t2;
			t2 = storage;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else if ((-dotDelta + minPoint.x > 0.0f) || (-dotDelta + maxPoint.x < 0.0f)){
		return false;
	}

	glm::vec3 yAxis = glm::vec3(model[1].x, model[1].y, model[1].z);
	dotDelta = glm::dot(delta, yAxis);
	dotDir = glm::dot(dir, yAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + minPoint.y) / dotDir;
		float t2 = (dotDelta + maxPoint.y) / dotDir;
		if (t1 > t2) {
			storage = t1;
			t1 = t2;
			t2 = storage;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else if ((-dotDelta + minPoint.y > 0.0f) || (-dotDelta + maxPoint.y < 0.0f)) {
		return false;
	}

	glm::vec3 zAxis = glm::vec3(model[2].x, model[2].y, model[2].z);
	dotDelta = glm::dot(delta, zAxis);
	dotDir = glm::dot(dir, zAxis);
	if (fabs(dotDir) > 0.001f) {
		float t1 = (dotDelta + minPoint.z) / dotDir;
		float t2 = (dotDelta + maxPoint.z) / dotDir;
		if (t1 > t2) {
			storage = t1;
			t1 = t2;
			t2 = storage;
		}
		if (t2 < tMax) {
			tMax = t2;
		}
		if (t1 > tMin) {
			tMin = t1;
		}
		if (tMax < tMin) {
			return false;
		}
	}
	else if ((-dotDelta + minPoint.z > 0.0f) || (-dotDelta + maxPoint.z < 0.0f)) {
		return false;
	}
	ray->intersection = tMin;
	return true;
}
