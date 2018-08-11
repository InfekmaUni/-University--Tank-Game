#include "RenderThread.h"
#include <iostream>
using namespace GameEngine;

void RenderThread::AddTweakbarVars()
{
	// tweakbar
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Render | Target Hz", TW_TYPE_INT32, &_fps, " min=1 ");
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Render | Actual Hz", TW_TYPE_INT32, &_actualFps, " readonly='true'  ");
}

void RenderThread::Run()
{
	_mutex->lock();
	std::cout << "Render thread Running, ID:" << myThread.get_id() << std::endl;
	_mutex->unlock();

	//auto threadTask = static_cast<RenderThread*>(data);
	SetThreadAffinityMask(myThread.native_handle(), static_cast<DWORD_PTR>(THREAD_CORE_AFFINITY::CORE_ONE));
	SetThreadDescription(myThread.native_handle(), L"Render Thread");
	
	AddTweakbarVars();

	while (_isRunning)
	{
		if (!_forcePause)
		{
			if (FreqWait()) // cap to freq
			{
				_idle = false;
				UpdateActualFreqTime();
				_game->OnRender();
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