#pragma once
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <string>
#include <iostream>
#include <Ws2tcpip.h>
#include <stdio.h>

// available ports
// 9171-9176

static const int DEFAULT_PORT = 9171;
static const int BROADCAST_PORT = 9171;
static const WORD DEFAULT_VERSION = MAKEWORD(2, 0);
static const std::string DEFAULT_ADDRESS = "127.0.0.1"; // peer ip
static const size_t BUFFER_SIZE = 1;
class UdpNetworkClient
{
public:
	UdpNetworkClient(int port = DEFAULT_PORT, std::string address = DEFAULT_ADDRESS, bool broadcast = false) : _version(DEFAULT_VERSION), _clientAddress(address), _clientPort(port), _broadcasting(broadcast)
	{}
	~UdpNetworkClient() = default;
private:
	WORD _version;
	WSADATA _data;
	SOCKET _socket;


	sockaddr_in _client;
	int _clientPort = 9171;
	std::string _clientAddress;

	sockaddr_in _broadCast;
	int _broadCastPort = 9171;
	std::string _broadCastIP = DEFAULT_ADDRESS;


	sockaddr_in _listener;


	sockaddr_in _recievedFrom;

	bool _connected = false;
	bool _broadcasting = false;

	// get & set
public:
	void SetBroadCast(bool val) { _broadcasting = val; }

	// function
public:
	void TerminateConnection();
	void CreateConnection();
	void StartConnection();

	char* RecieveFromPeer();
	char* RecieveFromBroadcast();

	void ConnectToPeer();

	void SendPeerMessage(std::string message);
	void SendBroadcastMessage(std::string message);
};