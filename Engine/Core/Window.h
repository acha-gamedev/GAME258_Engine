#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Window {
private:
	//The pointer to the window
	SDL_Window* window;
	//The GL rendering context
	SDL_GLContext glContext;
	int width, height;

public:
	Window();
	~Window();

	//Create and intialize the window
	//PARAMS: _name: the name of the window; _width: the width of the window, in pixels; _height: height of the window, in pixels
	//OUT: true if completed, false if an error occured
	bool OnCreate(std::string _name, int _width, int _height);
	//Destroy and clean up the window
	void OnDestroy();
	//Get the pointer to the window
	inline SDL_Window* GetWindow() const { return window; }
	//Get the width of the window, in pixels
	inline int GetWidth() const { return width; }
	//Get the height of the window, in pixels
	inline int GetHeight() const { return height; }
private:
	//Intialise GL settings; call before window construction
	void PreWindowConfig();
	//Intialise GL settings; call after window construction
	void PostWindowConfig();
};

#endif