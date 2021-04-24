#include "OctSpatialPartition.h"
//class OctNode

int OctNode::numCreated = 0;

OctNode::OctNode(glm::vec3 _position, float _size, OctNode* _parent) {
	bBox = new BoundingBox();
	bBox->minVertex = _position;
	bBox->maxVertex = _position + glm::vec3(_size);
	size = _size;
	for (int i = 0; i < CHILDREN_NUM; i++) {
		children[i] = nullptr;
	}
	parent = _parent;
}

OctNode::~OctNode() {
	delete bBox;
	bBox = nullptr;

	if (objects.size() > 0) {
		for (auto go : objects) {
			go = nullptr;
		}
		objects.clear();
	}

	for (int i = 0; i < CHILDREN_NUM; i++) {
		if (children[i] == nullptr) {
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth) {
	if (depth > 0 && this) {
		float half = size / 2.0f;

		children[static_cast<int>(OCT_TLF)] = new OctNode(glm::vec3(bBox->minVertex.x, bBox->minVertex.y + half, bBox->minVertex.z + half),
			half, this);
		children[static_cast<int>(OCT_BLF)] = new OctNode(glm::vec3(bBox->minVertex.x, bBox->minVertex.y, bBox->minVertex.z + half),
			half, this);
		children[static_cast<int>(OCT_BRF)] = new OctNode(glm::vec3(bBox->minVertex.x + half, bBox->minVertex.y, bBox->minVertex.z + half),
			half, this);
		children[static_cast<int>(OCT_TRF)] = new OctNode(glm::vec3(bBox->minVertex.x + half, bBox->minVertex.y + half, bBox->minVertex.z + half),
			half, this);
		children[static_cast<int>(OCT_TLR)] = new OctNode(glm::vec3(bBox->minVertex.x, bBox->minVertex.y + half, bBox->minVertex.z),
			half, this);
		children[static_cast<int>(OCT_BLR)] = new OctNode(glm::vec3(bBox->minVertex.x, bBox->minVertex.y, bBox->minVertex.z),
			half, this);
		children[static_cast<int>(OCT_BRR)] = new OctNode(glm::vec3(bBox->minVertex.x + half, bBox->minVertex.y, bBox->minVertex.z),
			half, this);
		children[static_cast<int>(OCT_TRR)] = new OctNode(glm::vec3(bBox->minVertex.x + half, bBox->minVertex.y + half, bBox->minVertex.z),
			half, this);

		numCreated += CHILDREN_NUM;
	}

	if (depth > 0 && this) {
		for (int i = 0; i < CHILDREN_NUM; i++) {
			children[i]->Octify(depth - 1);
		}
	}
}

OctNode* OctNode::GetChild(OctChild location) {	
	return children[static_cast<int>(location)];
}

void OctNode::AddCollisionObject(GameObject* _object) {
	objects.push_back(_object);
}

bool OctNode::IsLeaf() {
	if (children[0]) {
		return false;
	}
	else {
		return true;
	}
}

//class OctSpatialPartition

OctSpatialPartition::OctSpatialPartition(float worldSize) {
	root = new OctNode(glm::vec3(-worldSize / 2.0f), worldSize, nullptr);
	root->Octify(3);
	intersections.reserve(20);
}

OctSpatialPartition::~OctSpatialPartition() {
	delete root;
	root = nullptr;
	if (intersections.size() > 0) {
		for (auto on : intersections) {
			on = nullptr;
		}
	}
	intersections.clear();
}

void OctSpatialPartition::AddGameObject(GameObject* object) {
	AddToCell(object, root);
}

GameObject* OctSpatialPartition::GetHitObject(Ray* ray)
{
	if (intersections.size() > 0) {
		for (auto on : intersections) {
			on = nullptr;
		}
	}
	intersections.clear();
	QueryCollision(root, ray);

	GameObject* target = nullptr;
	float shortest = FLT_MAX;

	for (auto on : intersections) {
		for (auto go : on->objects) {
			if (ray->TestCollision(go->GetBoundingBox())) {
				if (ray->intersection < shortest) {
					target = go;
					shortest = ray->intersection;
				}
			}
		}
	}
	if (target) {
		return target;
	}
	return nullptr;
}

void OctSpatialPartition::AddToCell(GameObject* object, OctNode* cell) {
	if (cell) {
		if (cell->GetBoundingBox()->CheckIntersection(*object->GetBoundingBox())) {
			if (cell->IsLeaf()) {
				cell->AddCollisionObject(object);
				return;
			}
			else {
				for (int i = 0; i < CHILDREN_NUM; i++) {
					AddToCell(object, cell->GetChild(static_cast<OctChild>(i)));
				}
			}
		}
	}
}

void OctSpatialPartition::QueryCollision(OctNode* node, Ray* ray) {
	if (node) {
		if (ray->TestCollision(node->GetBoundingBox())) {
			if (node->IsLeaf()) {
				intersections.push_back(node);
				return;
			}
			else {
				for (int i = 0; i < CHILDREN_NUM; i++) {
					QueryCollision(node->GetChild(static_cast<OctChild>(i)), ray);
				}
			}
		}
	}
}