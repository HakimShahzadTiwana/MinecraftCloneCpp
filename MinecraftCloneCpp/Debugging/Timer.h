#pragma once
#pragma once
#include <chrono>

class Timer {
public:
	// Starts the timer object
	void start();

	// Stops the timer and returns the time elapsed since it started
	float stop();

	// Returns the elapsed time in miliseconds
	float getElapsedTime();
private:

	bool mRunning = false;

	std::chrono::time_point<std::chrono::steady_clock> mStartTime{};
};