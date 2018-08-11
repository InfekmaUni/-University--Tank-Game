#pragma once
#include "Game.h"
#include "Entity.h"
#include "EntityManager.h"

namespace GameEngine
{
	class Entity;
	class EntityManager;
	class SceneManager;
	class Game;
	class Scene
	{
		// structors
	public:
		Scene(int id);
		~Scene() = default;

		// data
	protected:
		int _sceneID;
		Game* _gameInstance;
		std::vector<BaseManager*> _managers;

		// getters & setters
	public:
		int GetSceneID() { return _sceneID; }
		void AddManager(BaseManager* manager) { _managers.push_back(manager); }
		BaseManager* GetManagerByName(std::string name)
		{
			for (auto& manager : _managers)
			{
				if (manager->GetName() == name)
					return manager;
			}
			return nullptr;
		}


		// functions
	public:
		void Quit();

		// called when respective events happen
		virtual void OnInitialise();
		virtual void OnUpdate(float delta);
		virtual void OnRender(Renderer* renderer);
		virtual void OnShutdown();
		virtual void OnMessage(Message* msg);
	};
}