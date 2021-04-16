#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::instance = nullptr;
std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
std::vector<GameObject*> CollisionHandler::previousCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler() {}

CollisionHandler::~CollisionHandler() {
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new CollisionHandler());
	}
	return instance.get();
}

void CollisionHandler::OnCreate() {
	colliders.clear();
	colliders.reserve(5);
	previousCollisions.clear();
	previousCollisions.reserve(5);
}

void CollisionHandler::AddGameObject(GameObject* go) {
	colliders.push_back(go);
}

void CollisionHandler::Update(glm::vec2 mousePos, int button) {
	Ray screenCast = CollisionDetection::ScreenPosToRay(mousePos, CoreEngine::GetInstance()->GetWindowSize(), 
		CoreEngine::GetInstance()->GetCamera());
	GameObject* target = nullptr;
	float shortestDist = 1000000.0f;
	for (auto c : colliders) {
		if (screenCast.TestCollision(c->GetBoundingBox())) {
			if (screenCast.intersection < shortestDist) {
				target = c;
				shortestDist = screenCast.intersection;
			}
		}
	}

	if (target) {
		target->SetHitStatus(true, button);
	}
	for (auto prev : previousCollisions) {
		if (prev != target && prev != nullptr) {
			prev->SetHitStatus(false, button);
		}
	}
	previousCollisions.clear();
	if (target) {
		previousCollisions.push_back(target);
	}
}

void CollisionHandler::OnDestroy() {
	if (colliders.size() > 0) {
		for (auto c : colliders) {
			c = nullptr;
		}
		colliders.clear();
	}
	if (previousCollisions.size() > 0) {
		for (auto pc : previousCollisions) {
			pc = nullptr;
		}
	}
}