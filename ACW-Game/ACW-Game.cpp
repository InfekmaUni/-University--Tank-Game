// ACW-Game.cpp : Defines the entry point for the console application.
//

#define _WINSOCKAPI_
#include <windows.h>
#include <windowsx.h>
#include <d3d11.h>

// engine headers
#include "TankGame.h"
#include "ApplicationWindow_DX.h"

// game headers
#include "GameScene.h"

#pragma warning(disable:4996) // disable freopen warning

const bool VISIBLE_CONSOLE = true;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	if (VISIBLE_CONSOLE) {
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
	}

	// create game instance
	TankGame tankGame = TankGame();

	// create window
	GameEngine::ApplicationWindow_DX dxWindowApp = GameEngine::ApplicationWindow_DX(&tankGame, SCREEN_WIDTH, SCREEN_HEIGHT, hInstance, nCmdShow);

	// start
	dxWindowApp.Run();

    return 0;
}