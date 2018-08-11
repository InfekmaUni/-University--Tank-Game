#include "stdafx.h"
#include "UdpNetworkClient.h"

void UdpNetworkClient::CreateConnection()
{
	//// Startup windows sockets
	if (WSAStartup(_version, &_data) != 0)
	{
		std::cout << "Failed to setup winsock 2" << std::endl;
		return;
	}

	//// Create socket
	//if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	//{
	//	std::cout << "Failed to create client socket, exited with error: " << WSAGetLastError() << std::endl;
	//}

	//// set socket to be broadcasting
	//if (setsockopt(_socket, SOL_SOCKET, SO_BROADCAST, (char*)&_broadcasting, sizeof(BOOL)) < 0)
	//{
	//	std::cout << "Error setting up a UDP broadcast" << std::endl;
	//}

	//// Bind broadcast and use this as the channel to send messages to
	//_broadCast.sin_family = AF_INET;
	//_broadCast.sin_port = htons(_broadCastPort);
	//inet_pton(AF_INET, _broadCastIP.c_str(), &_broadCast.sin_addr); // bind specific address

	//// create reciever which is used to populate information when recieving
	//_recievedFrom.sin_family = AF_INET;
	//_recievedFrom.sin_port = htons(_broadCastPort);
	//inet_pton(AF_INET, _broadCastIP.c_str(), &_recievedFrom.sin_addr); // bind specific address

	//// setup own connection and bind socket to our information
	//_client.sin_family = AF_INET;
	//_client.sin_port = htons(_clientPort);
	//_client.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//if (bind(_socket, (sockaddr *)&_client, sizeof(_client)) == SOCKET_ERROR)
	//{
	//	std::cout << "Failed to bind socket, exited with error: " << WSAGetLastError() << std::endl;
	//}

	if ((_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
	{
		std::cout << "Failed to create client socket, exited with error: " << WSAGetLastError() << std::endl;
	}

	int enable = 1;
	if ( setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&enable, sizeof(int)) < 0)
	{
		std::cout << "Error setting re-usable address on socket operation" << std::endl;
	}

	_listener.sin_family = AF_INET;
	_listener.sin_port = htons(_broadCastPort);
	_listener.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET, INADDR_ANY, &_listener.sin_addr.S_un.S_addr);

	// allows socket to listen to any ip on the broadcast port
	// does not block, accept() blocks.
	//if (bind(_socket, (sockaddr*)&_listener, sizeof(_listener)))
	//{
	//	std::cout << "Failed to bind socket, exited with error: " << WSAGetLastError() << std::endl;
	//}
	//listen(_socket, SOMAXCONN);
}

