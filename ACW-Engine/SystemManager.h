#pragma once
#include <vector>

#include "RenderableSystem.h"
#include "UpdateableSystem.h"
#include "BaseManager.h"

#include "EntityManager.h"
#include "SceneManager.h"


namespace GameEngine
{
	class SystemManager : public BaseManager
	{
	public:
		SystemManager() : BaseManager("SystemManager")
		{}
		~SystemManager() = default;

		// functions
	public:
		void Update(float dt);
		void Render(Renderer* renderer);
		void Initialise();
		void Shutdown();
		void OnMessage(Message* msg);

		// getters & setters
	public:
		void AddUpdateSystem(UpdateableSystem* system)
		{ 
			if (std::find(_updateSystemList.begin(), _updateSystemList.end(), system) == _updateSystemList.end())
				_updateSystemList.push_back(system);
		}
		void AddRenderableSystem(RenderableSystem* system)
		{
			if (std::find(_renderSystemList.begin(), _renderSystemList.end(), system) == _renderSystemList.end())
				_renderSystemList.push_back(system);
		}
		
		RenderableSystem* GetRenderSystem(std::string name)
		{
			for (auto const& system : _renderSystemList)
			{
				if (system->GetName() == name)
				{
					return system;
				}
			}
		}

		UpdateableSystem* GetUpdateSystem(std::string name)
		{
			for (auto const& system : _updateSystemList)
			{
				if (system->GetName() == name)
				{
					return system;
				}
			}
		}

		// data
	private:
		std::vector<RenderableSystem*> _renderSystemList;
		std::vector<UpdateableSystem*> _updateSystemList;

	};
}
