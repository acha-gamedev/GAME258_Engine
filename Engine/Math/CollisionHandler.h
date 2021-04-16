#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Ray.h"
#include "../Rendering/3D/GameObject.h"
#include <memory>
#include <vector>

class CollisionHandler {
private:
	static std::unique_ptr<CollisionHandler> instance;
	friend std::default_delete<CollisionDetection>;

	static std::vector<GameObject*> colliders;
	static std::vector<GameObject*> previousCollisions;
public:
	static CollisionHandler* GetInstance();

	void OnCreate();

	void AddGameObject(GameObject* go);

	void Update(glm::vec2 mousePos, int button);

	void OnDestroy();
	~CollisionHandler();
private:
	CollisionHandler();

	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator=(const CollisionHandler&) = delete;
	CollisionHandler& operator=(CollisionHandler&&) = delete;
};

#endif //COLLISIONHANDLER_H