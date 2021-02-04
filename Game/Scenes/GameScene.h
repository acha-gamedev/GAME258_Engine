#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/Scene.h"

class GameScene : public Scene {
public:
	GameScene();
	virtual ~GameScene();
	
	//Create and initialize the scene; returns true if successful, false if an error occured
	bool OnCreate() override;

	//Update any time-based actions
	//PARAMS: dTime: the time since last frame, in seconds
	void Update(const float dTime) override;

	//Draw current scene to window
	void Render() override;
};

#endif //GAMESCENE_H