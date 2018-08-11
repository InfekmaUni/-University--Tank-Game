#pragma once
#include <map>
#include <vector>
#include <mutex>

#include "Component.h"
#include "Message.h"
#include "EntityManager.h"
#include "Game.h"

namespace GameEngine
{
	class EntityManager;
	class Component;
	class Entity
	{
		// structors
	public:
		Entity();
		Entity(bool add); // whether to add ent to ent list or not
		~Entity() = default;

		// getters & setters
	public:
		void SetFakeDeath(bool val) { _isFakeDeath = val; }
		bool GetFakeDeath() { return _isFakeDeath; }

		void SetIsAlive(bool val) { _isAlive = val; }
		bool GetIsAlive() { return _isAlive; }
		bool AddComponent(Component* component);
		Component* GetComponent(std::string type);
		bool HasComponent(std::string type);
		bool HasComponent(std::vector<std::string> types);
		bool HasComponent(const std::string types[], int length);
		int GetID() { return _entityID; }
		void SetID(int id) { _entityID = id; }
		bool GetInit() { return _init; }
		void SetInit(bool val) { _init = val; }

		void LockEntity() { _mut.lock(); }
		void UnlockEntity() { _mut.unlock(); }
		std::mutex& GetMutex() { return _mut; }
		void SetEntityName(std::string name) { _entityName = name; }
		std::string GetEntityName() { return _entityName; }

		void AddListener(std::string msg, Component* component);
		void RemoveMessageListener(std::string msg, Component* component);
		// data
	protected:
		std::map<std::string, Component*> _components;
		std::map<std::string, std::vector<Component*>> _messageListener; // components registered to an event

		bool _isAlive = true;
		bool _isFakeDeath = false;
		int _entityID = 0;
		std::string _entityName = "Undefined";
		bool _init = false;
		std::mutex _mut;

		// functions
	public:
		virtual void OnUpdate(float dt);
		virtual void OnRender() {}
		virtual void OnShutdown();
		virtual void OnInitialise() { _init = true; }
		virtual void OnMessage(Message* msg);
	};
}