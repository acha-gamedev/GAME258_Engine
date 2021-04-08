#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <SDL.h>
#include "MouseEventListener.h"

class EventListener {
public:
	EventListener() = delete;
	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator=(const EventListener&) = delete;
	EventListener& operator=(EventListener&&) = delete;
	~EventListener();

	//Resolve Event calls
	static void HandleEvents();
};

#endif //EVENTLISTENER_H