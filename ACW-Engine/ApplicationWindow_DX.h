#pragma once
#include "Renderer_DX.h"
#include "ApplicationWindow.h"

namespace GameEngine
{
	class Game;
	class ApplicationWindow_DX : public ApplicationWindow
	{
	public:
		ApplicationWindow_DX(Game* game, int width, int height, HINSTANCE, int nCmdShow);
		~ApplicationWindow_DX() = default;

		// data
	protected:
		HWND	_hWnd;
		// getters & setters
	public:
		HWND GetHWND() { return _hWnd; }

		// functions
	public:
		void Initialise();
		void Shutdown();
		void Run();

		// Windows Message loop
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};
}