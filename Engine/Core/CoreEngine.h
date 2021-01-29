#ifndef COREENGINE_H
#define COREENGINE_H

#include "Window.h"
#include <memory>

class CoreEngine {
private:
	Window* window;
	bool isRunning;

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

public:
	//remove copy and move constructors
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;

	//Initialize the engine
	//PARAMS: _name: the name of the window; _width: the width of the window, in pixels; _height: height of the window, in pixels
	//OUT: true if completed, false if an error occured
	bool OnCreate(std::string _name, int _width, int _height);
	//Run core loop of the engine
	void Run();
	//Get the pointer to the engine instance; creates it if necessary
	static CoreEngine* GetInstance();
private:
	CoreEngine();
	~CoreEngine();
	//resolve event calls
	void HandleEvents();
	//resolve physics and independent updates
	//PARAMS: dTime: the amount of time passed between updates
	void Update(const float dTime);
	//draw the current scene to the window
	void Render();
	void OnDestroy();
};

#endif