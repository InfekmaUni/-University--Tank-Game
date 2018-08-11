#pragma once
#include <string>
#include "Renderer.h"
#include "Message.h"

namespace GameEngine
{
	class BaseManager
	{
	public:
		BaseManager(std::string name) : _managerName(name)
		{}
		~BaseManager() = default;

		virtual void Update(float dt) {}
		virtual void Render(Renderer* renderer) {}
		virtual void Shutdown() = 0;
		virtual void Initialise() = 0;
		virtual void OnMessage(Message* msg) {}
		virtual void OnNetwork() {}

		// getters & setters
	public:
		std::string GetName() { return _managerName; }

		// data
	private:
		std::string _managerName;
	};
}
