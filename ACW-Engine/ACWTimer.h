#pragma once
#include <time.h>

class ACWTimer
{
public:
	// duration in seconds
	ACWTimer(float duration) : _duration(duration)
	{}
	ACWTimer()
	{}
	~ACWTimer() = default;

	// data
private:
	float _duration;

	clock_t _startTime;
	clock_t _curTime;

	// getters & setters
public:
	bool IsDone() { return (_startTime + (_duration * CLOCKS_PER_SEC) < clock()); }
	float ElapsedSeconds() { return static_cast<float>((clock() - _startTime) / CLOCKS_PER_SEC); }

public:
	void Start() { _startTime = clock(); }
	void Start(float newDuration) { _duration = newDuration; Start(); }
};