#pragma once
#include "Vector4.h"
#include "Game.h"

namespace GameEngine
{
	class Game;
	class GameMouse
	{
	public:
		GameMouse() = default;
		~GameMouse() = default;

		// data
	protected:
		Vector4 _position;
		Vector4 _oldPosition;
		Vector4 _posChange;

		bool _leftButtonDown = false;
		bool _rightButtonDown = false;

		// get & set
	public:
		Vector4 GetPosition() { return _position; }
		Vector4 GetOldPosition() { return _oldPosition; }
		Vector4 GetPositionChange() { return _posChange; }
		
		bool GetLeftMouseButtonDown() { return _leftButtonDown; }
		void SetLeftMouseButtonDown(bool val) { _leftButtonDown = val; BroadcastMousePressChange(); }
		bool GetRightMouseButtonDown() { return _rightButtonDown; }
		void SetRightMouseButtonDown(bool val) { _rightButtonDown = val; BroadcastMousePressChange(); }

		// function
	public:
		virtual void UpdateMousePosition(int x, int y);
		virtual void BroadcastMousePressChange();
	};
}