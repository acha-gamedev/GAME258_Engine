#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <memory>
#include <map>
#include <vector>
#include "3D/GameObject.h"

class SceneGraph {
private:
	static std::unique_ptr<SceneGraph> instance;
	friend std::default_delete<SceneGraph>;

	static std::map<GLuint, std::vector<Model*>> models;
	static std::map<std::string, GameObject*> gameObjects;
public:
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph&&) = delete;

	static SceneGraph* GetInstance();

	void AddModel(Model* _model);
	void AddGameObject(GameObject* _gameObject, std::string tag = "");
	GameObject* GetGameObject(const std::string tag);
	void Update(const float deltaTime);
	void Render(const Camera* camera);
	void OnDestroy();
private:
	SceneGraph();
	~SceneGraph();
};

#endif //SCENEGRAPH_H