#include "GameScene.h"
#include "../../Engine/Core/Debug.h"
#include <iostream>

GameScene::GameScene() : triangle(nullptr) {}

GameScene::~GameScene() {
	if (triangle) {
		delete triangle;
		triangle = nullptr;
	}
}

bool GameScene::OnCreate()
{
	Debug::LogInfo("Created Game Scene", __FILE__, __LINE__);
	std::cout << "Created Game Scene" << std::endl;

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(3);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	Vertex p;
	std::vector<Vertex> vertexList2;
	vertexList2.reserve(3);
	p.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList2.push_back(p);
	p.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList2.push_back(p);
	p.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList2.push_back(p);

	Model* model = new Model();
	model->AddMesh(new Mesh(vertexList));
	model->AddMesh(new Mesh(vertexList2));
	triangle = new GameObject(model);

	return true;
}

void GameScene::Update(const float dTime) {}

void GameScene::Render() {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (triangle) {
		triangle->Render();
	}
}