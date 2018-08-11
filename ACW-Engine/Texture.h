#pragma once
#include <string>
#include "Renderer.h"

namespace GameEngine
{
	class Texture
	{
	public:
		Texture(std::string name) : _textureName(name)
		{}
		~Texture() = default;

	protected:
		std::string _textureName;

		// getters & setters
	public:
		std::string GetName() { return _textureName; }

	public:
		virtual void Shutdown() = 0;
		virtual void Create(Renderer* renderer) = 0;
		virtual void Bind(Renderer* renderer, int startSlot, int numText) = 0;
	};
}