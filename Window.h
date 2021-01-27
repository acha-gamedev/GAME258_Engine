#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Window {

public:
	bool OnCreate();
	void OnDestroy();
	Window* GetWindow() const;
	int GetHeight() const;
	int GetWidth() const;
private:
	void GLInit();
	void PostInit();
};

#endif