#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <fstream>

#include <string>
#include <WS2tcpip.h>
#include <WinSock2.h>

#include "Game.h"

#include "BaseManager.h"

#include "NetworkMessage.h"

const int DEFAULT_PORT = 9171;
const std::string DEFAULT_IP = "150.237.93.255";
const int SOCK_ADDR_LENGTH = sizeof(sockaddr_in);

// http://www.unit-conversion.info/texttools/random-string-generator/
static const std::string ENCRYPTION_KEY = "JUvGNcjPGemxBfHXjpOglyqRKMKvN86mVhbW5tEBw3zkDbvfP83zg9oUf9acTJBF6mLiZ1ReLfuFXrkEFZyC4X7KOGcwr6J3J25gAmQxK4Cmcju2WiYlttYVWsRG5afCVgiSduiEhcv9C8Z4HJDRXs2Dc9Xq6JzN1wf44UbJJ2BnSP48HDYZCjLsCqI7VVGMPwhrUPEysJtmqjSgxMQYNyUdjjhVjvMGI2juvT7RluJzDMGA2e4YeROBPKubgSoFCzR2DKzPV135Qp54e4nE7bxog5BeFNEfE1VuRMi5oDtQMYrDXV8N9sAcEKEpVlZp4LjqScc2OjfCr8ZndBlvlU2pbJJOUfpC8Xx0XseJrlYDfcXFagXb2WGYtAOI75FWTbLG73gjKTzBJExdhC5Hg8luC7ES5i1zmGeH5XRKC7LYbK0NguskuLxlNQ69kjLUKbIJ4XogIIzLPa8KtA1mBKcJpxVe8VoQ6rX0HmX3Zv0SjL7Up9HjBi7FucTGmUyq";
static const std::string VERIFICATION_CODE = "WILLSMITH";

const int BUFFER_SIZE = 512;
const int RECONNECTION_ATTEMPT_THRESHOLD = 10;

namespace GameEngine
{
	class NetworkManager : public BaseManager
	{
	public:
		NetworkManager(int port = DEFAULT_PORT, std::string broadcastIP = DEFAULT_IP);
		NetworkManager(std::string fileName);
		~NetworkManager() = default;

		// data
	private:
		SOCKET _broadcastSocket;
		sockaddr_in _recieveBroadcast;
		sockaddr_in _sendBroadcast;
		int _port;
		std::string _broadcastIP;
		bool _listening;

		// get & set
	public:
		int GetPort() { return _port; }
		std::string GetBroadcastIP() { return _broadcastIP; }
		bool SetListen(bool val) { _listening = val; }

		// functions
	public:
		virtual void Update(float dt) {}
		virtual void OnNetwork();
		virtual void Render(Renderer* renderer) {}
		virtual void Shutdown();
		virtual void Initialise();
		virtual void OnMessage(Message* msg) {}

		void SendNetworkMessage(std::string msg);

		// private functions
	private:
		bool VerifyNetworkMessage(std::string msg);
		std::string ExtractNetworkMessage(std::string msg);
		void ProcessNetworkMessage(std::string msg);

		// source: http://www.cplusplus.com/forum/windows/128374/
		std::string Encrypt(std::string msg, std::string key);
		std::string Decrypt(std::string msg, std::string key);
	};
}