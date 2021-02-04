#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
#include "Timer.h"
#include <memory>
#include "GameInterface.h"
#include "Scene.h"
#include "Debug.h"

class CoreEngine {
private:
	Window* window;
	bool isRunning;
	Timer* timer;
	unsigned int fps;
	GameInterface* gameInstance;
	unsigned int currentScene;

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

public:
	//remove copy and move constructors
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	//Initialize the engine; returns true if completed, false if an error occured
	//PARAMS: _name: the name of the window; _width: the width of the window, in pixels; _height: height of the window, in pixels
	bool OnCreate(std::string _name, int _width, int _height);

	//Run core loop of the engine
	void Run();

	//Exits the program
	void Exit();

	//Returns the pointer to the engine instance; creates it if necessary
	static CoreEngine* GetInstance();

	//Sets the game instance
	//PARAMS: _gameInstance: the pointer of the game instance to use;
	static void SetGameInstance(GameInterface* _gameInstance);

	//Returns the current scene ID
	inline unsigned int GetCurrentScene() { return currentScene; }
	
	//Sets the current scene by ID
	//PARAMS: newScene: the new scene's ID
	inline void SetCurrentScene(unsigned int newScene) { currentScene = newScene; }

	//Returns if the engine is running
	inline bool GetIsRunning() { return isRunning; }

private:
	CoreEngine();
	~CoreEngine();
	
	//Resolve event calls
	void HandleEvents();
	
	//Resolve physics and independent updates
	//PARAMS: dTime: the amount of time passed between updates
	void Update(const float dTime);
	
	//Draw the current scene to the window
	void Render();

	void OnDestroy();
};

#endif //COREENGINE_H