#pragma once
#include "BaseSystem.h"
#include <string>
#include "Renderer.h"

namespace GameEngine
{
	class RenderableSystem : public BaseSystem
	{
		// structors
	public:
		RenderableSystem(std::string name) : BaseSystem(name)
		{}
		~RenderableSystem() = default;

		// functions
	public:
		virtual void Render(Renderer* renderer, Entity* ent) = 0;
		virtual void Shutdown() = 0;
		virtual void Initialise() = 0;
		virtual void OnMessage(Message* msg) {}
	};
}