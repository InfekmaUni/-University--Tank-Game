#pragma once
#include "Scene.h"
#include <iostream>
#include <string>

#include <DirectXMath.h>
#include "SystemManager.h"

#include "SystemRender.h"
#include "SystemPhysics.h"

#include "RenderedEntity.h"
#include "PlayerCamera.h"

#include "SceneShader.h"

#include "NetworkManager.h"
#include "GameSceneNetworking.h"

#include "PlayerTank.h"
#include "AITank.h"
#include "Barrier.h"
#include "HealthPack.h"

using namespace GameEngine;

class Tank;
class GameSceneNetworking;
class GameScene : public Scene
{
public:
	static GameScene* myGameScene;

public:
	GameScene(int id);
	~GameScene() = default;

	// data
private:
	std::vector<Tank*> _tanks;
	std::vector<Vector4> _spawnPoints;
	PlayerTank* _localPlayer;
	PlayerCamera* _playerCam;
	int _playerCount = 0;
	int _aiCount = 0;
	SceneShader* _sceneShader;
	std::vector<PlayerTank*> _playerTanks;

	std::vector<int> _playerIDs;

	GameSceneNetworking* _gameNetwork;
	bool _authenticated;

	// ui shader

	// getters & setters
public:
	SceneShader* GetSceneShader() { return _sceneShader; }
	std::vector<Tank*>& GetTankList() { return _tanks; }

	// ui shader

	// scene functions
public:
	// called when respective events happen
	void OnInitialise();
	void OnUpdate(float delta);
	void OnRender(Renderer* renderer);
	void OnShutdown();
	void OnMessage(Message* msg);

	void CreatePlayerTank(int playerID, TEAM_ID teamID, Vector4 pos);
	void CreateAITank(TEAM_ID teamID, Vector4 pos);
	void CreateLocalPlayerTank(int playerID, TEAM_ID teamID, Vector4 pos);
};

