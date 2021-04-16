#include "SceneGraph.h"
#include "../Math/CollisionHandler.h"

std::unique_ptr<SceneGraph> SceneGraph::instance = nullptr;
std::map<GLuint, std::vector<Model*>> SceneGraph::models = std::map<GLuint, std::vector<Model*>>();
std::map<std::string, GameObject*> SceneGraph::gameObjects = std::map<std::string, GameObject*>();

SceneGraph::SceneGraph() {}

SceneGraph::~SceneGraph() {
	OnDestroy();
}

SceneGraph* SceneGraph::GetInstance() {
	if (instance.get() == nullptr) {
		instance.reset(new SceneGraph);
	}
	return instance.get();
}

void SceneGraph::AddModel(Model* _model) {
	GLuint _shader = _model->GetShader();
	if (models.find(_shader) == models.end()) {
		models.insert(std::pair<GLuint, std::vector<Model*>>(_shader, std::vector<Model*>()));
		models[_shader].reserve(10);
	}
	models[_shader].push_back(_model);
}

void SceneGraph::AddGameObject(GameObject* _gameObject, std::string tag) {
	if (tag == "") {
		std::string newTag = "GameObject" + std::to_string(gameObjects.size() + 1);
		_gameObject->SetTag(newTag);
		gameObjects[newTag] = _gameObject;
	}
	else if (gameObjects.find(tag) == gameObjects.end()) {
		_gameObject->SetTag(tag);
		gameObjects[tag] = _gameObject;
	}
	else {
		Debug::LogWarning("Trying to add GameObject with exsisting tag '" + tag + "'", "Engine/Rendering/SceneGraph.cpp", __LINE__);
		std::string newTag = "GameObject" + std::to_string(gameObjects.size() + 1);
		_gameObject->SetTag(newTag);
		gameObjects[newTag] = _gameObject;
	}
	CollisionHandler::GetInstance()->AddGameObject(_gameObject);
}

GameObject* SceneGraph::GetGameObject(std::string tag) {
	if (gameObjects.find(tag) != gameObjects.end()) {
		return gameObjects[tag];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime) {
	for (auto g : gameObjects) {
		g.second->Update(deltaTime);
	}
}

void SceneGraph::Render(const Camera* camera) {
	for (auto m : models) {
		glUseProgram(m.first);
		for (auto v : m.second) {
			v->Render(camera);
		}
	}
	glUseProgram(0);
}

void SceneGraph::OnDestroy() {
	if (gameObjects.size() > 0) {
		for (auto g : gameObjects) {
			delete g.second;
			g.second = nullptr;
		}
		gameObjects.clear();
	}

	if (models.size() > 0) {
		for (auto m : models) {
			if (m.second.size() > 0) {
				for (auto v : m.second) {
					delete v;
					v = nullptr;
				}
				m.second.clear();
			}
		}
		models.clear();
	}
}