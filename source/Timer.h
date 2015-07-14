#ifndef TIMER_H_
#define TIMER_H_

#include <SDL.h>

class Timer
{
public:
	Timer();
	
	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();
	Uint32 getDeltaTicks();

	bool isStarted() { return started_; }
	bool isPaused() { return paused_; }

private:
	Uint32 startTicks_;
	Uint32 pausedTicks_;

	Uint32 previousTicks_;

	bool paused_;
	bool started_;
};

#endif