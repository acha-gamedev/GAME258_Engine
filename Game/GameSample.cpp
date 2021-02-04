#include "GameSample.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"

GameSample::GameSample() : currentScene(nullptr), currentSceneNum(0) {}

GameSample::~GameSample() {
	if (currentScene) {
		delete currentScene;
		currentScene = nullptr;
	}
}

bool GameSample::OnCreate() {
	if (currentScene) { delete currentScene; }
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}
	Debug::LogError("Core Engine scene not initialized to 0", __FILE__, __LINE__);
	return false;
}

void GameSample::Update(const float dTime) {
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(dTime);
}

void GameSample::Render() {
	currentScene->Render();
}

void GameSample::BuildScene() {
	if (currentScene) { delete currentScene; }

	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default: //case 0 or unreconized scene number
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		Debug::LogError("Scene failed to create", __FILE__, __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
}