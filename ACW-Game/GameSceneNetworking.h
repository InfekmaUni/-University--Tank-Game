#pragma once
#include "GameScene.h"
#include "Message.h"
#include "NetworkManager.h"
#include "ACWTimer.h"

using namespace GameEngine;

const int AUTHENTICATION_PEROID = 2;

class GameScene;
class GameSceneNetworking
{
public:
	GameSceneNetworking(GameScene* scene);
	~GameSceneNetworking() = default;

private:
	GameScene* _gameScene;
	NetworkManager* _networkManager;
	int _myID;
	std::vector<int> _playerIDs;
	bool _authenticating;

	ACWTimer* _authTimer;
public:
	int GetMyID() { return _myID; }

private:
	bool CheckAndAddNewPlayer(int ID);
	void DetermineSelfPlayerID();
	void SendNetworkMessage(std::string msg);

public:
	void OnMessage(NetworkMessage* msg);
	void OnUpdate(float delta);
};

