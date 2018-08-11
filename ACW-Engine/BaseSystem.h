#pragma once
#include <string>
#include <vector>
#include "Entity.h"
#include "Message.h"

namespace GameEngine
{
	class Entity;
	class BaseSystem
	{
		// structors
	public:
		BaseSystem(std::string name) : _systemName(name) {}
		~BaseSystem() = default;

		// getters
	public:
		const std::string GetName()
		{
			return _systemName;
		}

		// functions
	public:
		virtual void Shutdown() = 0;
		virtual void Initialise() = 0;
		virtual void OnMessage(Message* msg) = 0;

		// data
	protected:
		std::string _systemName;
	};
}