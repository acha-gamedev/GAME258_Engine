#include "Timer.h"

Timer::Timer() : currentTick(0), prevTick(0) {}

void Timer::Start() {
	currentTick = prevTick = SDL_GetTicks();
}

void Timer::Update() {
	prevTick = currentTick;
	currentTick = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
	return (currentTick - prevTick) / MILLI_TO_SEC;
}

unsigned int Timer::GetSleepTime(const unsigned int _fps) const
{
	unsigned int mspf = 1000 / _fps;
	if (mspf == 0) { return 0; }
	unsigned int sleep = mspf - (SDL_GetTicks() - currentTick);
	if (sleep > mspf) { return mspf; }
	return sleep;
}

unsigned int Timer::GetTicksMs() const
{
	return currentTick;
}

float Timer::GetTicksSec() const
{
	return currentTick / MILLI_TO_SEC;
}