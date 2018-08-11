#pragma once
#include "Entity.h"
#include "BaseManager.h"

#include <vector>
#include <mutex>
#include <thread>
#include <atomic>

namespace GameEngine
{
	class Entity;
	class EntityManager : public BaseManager
	{
		// structors
	public:
		EntityManager() : BaseManager("EntityManager")
		{
			_entityList = std::vector<Entity*>();
		}
		~EntityManager() = default;

		// data
	private:
		std::vector<Entity*> _entityList; // global list - used by update
		std::vector<Entity*> _renderEntityList; // list used by render thread

		std::mutex _mut;
		std::atomic<unsigned>_entFrameRenderCount = 0; // total entities rendered in frame;
		std::atomic<unsigned> _entFrameUpdateCount = 0;
		std::atomic<bool> _doneRendering = false;

		// getters && setters
	public:
		Entity * AddEntity(Entity* ent);
		Entity* FindEntity(int entID);
		bool RemoveEntity(int entID);
		bool RemoveEntity(Entity* ent);

		const std::vector<Entity*>& GetEntityList() { std::lock_guard<std::mutex> lock(_mut); return _entityList; }
		int EntitiesCount() { return (int)_entityList.size(); }

		std::vector<Entity*> GetEntityRenderList() { std::lock_guard<std::mutex> lock(_mut); return _renderEntityList; }
		void AddEntityToRenderList(Entity* ent) 
		{ 
			std::lock_guard<std::mutex> lock(_mut);  
			_renderEntityList.push_back(ent); 
		}
		void RemoveEntityFromRenderList(Entity* ent)
		{
			std::lock_guard<std::mutex> lock(_mut);
			
			// remove ent
			int pos = static_cast<int>(std::find(_renderEntityList.begin(), _renderEntityList.end(), ent) - _renderEntityList.begin());
			if(pos != -1)
				_renderEntityList.erase(_renderEntityList.begin() + pos);
		}

		bool DoneRenderingEnts() 
		{ 
			//std::lock_guard<std::mutex> lock(_mut); 
			return _doneRendering;
		}
		void RestartEntityUpdateList()
		{
			//std::lock_guard<std::mutex> lock(_mut);

			_doneRendering = false;
		}

		void ResetEntCounters() 
		{
			//std::lock_guard<std::mutex> lock(_mut);
			_entFrameRenderCount = 0; _entFrameUpdateCount = 0; 
			_doneRendering = true;
		}
		void IncrementEntRenderFrameCounter() 
		{ 
			//std::lock_guard<std::mutex> lock(_mut); 
			_entFrameRenderCount++; 
		}
		void IncrementEntUpdateFrameCounter() 
		{
			//std::lock_guard<std::mutex> lock(_mut); 
			_entFrameUpdateCount++; 
		}
		bool DoneUpdatingAndRendering() 
		{
			std::lock_guard<std::mutex> lock(_mut);
			if (_entFrameRenderCount == _entityList.size() && _entFrameUpdateCount == _entityList.size())
				return true;
			else
				return false;
		}

		// functions
	public:
		void Update(float dt);
		void Render();
		void Shutdown();
		void Initialise();
		void OnMessage(Message* msg);
	};
}