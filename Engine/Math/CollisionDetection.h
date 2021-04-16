#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "../Camera/Camera.h"
struct Ray;
struct BoundingBox;


class CollisionDetection {
public:
	//Converts a screen position to a Ray
	//PARAMS: mousePos: the position to convert(hor, ver); screenSize: the screen dimentions(width, height), camera: the camera instance
	static Ray ScreenPosToRay(glm::vec2 mousePos, glm::vec2 screenSize, Camera* camera);
	//Returns if a ray and bounding box intersect
	//PARAMS: ray: the ray to test; bBox: the bounding box to test
	static bool RayBBoxIntersection(Ray* ray, const BoundingBox* bBox);
private:
	CollisionDetection() = delete;
	CollisionDetection(const CollisionDetection&) = delete;
	CollisionDetection(CollisionDetection&&) = delete;
	CollisionDetection& operator=(const CollisionDetection&) = delete;
	CollisionDetection& operator=(CollisionDetection&&) = delete;
	~CollisionDetection() {}
};

#endif //COLLISIONDETECTION_H