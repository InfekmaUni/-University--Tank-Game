#pragma once
#include "Message.h"

namespace GameEngine
{
	class KeyPressMessage : public Message
	{
	public:
		KeyPressMessage(int key, bool down, bool press) : Message("KeyPress"), _key(key), _down(down), _press(press)
		{}
		~KeyPressMessage() = default;

		// data
	private:
		int _key;
		bool _down;
		bool _press;

		// getters & setters
	public:
		int GetKey() { return _key; }
		bool GetDownState() { return _down; }
		bool GetKeyPress() { return _press; }

		// functions
	public:

	};
}