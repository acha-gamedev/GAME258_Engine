#include "StartScene.h"
#include "../../Engine/Core/Debug.h"
#include <iostream>

StartScene::StartScene() {}

StartScene::~StartScene() {}

bool StartScene::OnCreate()
{
	Debug::LogInfo("Created Start Scene", __FILE__, __LINE__);
	std::cout << "Created Start Scene" << std::endl;
	return true;
}

void StartScene::Update(const float dTime) {}

void StartScene::Render() {}