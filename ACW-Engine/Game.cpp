#include "Game.h"
#include "ApplicationWindow_DX.h"

#include "EntityManager.h"
#include "SystemManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

using namespace GameEngine;

Game* Game::myGame = NULL;

Game::Game()
{
	myGame = this;
}

void Game::Initialise(ApplicationWindow* window)
{
	_renderer = window->GetRenderer();

	if (_tweakBar == nullptr)
	{
		_tweakBar = new ACWTweakBar();
		_tweakBar->Initialise(_renderer);

		// create new bar
		int pos[2] = { 25, 25 };
		int size[2] = { 300, 200 };
		int gameBarID = Game::myGame->GetTweakBar()->CreateNewBar("Infographics", pos, size);
		//_tweakBar->ToggleTweakBar("Infographics", false);
	}

	_mouse = new GameMouse();
	_keyboard = new GameKeyboard();

	if (_reset) // restart threads
	{
		_updateThread->ForcePause(false);
		_updateThread->AddTweakbarVars();
		_updateThread->SetFPS(60);

		_renderThread->ForcePause(false);
		_renderThread->AddTweakbarVars();
		_renderThread->SetFPS(60);

		_networkThread->ForcePause(false);
		_networkThread->AddTweakbarVars();
		_networkThread->SetFPS(60);
	}
	else // real init - init threads
	{
		_updateThread = new UpdateThread(this, 60);
		_renderThread = new RenderThread(this, 60);
		_networkThread = new NetworkThread(this, 60);
	}

	_mu = std::make_shared<std::mutex>();

	if(!_reset)
		_startTime = static_cast<float>(clock()); // log application start clock


	_lastTime = _appRunTime = clock();

	_reset = false;
}

void Game::BroadcastMessage(Message* msg)
{
	if (_reset)
		return;

	for (auto const& manager : _managerList)
	{
		manager->OnMessage(msg);
	}

	ListenMessage(msg);
}

void Game::ListenMessage(Message* msg)
{
	// listening to messages
	if (msg->GetType() == "KeyPress")
	{
		KeyPressMessage* keyMsg = (KeyPressMessage*)msg;
		int key = keyMsg->GetKey();
		bool downPress = keyMsg->GetKeyPress();
		bool downHeld = keyMsg->GetDownState();

		if (downHeld || downPress)
		{
			int frequencySteps = 1;
			if (key == 82 && downPress) // r - reset
			{
				_reset = true;
			}
			else if (key == 79) // o - physics +frequency
			{
				_updateThread->IncreaseFrequency(frequencySteps);
			}
			else if (key == 76) // l = physics -frequency
			{
				_updateThread->LowerFrequency(frequencySteps);
			}
			else if (key == 85)	// U = rendering +frequency
			{
				_renderThread->IncreaseFrequency(frequencySteps);
			}
			else if (key == 74) // J - rendering -frequency;
			{
				_renderThread->LowerFrequency(frequencySteps);
			}
			else if (key == 89)		// Y - network +frequency
			{
				_networkThread->IncreaseFrequency(frequencySteps);
			}
			else if (key == 72)// h - network -frequen
			{
				_networkThread->LowerFrequency(frequencySteps);
			}
			else if (key == 112 && downPress) // f1
			{
				_tweakBar->ToggleTweakBar("Infographics", true);
			}
			else if (key == 113 && downPress) // f2
			{
				_tweakBar->ToggleTweakBar("Infographics", false);
			}
		}
	}
}

void Game::OnNetwork()
{
	for (auto const& manager : _managerList)
	{
		manager->OnNetwork();
	}
}

void Game::Shutdown()
{
	_tweakBar->Shutdown();
	_tweakBar = nullptr;

	// stop threads
	if (!_reset)
	{
		_renderThread->Stop();
		_updateThread->Stop();
		_networkThread->Stop();
	
		while ( _renderThread->IsRunning() ) {} // wait for thread to finish
		while ( _updateThread->IsRunning() ) {} // wait for thread to finish
		while ( _networkThread->IsRunning() ) {} // wait for thread to finish
	}
	else
	{
		_renderThread->ForcePause(true);
		_updateThread->ForcePause(true);
		_networkThread->ForcePause(true);

		while ( !_renderThread->IsIdle() ) {} // wait till thread starts idling
		while ( !_updateThread->IsIdle() ) {} // wait till thread starts idling
		while ( !_networkThread->IsIdle() ) {} // wait till thread starts idling
	}

	for (auto const& manager : _managerList)
	{
		manager->Shutdown();
		delete manager;
	}
	_managerList.clear();

	delete _mouse;
	delete _keyboard; 
}

int Game::Run()
{
	if (_reset)
		return 2; // reset

	// launch threads
	if (!_updateThread->IsRunning())
	{
		_updateThread->Start(_mu);
	}
	if (!_renderThread->IsRunning())
	{
		_renderThread->Start(_mu);
	}
	if (!_networkThread->IsRunning())
	{
		_networkThread->Start(_mu);
	}

	//OnUpdate();
	//OnRender();

	return 1; // everything fine
}

void Game::OnUpdate()
{
	if (!_reset && !_pausedSimulation)
	{
		for (auto const& manager : _managerList)
		{
			manager->Update(_deltaTime);
		}

		_keyboard->Update();
	}
}

void Game::UpdateFixedDeltaTime(float freq)
{
	_deltaTime = freq;
}

void Game::UpdateDeltaTime()
{
	float curTime = static_cast<float>(clock());
	_deltaTime = (curTime - _lastTime) / CLOCKS_PER_SEC;
	_lastTime = curTime;
	_appRunTime = (curTime - _startTime) / CLOCKS_PER_SEC;
	float fps = 1 / _deltaTime;
}

void Game::OnRender()
{
	if (!_reset && !_pausedSimulation)
	{
		for (auto const& manager : _managerList)
		{
			manager->Render(_renderer);
		}
	}
}