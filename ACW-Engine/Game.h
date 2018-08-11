#pragma once

#include <vector>
#include <time.h>

#include "BaseManager.h"
#include "BaseSystem.h"

#include "Renderer.h"
#include "ApplicationWindow.h"

#include "RenderThread.h"
#include "UpdateThread.h"
#include "NetworkThread.h"

#include "ACWTweakBar.h"
#include "KeyPressMessage.h"

#include "GameMouse.h"
#include "GameKeyboard.h"

namespace GameEngine
{
	class GameMouse;
	class GameKeyboard;
	class RenderThread;
	class UpdateThread;
	class NetworkThread;
	class ApplicationWindow;
	class Game
	{
		// static singleton
	public:
		static Game* myGame;

	public:
		Game();
		~Game() = default;

		// data
	protected:
		float _startTime;
		float _lastTime;
		float _deltaTime;
		float _appRunTime;
		std::vector<BaseManager*> _managerList;
		ApplicationWindow* _window; // window
		Renderer* _renderer;
		bool _quitFlag = false;
		bool _pausedSimulation = false;
		bool _reset = false;
		bool _init = false;
		ACWTweakBar* _tweakBar;

		std::shared_ptr<std::mutex> _mu;

		RenderThread* _renderThread;
		UpdateThread* _updateThread;
		NetworkThread* _networkThread;

		GameMouse* _mouse;
		GameKeyboard* _keyboard;

		// getters & setters
	public:
		bool GetResetFlag() { return _reset; }
		bool GetQuitFlag() { return _quitFlag; }
		void SetQuitFlag() { _quitFlag = true; }
		float GetDeltaTime() { return _deltaTime; }
		bool AddManager(BaseManager* manager) 
		{
			if (std::find(_managerList.begin(), _managerList.end(), manager) == _managerList.end()) // if manager doesn't already exist
			{
				_managerList.push_back(manager);
				return true;
			}
			return false;
		}
		void RemoveManager(BaseManager* manager)
		{
			for (unsigned i = 0; i < _managerList.size(); i++)
			{
				if (_managerList.at(i)->GetName() == manager->GetName())
				{
					_managerList.erase(_managerList.begin() + i);
				}
			}
		}

		BaseManager* GetManager(std::string managerName)
		{
			for (auto const& manager : _managerList)
			{
				if (manager->GetName() == managerName)
					return manager;
			}
			return nullptr;
		}

		std::shared_ptr<std::mutex> GetMutex()
		{
			return _mu;
		}
		ACWTweakBar* GetTweakBar() { return _tweakBar; }

		GameMouse* GetMouse() { return _mouse; }
		GameKeyboard* GetKeyboard() { return _keyboard; }
		void TogglePause() { _pausedSimulation = !_pausedSimulation; }

		// functions
	public:
		virtual void Initialise(ApplicationWindow* window);
		virtual void Shutdown();
		virtual int Run();

		virtual void OnUpdate();
		virtual void OnRender();
		virtual void OnNetwork();

		virtual void UpdateDeltaTime();
		virtual void UpdateFixedDeltaTime(float freq);
		virtual void BroadcastMessage(Message* msg);
		virtual void ListenMessage(Message* msg);
	};
}