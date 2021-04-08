#include "EventListener.h"
#include "../Core/CoreEngine.h"

EventListener::~EventListener() {}

void EventListener::HandleEvents() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
        case SDL_QUIT:
            CoreEngine::GetInstance()->Exit();
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEWHEEL:
        case SDL_MOUSEMOTION:
            MouseEventListener::HandleEvents(sdlEvent);
            break;
        }
    }
}