#pragma once
#include "BaseSystem.h"
#include <string>

namespace GameEngine
{
	class UpdateableSystem : public BaseSystem
	{
		// structors
	public:
		UpdateableSystem(std::string name) : BaseSystem(name)
		{}
		~UpdateableSystem() = default;

		// functions
	public:
		virtual void Update(float dt, Entity* ent) = 0;
		virtual void Shutdown() {}
		virtual void Initialise() {}
		virtual void OnMessage(Message* msg) {}
	};
}