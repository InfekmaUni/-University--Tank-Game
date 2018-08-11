#include "ACWThread.h"

using namespace GameEngine;

void ACWThread::Start(std::shared_ptr<std::mutex> mutex)
{
	_mutex = mutex;
	_isRunning = true;
	_updateTimer = ACWTimer(1.0f / _fps);
	_fpsTimer = ACWTimer(1); // every second
	_updateTimer.Start();
	_idle = false;
	myThread = std::thread(&ACWThread::Run, this);
}

void ACWThread::Stop()
{
	_isRunning = false;
}

// timer to limit update calls to freq specified
bool ACWThread::FreqWait()
{
	_frequency = 1.0f / _fps; // update frequency for fps changes
	if ( _updateTimer.IsDone() )
	{
		_updateTimer.Start(1.0f / _fps);  // start again
		return true;
	}
	else
	{
		return false;
	} 

	return false;
}

void ACWThread::UpdateActualFreqTime()
{
	if (_fpsTimer.IsDone())
	{
		_fpsCounter++;
		if (_fpsCounter > 0)
		{
			_actualFps = static_cast<float>(_fpsCounter);
			_fpsCounter = 0;
		}
		_fpsTimer.Start(1); // start again - 1second (set in start)
	}
	else
	{
		_fpsCounter++;
	}
}