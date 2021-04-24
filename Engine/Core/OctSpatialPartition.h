#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Rendering/3D/GameObject.h"
#include "../Math/Ray.h"

constexpr int CHILDREN_NUM = 8;

enum OctChild {
	OCT_TLF, //Top Left Front
	OCT_BLF, //Bottom Left Front
	OCT_BRF, //Bottom Right Front
	OCT_TRF, //Top Right Front
	OCT_TLR, //Top Left Rear
	OCT_BLR, //Bottom Left Rear
	OCT_BRR, //Bottom Right Rear
	OCT_TRR  //Top Right Rear
};

class OctNode {
private:
	BoundingBox* bBox;
	OctNode* parent;
	OctNode* children[CHILDREN_NUM];
	std::vector<GameObject*> objects;
	float size;
	static int numCreated;

	friend class OctSpatialPartition;
public:
	OctNode() = delete;
	OctNode(glm::vec3 _position, float _size, OctNode* _parent);

	~OctNode();

	void Octify(int depth);

	inline OctNode* GetParent() { return parent; }
	OctNode* GetChild(OctChild location);
	void AddCollisionObject(GameObject* _object);
	int GetObjectCount() { return objects.size(); }
	bool IsLeaf();
	inline BoundingBox* GetBoundingBox() { return bBox; }
	inline int GetTotalChildren() { return numCreated; }

};

class OctSpatialPartition {
private:
	OctNode* root;
	std::vector<OctNode*> intersections;
public:
	OctSpatialPartition(float worldSize);
	~OctSpatialPartition();
	void AddGameObject(GameObject* object);
	GameObject* GetHitObject(Ray* ray);
private:
	void AddToCell(GameObject* object, OctNode* cell);
	void QueryCollision(OctNode* node, Ray* ray);
};

#endif //OCTSPATIALPARTITION_H