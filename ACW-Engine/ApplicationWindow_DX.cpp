#include "ApplicationWindow_DX.h"

using namespace GameEngine;

ApplicationWindow_DX::ApplicationWindow_DX(Game* game, int width, int height, HINSTANCE hInstance, int nCmdShow)
	: ApplicationWindow(game, width, height)
{

	// Reset RNG
	srand(time(NULL));

	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = ApplicationWindow_DX::WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	RECT wr = { 0, 0, _width, _height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);

	_hWnd = CreateWindowEx(NULL,
		L"WindowClass",
		L"ACW Tank",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, nCmdShow);
	SetForegroundWindow(_hWnd);
	SetFocus(_hWnd);
	HANDLE mouseHandle = SetCapture(_hWnd);
}

void ApplicationWindow_DX::Run()
{
	int state = 1;
	MSG msg;
	while (!_game->GetQuitFlag())
	{
		Initialise(); // initialise
		state = 1; // reset state to 1
		while (state == 1 && !_game->GetQuitFlag()) // everything is fine
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				if (msg.message == WM_QUIT)
					break;
			}

			state = _game->Run();
		}

		// Clean up DirectX
		Shutdown();
	}
}

void ApplicationWindow_DX::Initialise()
{
	// initialise dx renderer
	if (!_game->GetResetFlag())
	{
		_renderer = new Renderer_DX(_hWnd);
		_renderer->Initialise(_width, _height);
	}

	// initialise game
	_game->Initialise(this);
}

void ApplicationWindow_DX::Shutdown()
{
	// shutdown game
	_game->Shutdown();

	if (!_game->GetResetFlag())
	{
		// cleanup renderer
		_renderer->Shutdown();
		delete _renderer; _renderer = 0;
	}
}

// This is the main message handler for the program
LRESULT CALLBACK ApplicationWindow_DX::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}	break;
		case WM_KEYDOWN:
		{
			Game::myGame->GetKeyboard()->UpdateKey(wParam, true);
		}	break;
		case WM_KEYUP:
		{
			Game::myGame->GetKeyboard()->UpdateKey(wParam, false);
		}	break;
		case WM_MOUSEMOVE:
		{
			POINT p;
			if ( GetCursorPos(&p) )
			{
				if ( ScreenToClient(hWnd, &p) )
				{
					Game::myGame->GetMouse()->UpdateMousePosition(p.x, p.y);
				}
			}
		}break;
		case WM_LBUTTONDOWN:
		{
			Game::myGame->GetMouse()->SetLeftMouseButtonDown(true);
		}break;
		case WM_LBUTTONUP:
		{
			Game::myGame->GetMouse()->SetLeftMouseButtonDown(false);
		}
		case WM_RBUTTONDOWN:
		{
			Game::myGame->GetMouse()->SetRightMouseButtonDown(false);
		}break;
		case WM_RBUTTONUP:
		{
			Game::myGame->GetMouse()->SetRightMouseButtonDown(true);
		}break;
	};

	if (Game::myGame->GetTweakBar() != nullptr)
	{
		if (TwEventWin(hWnd, message, wParam, lParam)) // send event message to AntTweakBar
		{
			// event was handled by anttweak
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}