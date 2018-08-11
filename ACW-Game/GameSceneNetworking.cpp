#include "GameSceneNetworking.h"

using namespace GameEngine;

GameSceneNetworking::GameSceneNetworking(GameScene* scene) : _gameScene(scene), _authenticating(true), _myID(0)
{
	_authTimer = new ACWTimer(AUTHENTICATION_PEROID);
	_authTimer->Start();
}

void GameSceneNetworking::OnMessage(NetworkMessage* msg)
{
	if(_networkManager == nullptr)
	_networkManager = (NetworkManager*)Game::myGame->GetManager("NetworkManager");

	std::string networkMessage = msg->GetNetworkMessage();

	std::string command = networkMessage.substr(0, networkMessage.find_first_of(' '));
	// global commands (no player id required)
	if (command == "Pause")
	{
		Game::myGame->TogglePause();
	}
	else if (command == "IDRequest" && !_authenticating)
	{
		_networkManager->SendNetworkMessage("IDResponse "+_myID);
	}
	else if (command == "IDResponse" && !_authenticating)
	{
		std::string actualmsg = networkMessage.substr(networkMessage.find_first_of(' ') + 1, networkMessage.length() - networkMessage.find_first_of(' ') + 1);
		int playerID = std::stoi(actualmsg);
		CheckAndAddNewPlayer(playerID);
	}

	// commands involving player ID
	if (command == "TeamIDRequest")
	{
		_networkManager->SendNetworkMessage("TeamIDResponse ");
	}
	//else if (command == "TeamIDResponse")
	//{
	//	manager->SendNetworkMessage("TeamIDResponse ");
	//}

}

void GameSceneNetworking::OnUpdate(float delta)
{
	if (_networkManager == nullptr)
	{
		_networkManager = (NetworkManager*)Game::myGame->GetManager("NetworkManager");
	}

	if (_authTimer->IsDone() && _authenticating)
	{
		_authenticating = false;
		DetermineSelfPlayerID();
	}
}

void GameSceneNetworking::DetermineSelfPlayerID()
{
	bool id[4] = { FALSE };
	for (auto& pID : _playerIDs)
	{
		id[pID] = true;
	}

	for (auto& pID : id)
	{
		if (!pID) {
			_myID = pID;
			std::cout << "My Player ID Is: " << _myID << std::endl;
			break;
		}
	}
	_gameScene->CreateLocalPlayerTank(_myID, TEAM_ID::TEAM_1, Vector4(0,0,0));
}

void GameSceneNetworking::SendNetworkMessage(std::string msg)
{
	_networkManager->SendNetworkMessage(msg);
}

bool GameSceneNetworking::CheckAndAddNewPlayer(int id)
{
	for (auto& pID : _playerIDs)
	{
		if (pID == id)
		{
			return false;
		}
	}
	_playerIDs.push_back(id);
	return true;
}