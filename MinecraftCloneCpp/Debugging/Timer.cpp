#include "Timer.h"

void Timer::start()
{
	if (mRunning)
	{
		return;
	}
	mRunning = true;

	mStartTime = std::chrono::steady_clock::now();
}

float Timer::stop()
{
	if (!mRunning) 
	{
		return 0;
	}

	mRunning = false;

	return getElapsedTime();
}

float Timer::getElapsedTime()
{
	auto currentTime = std::chrono::steady_clock::now();

	// get elapsed time in miliseconds
	float timerMilliSeconds = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - mStartTime).count() / 1000.0f;

	return timerMilliSeconds;
}