//https://stackoverflow.com/questions/2843277/c-winsock-p2p
void UdpNetworkClient::StartConnection()
{
	if (_socket == INVALID_SOCKET) {
		std::cout << "Invalid Socket, Unable to start connection" << std::endl;
		return;
	}

	_connected = true;
	while (_connected)
	{
		char message[BUFFER_SIZE];
		std::cin >> message;

		char* recievedMSG;


		sockaddr_in peer;
		peer.sin_family = AF_INET;
		peer.sin_port = htons(9171); // port 9171
		peer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
		// Create listening socket
		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		int enable = 1;
		if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&enable, sizeof(int)) < 0)
		{
			std::cout << "Error setting re-usable address on socket operation" << std::endl;
		}

		if (s == INVALID_SOCKET) {
			std::cout << "Error socket" << std::endl;
		}
		else if (bind(s, (sockaddr *)&peer, sizeof(peer)) == SOCKET_ERROR) {
			std::cout << "Error Binding "  << WSAGetLastError() << std::endl;
		}
		else if (listen(s, 5) == SOCKET_ERROR) {
			std::cout << "Error listening" << std::endl;
		}
		else {
			// Create transfer socket
			char buffer;
			SOCKET s1 = accept(s, NULL, NULL);
			if (s1 == INVALID_SOCKET) {
				std::cout << "Error transfer socket" << std::endl;
			}
			else if (recv(s1, &buffer, 1, 0) == SOCKET_ERROR) {
				std::cout << "Error recieving" << std::endl;
			}
			else {
				std::cout << "Message= " << buffer << std::endl;
				if (send(s1, "2", 1, 0) == SOCKET_ERROR) {
					std::cout << "Error sending" << std::endl;
				}
			}
		}

		//// recieving
		//fd_set mySet;
		//FD_ZERO(&mySet);
		//FD_SET(_socket, &mySet);
		//
		//sockaddr_in newPeer;
		//SOCKET newPeerSocket;
		//timeval zero = { 0, 0 };
		//int sel = select(0, &mySet, NULL, NULL, &zero);
		//if ( FD_ISSET(newPeerSocket, &mySet) )
		//{
		//	// new connection
		//	int size = sizeof(newPeer);
		//	newPeerSocket = accept(_socket, (SOCKADDR*)&newPeer, &size);
		//	std::cout << "new peer" << std::endl;

		//	int peerSize = sizeof(newPeer);
		//	if (recvfrom(newPeerSocket, message, BUFFER_SIZE, 0, (sockaddr*) &newPeer, &peerSize) == SOCKET_ERROR) {
		//		// error recieve connection
		//		std::cout << "Failed to recieved broadcast message, exited with error: " << WSAGetLastError() << std::endl;
		//	}

		//	std::cout << "recieved: " << message << std::endl;
		//}


		//// sending
		//fd_set senderSet;
		//FD_ZERO(&senderSet);
		//FD_SET(newPeerSocket, &senderSet);

		//timeval zero1 = { 0,0 };
		//int sel2 = select(0, NULL, &senderSet, NULL, &zero);
		//if ( FD_ISSET(newPeerSocket, &senderSet) )
		//{
		//	if (sendto(newPeerSocket, message, BUFFER_SIZE, 0, (sockaddr*) &newPeer, sizeof(newPeer)) == SOCKET_ERROR)
		//	{
		//		// error sending
		//		std::cout << "Failed to send Message to broadcast, exited with error: " << WSAGetLastError() << std::endl;
		//	}
		//}

		//std::cout << "send message: " << message << std::endl;

		//if (_broadcasting) // broadcast
		//{
		//	SendBroadcastMessage(message);

		//	recievedMSG = RecieveFromBroadcast();
		//	if (recievedMSG == nullptr)
		//	{
		//		continue; // no message
		//	}
		//}
		//else // specific connection
		//{
		//	ConnectToPeer();

		//	SendPeerMessage(message);

		//	recievedMSG = RecieveFromPeer();
		//	if (recievedMSG == nullptr)
		//	{
		//		continue; // no message
		//	}
		//}

		//std::cout << "Recieved Message: " << std::endl;
		//std::cout << recievedMSG << std::endl;
	}
}

// specific connection
void UdpNetworkClient::ConnectToPeer()
{
	//if (connect(_socket, (sockaddr *)&_peer, sizeof(_peer)) == SOCKET_ERROR) 
	//{
	//	// connect to peer failed
	//	std::cout << "Failed to connect to peer, exited with error: " << WSAGetLastError() << std::endl;
	//}
}

// broadcast
char* UdpNetworkClient::RecieveFromBroadcast()
{
	char buffer[BUFFER_SIZE];

	//int peerSize = sizeof(_broadCast);
	//if (recvfrom(_socket, buffer, BUFFER_SIZE, 0, (sockaddr*) &_broadCast, &peerSize) == SOCKET_ERROR) {
	//	// error recieve connection
	//	std::cout << "Failed to recieved broadcast message, exited with error: " << WSAGetLastError() << std::endl;
	//}


	return buffer;
}

// broadcast
void UdpNetworkClient::SendBroadcastMessage(std::string message)
{
	//send the message
	//if (sendto(_socket, message.c_str(), BUFFER_SIZE, 0, (sockaddr*) &_broadCast, sizeof(_broadCast)) == SOCKET_ERROR)
	//{
	//	// error sending
	//	std::cout << "Failed to send Message to broadcast, exited with error: " << WSAGetLastError() << std::endl;
	//}
}

// specific connection
char* UdpNetworkClient::RecieveFromPeer()
{
	char buffer[BUFFER_SIZE];

	if (recv(_socket, buffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
		// error recieve connection
		std::cout << "Failed to recieved client message, exited with error: " << WSAGetLastError() << std::endl;
	}

	return buffer;
}

// specific connection
void UdpNetworkClient::SendPeerMessage(std::string message)
{
	char mesg = 'a';
	if (send(_socket, &mesg, BUFFER_SIZE, 0) == SOCKET_ERROR)
	{
		// error sending
		std::cout << "Failed to send Message to broadcast, exited with error: " << WSAGetLastError() << std::endl;
	}
}

void UdpNetworkClient::TerminateConnection()
{
	_connected = false;


	// Cleanup windows sockets
	closesocket(_socket);
	WSACleanup();
	_socket = INVALID_SOCKET;
}