#pragma once
#include "Game.h"
#include "Renderer.h"

namespace GameEngine
{
	class Game;
	class ApplicationWindow
	{
	public:
		static ApplicationWindow* Window;

	public:
		ApplicationWindow(Game* game, int width, int height) : _game(game), _width(width), _height(height)
		{
			Window = this;
		}
		~ApplicationWindow() = default;

		// data
	protected:
		Game* _game;
		int _width;
		int _height;
		Renderer* _renderer;

		// getters & setters
	public:
		int GetWidth() { return _width; }
		int GetHeight() { return _height; }
		Game* GetGame() { return _game; }
		Renderer* GetRenderer() { return _renderer; }

		// functions
	public:
		virtual void Run() = 0;
		virtual void Initialise() = 0;
		virtual void Shutdown() = 0;
	};
}