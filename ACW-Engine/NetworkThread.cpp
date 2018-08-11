#include "NetworkThread.h"

using namespace GameEngine;

void NetworkThread::AddTweakbarVars()
{
	// tweakbar
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Network | Target Hz", TW_TYPE_INT32, &_fps, " min=1 ");
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Network | Actual Hz", TW_TYPE_INT32, &_actualFps, " readonly='true'  ");
}

void NetworkThread::Run()
{
	_mutex->lock();
	std::cout << "Network thread Running, ID:" << myThread.get_id() << std::endl;
	_mutex->unlock();

	SetThreadAffinityMask(myThread.native_handle(), static_cast<DWORD_PTR>(THREAD_CORE_AFFINITY::CORE_ONE));
	SetThreadDescription(myThread.native_handle(), L"Network Thread");

	AddTweakbarVars();

	while (_isRunning)
	{
		if (!_forcePause)
		{
			if (FreqWait()) // cap to freq
			{
				_idle = false;
				UpdateActualFreqTime();

				_game->OnNetwork();
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