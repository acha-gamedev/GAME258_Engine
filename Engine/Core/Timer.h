#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

constexpr float MILLI_TO_SEC = 1000.0f;

class Timer {
private:
	unsigned int currentTick, prevTick;
public:
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	Timer();

	//Configures the timer to start
	void Start();

	//Updates the current and previous tick values
	void Update();

	//Returns the amount of time since previous update
	float GetDeltaTime() const;

	//Returns how many milliseconds to wait between frames
	//PARAMS: _fps: the target frame rate
	unsigned int GetSleepTime(const unsigned int _fps) const;

	//Returns the current ticks, in milliseconds
	unsigned int GetTicksMs() const;

	//Returns the current ticks, in seconds
	float GetTicksSec() const;
};

#endif //TIMER_H