#include "NetworkManager.h"

using namespace GameEngine;

NetworkManager::NetworkManager(int port, std::string broadcastIP) : BaseManager("NetworkManager"), _port(port), _broadcastIP(broadcastIP), _listening(true)
{}

NetworkManager::NetworkManager(std::string fileName) : BaseManager("NetworkManager"), _listening(true)
{
	char input;
	std::string line;
	std::ifstream myfile(fileName + ".txt");
	if (myfile.is_open() && myfile.good())
	{
		while (getline(myfile, line))
		{
			int seperatorPos = static_cast<int>(line.find_first_of(':'));
			const std::string identifier = line.substr(0, seperatorPos - 1);
			std::string value = line.substr(seperatorPos + 2, line.length() - seperatorPos + 2);

			if (identifier == "Port")
			{
				 _port = std::stoi(value);
			}
			else if (identifier == "IP")
			{
				_broadcastIP = value;
			}
		}
	}
}

void NetworkManager::SendNetworkMessage(std::string msg)
{
	std::string realMessage = VERIFICATION_CODE + " " +msg;
	std::string encryptedMsg = Encrypt(realMessage, ENCRYPTION_KEY);
	if (sendto(_broadcastSocket, encryptedMsg.c_str(), BUFFER_SIZE, 0, (sockaddr*)&_sendBroadcast, sizeof(_sendBroadcast)) < 0)
	{
		std::cerr << "Failed to send broadcast message " << WSAGetLastError() << std::endl;
	}
}

bool NetworkManager::VerifyNetworkMessage(std::string msg)
{
	std::string code = msg.substr(0, msg.find_first_of(' '));
	if (code.compare(VERIFICATION_CODE) == 0)
	{
		return true;
	}
	return false;
}

std::string NetworkManager::ExtractNetworkMessage(std::string msg)
{
	return msg.substr(msg.find_first_of(' ') +1, msg.length() - msg.find_first_of(' ') + 1);
}

void NetworkManager::ProcessNetworkMessage(std::string msg)
{
	std::cout << "Recieved valid message: " << msg << std::endl;
	NetworkMessage* networkMessage = new NetworkMessage(msg);
	Game::myGame->BroadcastMessage(networkMessage);
}

void NetworkManager::Shutdown()
{
	WSACleanup();
}

void NetworkManager::Initialise()
{
	// Create version identifier
	WORD wVersionRequested = MAKEWORD(2, 0);

	// Startup windows sockets
	WSADATA wsaData;
	if (WSAStartup(wVersionRequested, &wsaData)) {
		std::cerr << "Socket initialisation failed" << std::endl;
	}

	// setup broadcast send and recieve address
	_recieveBroadcast.sin_family = AF_INET;
	_recieveBroadcast.sin_port = htons(_port);	// port 9171
	_recieveBroadcast.sin_addr.S_un.S_addr = htons(INADDR_ANY);
	//inet_pton(AF_INET, "127.0.0.1", &recieveBroadcast.sin_addr.S_un.S_addr);

	_sendBroadcast.sin_family = AF_INET;
	_sendBroadcast.sin_port = htons(_port);	// port 9171
	inet_pton(AF_INET, _broadcastIP.c_str(), &_sendBroadcast.sin_addr.S_un.S_addr);

	// broadcast socket
	_broadcastSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	BOOL enabled = true;

	// set socket to be re-usable by multiple peers on same machine
	if (setsockopt(_broadcastSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&enabled, sizeof(BOOL)) < 0)
	{
		std::cerr << "failed to setup re-useable address" << std::endl;
	}

	// set socket to be type broadcast
	if (setsockopt(_broadcastSocket, SOL_SOCKET, SO_BROADCAST, (char*)&enabled, sizeof(BOOL)) < 0)
	{
		std::cerr << "Failed to set broadcast socket operation " << WSAGetLastError() << std::endl;
	}

	// create broadcast socket
	if (_broadcastSocket == SOCKET_ERROR) {
		std::cerr << "Failed to create broadcast socket " << WSAGetLastError() << std::endl;
	}
	else if (bind(_broadcastSocket, (sockaddr *)&_recieveBroadcast, sizeof(_recieveBroadcast)) == SOCKET_ERROR) {
		std::cerr << "Bind failed with " << WSAGetLastError() << std::endl;
	}
}

void NetworkManager::OnNetwork()
{
	if (!_listening)
		return;

	bool first = true;
	char recieved[BUFFER_SIZE];
	while (recieved != "" || first) // read till there's nothing left from recv
	{
		first = false;

		if (recv(_broadcastSocket, recieved, BUFFER_SIZE, 0) < 0)
		{
			std::cerr << "Failed to recieve broadcast message " << WSAGetLastError() << std::endl;
		}

		if (recieved != "")
		{
			std::string decryptedMsg = Encrypt(recieved, ENCRYPTION_KEY);

			if (VerifyNetworkMessage(decryptedMsg))
			{
				std::string realMessage = ExtractNetworkMessage(decryptedMsg);
				ProcessNetworkMessage(realMessage);
			}
		}
		else
		{
			std::cout << "Did not recieve any messages" << std::endl;
		}
	}
}

std::string NetworkManager::Encrypt(std::string msg, std::string key)
{
	// Make sure the key is at least as long as the message
	std::string tmp(key);
	while (key.size() < msg.size())
		key += tmp;

	// And now for the encryption part
	for (std::string::size_type i = 0; i < msg.size(); ++i)
		msg[i] ^= key[i];
	return msg;
}

std::string NetworkManager::Decrypt(std::string msg, std::string key)
{
	return Encrypt(msg, key); // lol
}