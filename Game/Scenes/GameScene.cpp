#include "GameScene.h"
#include "../../Engine/Core/Debug.h"
#include "../../Engine/Core/CoreEngine.h"
#include "../../Engine/Rendering/TextureHandler.h"
#include <iostream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	//if (triangle) {
	//	delete triangle;
	//	triangle = nullptr;
	//}
}

bool GameScene::OnCreate()
{
	Debug::LogInfo("Created Game Scene", __FILE__, __LINE__);
	std::cout << "Created Game Scene" << std::endl;

	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLight(new LightSource(glm::vec3(0.0f, 0.5f, 2.0f),
		0.1f, 0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f)));
	
	//Model* model = new Model(ShaderHandler::GetInstance()->GetShader("BasicShader"),
	//	"Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl");
	//triangle = new GameObject(model);
	//triangle->SetScale(glm::vec3(0.5, 0.5, 0.5));

	Model* modelApple = new Model(ShaderHandler::GetInstance()->GetShader("BasicShader"),
		"Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl");
	SceneGraph::GetInstance()->AddModel(modelApple);
	Model* modelDice = new Model(ShaderHandler::GetInstance()->GetShader("BasicShader"),
		"Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl");
	SceneGraph::GetInstance()->AddModel(modelDice);

	GameObject* apple = new GameObject(modelApple);
	apple->SetScale(glm::vec3(0.5, 0.5, 0.5));
	apple->SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
	GameObject* dice = new GameObject(modelDice);
	dice->SetScale(glm::vec3(0.5, 0.5, 0.5));
	dice->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
	SceneGraph::GetInstance()->AddGameObject(apple, "Apple");
	SceneGraph::GetInstance()->AddGameObject(dice, "Dice");

	return true;
}

void GameScene::Update(const float dTime) {

	SceneGraph::GetInstance()->Update(dTime);

	//float  _angle = triangle->GetAngle();
	//_angle += 0.005f;
	//triangle->SetAngle(_angle);
}

void GameScene::Render() {

	SceneGraph::GetInstance()->Render(CoreEngine::GetInstance()->GetCamera());

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//if (triangle) {
	//	triangle->Render(CoreEngine::GetInstance()->GetCamera());
	//}
}