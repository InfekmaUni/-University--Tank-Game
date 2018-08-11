#pragma once
#include "Message.h"

namespace GameEngine
{
	class NetworkMessage : public Message
	{
	public:
		NetworkMessage(std::string msg) : Message("NetworkMessage"), _msg(msg)
		{}
		~NetworkMessage() = default;

	private:
		std::string _msg;

	public:
		std::string GetNetworkMessage() { return _msg; }
	};
}