#pragma once
#include <vector>
#include "Game.h"

namespace GameEngine
{
	class Game;
	class GameKeyboard
	{
	public:
		GameKeyboard()
		{
			_keyPress = std::vector<bool>(256);
			_keyHeld = std::vector<bool>(256);
		}
		~GameKeyboard() = default;

	protected:
		std::vector<bool> _keyPress;
		std::vector<bool> _keyHeld;

		// get & set
	public:
		bool GetKeyDown(int key) { return _keyHeld[key]; }
		bool GetKeyPress(int key) { return _keyPress[key]; }

		// function
	public:
		virtual void UpdateKey(int key, bool down);
		virtual void Update();
	};
}