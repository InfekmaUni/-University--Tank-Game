#include "UpdateThread.h"
using namespace GameEngine;

void UpdateThread::AddTweakbarVars()
{
	// tweakbar
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Update | Avg. Timestep", TW_TYPE_FLOAT, &_averageTimeStep, " readonly=`true` ");
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Update | Target Hz", TW_TYPE_INT32, &_fps, " min=1 ");
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Update | Actual Hz", TW_TYPE_INT32, &_actualFps, " readonly='true'  ");
}

void UpdateThread::Run()
{
	_mutex->lock();
	std::cout << "Update thread Running, ID:" << myThread.get_id() << std::endl;
	_mutex->unlock();

	SetThreadAffinityMask(myThread.native_handle(), static_cast<DWORD_PTR>(THREAD_CORE_AFFINITY::CORE_THREE));
	SetThreadDescription(myThread.native_handle(), L"Update Thread");

	float sampleLength = 1;
	_averageTimeStepTimer = ACWTimer(sampleLength);
	_averageTimeStepTimer.Start();

	// tweakbar
	AddTweakbarVars();
	
	// dt
	_game->UpdateDeltaTime();

	while (_isRunning)
	{
		if (!_forcePause)
		{
			if (FreqWait()) // cap to freq
			{
				_idle = false;

			//	_game->UpdateFixedDeltaTime(1.0f / _fps);
				_game->UpdateDeltaTime();

				// average timestep
				UpdateAverageTimeStep(Game::myGame->GetDeltaTime());
				UpdateActualFreqTime();

				_game->OnUpdate();
			}
		}
		else
		{
			_idle = true;
		}
	}
	_isRunning = false;
	myThread.join();
}

void UpdateThread::UpdateAverageTimeStep(float dt)
{
	timeStep.push_back(dt);
	
	if (_averageTimeStepTimer.IsDone()) // if done
	{
		_averageTimeStepTimer.Start();
		// calculate average time step
		float temp = 0;
		for (auto& step : timeStep)
			temp += step;
		temp = temp / (timeStep.size() + 1);
		_averageTimeStep = temp;
		timeStep.clear(); // clear vector for next sample
	}
}