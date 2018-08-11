#pragma once
#include "Message.h"
#include "GameMouse.h"

namespace GameEngine
{
	class MouseMoveMessage : public Message
	{
	public:
		MouseMoveMessage(GameMouse* mouse) : Message("MouseMove"), _mouse(mouse)
		{}
		~MouseMoveMessage() = default;

		// data
	private:
		GameMouse* _mouse;

		// get
	public:
		GameMouse* GetMouse() { return _mouse; }
		Vector4 GetPosition() { return _mouse->GetPosition(); }
		Vector4 GetOldPosition() { return _mouse->GetOldPosition(); }
		Vector4 GetPositionChange() { return _mouse->GetPositionChange(); }
	};
}