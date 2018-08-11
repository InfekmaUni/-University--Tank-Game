#include "GameMouse.h"

#include "MouseMoveMessage.h"
#include "MousePressMessage.h"

using namespace GameEngine;

void GameMouse::UpdateMousePosition(int x, int y)
{
	_oldPosition = _position;
	_posChange = Vector4(_position.x() - _oldPosition.x(), _position.y() - _oldPosition.y()); // mouse change since last frmae
	_position = Vector4(x, y);

	// broadcast mouse moved
	MouseMoveMessage* msg = new MouseMoveMessage(this);
	Game::myGame->BroadcastMessage(msg);
}

void GameMouse::BroadcastMousePressChange()
{
	// broadcast mouse press
	MousePressMessage* msg = new MousePressMessage(this);
	Game::myGame->BroadcastMessage(msg);
}