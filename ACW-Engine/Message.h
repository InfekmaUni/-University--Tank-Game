#pragma once
#include <string>

namespace GameEngine
{
	class Message
	{
	public:
		Message(std::string type) : _type(type)
		{}
		~Message() = default;

		// data
	protected:
		std::string _type;

		// getters & setters
	public:
		std::string GetType() { return _type; }

		// functions
	public:

	};
}