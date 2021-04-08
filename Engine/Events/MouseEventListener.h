#ifndef MOUSEEVENTLISTENER_H
#define MOUSEEVENTLISTENER_H

#include <SDL.h>
#include <glm/glm.hpp>

class CoreEngine;

class MouseEventListener {
private:
	static CoreEngine* engine;
	static glm::ivec2 currentPos;
	static glm::ivec2 previousPos;
	static bool firstUpdate;
public:
	MouseEventListener() = delete;
	MouseEventListener(const MouseEventListener&) = delete;
	MouseEventListener(MouseEventListener&&) = delete;
	MouseEventListener& operator=(const MouseEventListener&) = delete;
	MouseEventListener& operator=(MouseEventListener&&) = delete;
	~MouseEventListener();

	//Register a pointer to the engine instance
	static void RegisterEngine();
	//Resolve Event calls
	//PARAMS: sdlevent: the event data struct
	static void HandleEvents(const SDL_Event& sdlevent);
	//Resolve a mouse button press
	//PARAMS: button: the button pressed (Enum)
	static void MousePressed(const int button);
	//Resolve a mouse button release
	//PARAMS: button: the button released (Enum)
	static void MouseReleased(const int button);
	//Resolve scroll wheel movement
	//PARAMS: yAmount: the amount the scroll wheel was moved
	static void MouseScrolled(const int yAmount);
	//Resolve mouse movement
	static void MouseMoved();
	//Returns the previous position of the mouse
	inline static glm::ivec2 GetPreviousPosition() { return previousPos; }
	//Returns the current position of the mouse
	inline static glm::ivec2 GetCurrentPosition() { return currentPos; }
	//Returns the amount the mouse was moved
	static glm::ivec2 GetMouseOffset();
private:
	static void UpdatePositions();
};

#endif //MOUSEEVENTLISTENER_H