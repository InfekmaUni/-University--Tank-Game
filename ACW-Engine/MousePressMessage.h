#pragma once
#include "Message.h"
#include "GameMouse.h"

namespace GameEngine
{
	class MousePressMessage : public Message
	{
	public:
		MousePressMessage(GameMouse* mouse) : Message("MousePress"), _mouse(mouse)
		{}
		~MousePressMessage() = default;

		// data
	private:
		GameMouse* _mouse;

		// get
	public:
		bool IsLeftMouseDown() { return _mouse->GetLeftMouseButtonDown(); }
		bool IsLeftMouseUp() { return !_mouse->GetLeftMouseButtonDown(); }

		bool IsRightMouseDown() { return _mouse->GetRightMouseButtonDown(); }
		bool IsRightMouseUp() { return !_mouse->GetRightMouseButtonDown(); }
	};
}