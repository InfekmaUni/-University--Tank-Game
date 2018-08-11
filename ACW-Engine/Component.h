#pragma once
#include "Entity.h"
#include <string>
#include <vector>
#include "Message.h"

namespace GameEngine
{
	class Entity;
	class Component
	{
	public:
		Component(std::string type, Entity* parent);
		~Component() = default;

		// getters & setters
	public:
		Entity * GetEntity() const {return _parent;}
		std::string GetComponentType() const { return _componentType; }
		bool IsInit() { return _init; }
		void SetInit(bool val) { _init = val; }

		// data
	protected:
		std::string _componentType;
		Entity* _parent;
		bool _init;

		// component messages for entity OnStart() etc
	public:
		virtual void Initialise() {}
		virtual void Update(float dt) {}
		virtual void OnMessage(Message* msg) {}
		virtual void Shutdown() {}
		
		void BroadcastMessage(Message* msg);
	};
}