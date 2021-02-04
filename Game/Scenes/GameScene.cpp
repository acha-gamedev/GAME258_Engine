#include "GameScene.h"
#include "../../Engine/Core/Debug.h"
#include <iostream>

GameScene::GameScene() {}

GameScene::~GameScene() {}

bool GameScene::OnCreate()
{
	Debug::LogInfo("Created Game Scene", __FILE__, __LINE__);
	std::cout << "Created Game Scene" << std::endl;
	return true;
}

void GameScene::Update(const float dTime) {}

void GameScene::Render() {}