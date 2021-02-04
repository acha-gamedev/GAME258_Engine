#ifndef GAMESAMPLE_H
#define GAMESAMPLE_H

#include "../Engine/Core/CoreEngine.h"

class GameSample : public GameInterface {
private:
	int currentSceneNum;
	Scene* currentScene;

public:
	GameSample();
	virtual ~GameSample();
	
	//Create and intialize the game instance; returns true if successful, false if an error occured
	bool OnCreate() override;

	//Update any time-based actions
	//PARAMS: dTime: the time since last frame, in seconds
	void Update(const float dTime) override;

	//Draw current scene to window
	void Render() override;

private:
	void BuildScene();
};

#endif //GAMESAMPLE