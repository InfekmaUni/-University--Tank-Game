#pragma once
#include "Vector4.h"

namespace GameEngine
{
	class Renderer
	{
		// structors
	public:
		Renderer() : _clearColor(0, 0, 1, 0)
		{}
		~Renderer() = default;

		// data
	protected:
		Vector4 _clearColor;

		// getters & setters
	public:
		Vector4 GetClearColor() { return _clearColor; }
		void SetClearColor(Vector4 newColor) { _clearColor.set(newColor); }

		// functions
	public:
		virtual void Initialise(int width, int height) = 0;
		virtual void Shutdown() = 0;
		virtual void ClearScreen() = 0;
		virtual void SwapBuffers() = 0;
	};
}