#include "GameKeyboard.h"

using namespace GameEngine;

void GameKeyboard::UpdateKey(int key, bool down)
{

	if(_keyPress[key] == false && down == true && _keyHeld[key] == false)// key was not previously down
	{
		_keyPress[key] = true;
	}

	if (down == false) // up - reset
	{
		_keyPress[key] = false;
		_keyHeld[key] = false;
	}

	KeyPressMessage* msg = new KeyPressMessage(key, _keyHeld[key], _keyPress[key]);
	Game::myGame->BroadcastMessage(msg);
}

void GameKeyboard::Update()
{
	for (int i = 0; i < _keyPress.size(); i++)
	{
		if (_keyPress.at(i) == true)
		{
			_keyPress.at(i) = false;
			_keyHeld.at(i) = true;
		}
	}
}