#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engine = nullptr;
glm::ivec2 MouseEventListener::currentPos = glm::ivec2();
glm::ivec2 MouseEventListener::previousPos = glm::ivec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener() {}

void MouseEventListener::RegisterEngine() {
	engine = CoreEngine::GetInstance();
}

void MouseEventListener::HandleEvents(const SDL_Event& sdlevent) {
	switch (sdlevent.type) {
	case SDL_MOUSEBUTTONDOWN:
		UpdatePositions();
		MousePressed(sdlevent.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		UpdatePositions();
		MouseReleased(sdlevent.button.button);
		break;
	case SDL_MOUSEMOTION:
		UpdatePositions();
		MouseMoved();
		break;
	case SDL_MOUSEWHEEL:
		MouseScrolled(sdlevent.wheel.y);
		break;
	}
}

void MouseEventListener::MousePressed(const int button) {
	if (engine) {
		engine->MousePressed(button, currentPos);
	}
}

void MouseEventListener::MouseReleased(const int button) {
	if (engine) {
		engine->MouseReleased(button, currentPos);
	}
}

void MouseEventListener::MouseScrolled(const int yAmount) {
	if (engine) {
		engine->MouseScrolled(yAmount);
	}
}

void MouseEventListener::MouseMoved() {
	if (engine) {
		engine->MouseMoved(currentPos);
	}
}

glm::ivec2 MouseEventListener::GetMouseOffset() {
	return glm::ivec2(currentPos.x - previousPos.x, previousPos.y - currentPos.y);
}

void MouseEventListener::UpdatePositions() {
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);
	tempY = engine->GetWindowSize().y - tempY;
	if (firstUpdate) {
		previousPos = currentPos = glm::ivec2(tempX, tempY);
		firstUpdate = false;
	}
	else if (tempX != currentPos.x || tempY != currentPos.y) {
		previousPos = currentPos;
		currentPos = glm::ivec2(tempX, tempY);
	}
}