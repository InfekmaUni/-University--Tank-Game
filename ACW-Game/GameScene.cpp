#include "GameScene.h"

GameScene* GameScene::myGameScene = NULL;

GameScene::GameScene(int sceneID) : Scene(sceneID)
{
	myGameScene = this;
}

// called when respective events happen
void GameScene::OnInitialise()
{
	EntityManager* _entManager;
	AddManager(_entManager = new EntityManager());
	SystemManager* _sysManager;
	AddManager(_sysManager = new SystemManager());

	SystemPhysics* physicsSystem;
	_sysManager->AddUpdateSystem(physicsSystem = new SystemPhysics());
	physicsSystem->Initialise();

	SystemRender* renderSystem;
	_sysManager->AddRenderableSystem(renderSystem = new SystemRender());
	renderSystem->Initialise();

	_gameNetwork = new GameSceneNetworking(this);
	_sceneShader = new SceneShader("Shaders/Default_VS.hlsl", "Shaders/Default_PS.hlsl");

	std::cout << "GameScene Initilize" << std::endl;

	RenderedEntity* sky = new RenderedEntity("Hemisphere", "sky");
	_entManager->AddEntity(sky);
	sky->SetPosition(Vector4(-25, -50, 0));
	sky->SetEntityName("Sky");
	sky->SetScale(Vector4(1000, 1000, 1000));

	RenderedEntity* floor = new RenderedEntity("Desert", "Desert");
	_entManager->AddEntity(floor);
	floor->SetPosition(Vector4(0, -5, 0));
	floor->SetScale(Vector4(50, 50, 50));
	floor->SetEntityName("Floor");
	new ComponentCollision(floor, Vector4(450,1,450), true);

	// obstacles
	Barrier* upWall = new Barrier(Vector4(0, -5, -100), Vector4(25, 15, 5));
	_entManager->AddEntity(upWall);

	Barrier* downWall = new Barrier(Vector4(0, -5, 100), Vector4(25, 15, 5));
	_entManager->AddEntity(downWall);

	Barrier* rightWall = new Barrier(Vector4(100, -5, 0), Vector4(5, 15, 25));
	_entManager->AddEntity(rightWall);

	Barrier* leftWall = new Barrier(Vector4(-100, -5, 0), Vector4(5, 15, 25));
	_entManager->AddEntity(leftWall);

	Barrier* leftLongWall = new Barrier(Vector4(300, -5, 0), Vector4(75, 15, 5));
	_entManager->AddEntity(leftLongWall);

	Barrier* rightLongWall = new Barrier(Vector4(-300, -5, 0), Vector4(75, 15, 5));
	_entManager->AddEntity(rightLongWall);

	// arena edges
	Barrier* borderUpWall = new Barrier(Vector4(0, -5, -450), Vector4(300, 15, 5));
	_entManager->AddEntity(borderUpWall);

	Barrier* borderDownWall = new Barrier(Vector4(0, -5, 450), Vector4(300, 15, 5));
	_entManager->AddEntity(borderDownWall);

	Barrier* borderRightWall = new Barrier(Vector4(450, -5, 0), Vector4(5, 15, 300));
	_entManager->AddEntity(borderRightWall);

	Barrier* borderLeftWall = new Barrier(Vector4(-450, -5, 0), Vector4(5, 15, 300));
	_entManager->AddEntity(borderLeftWall);

	//HealthPack* pack1 = new HealthPack(Vector4(50, -5, 50));
	//_entManager->AddEntity(pack1);

	//HealthPack* pack2 = new HealthPack(Vector4(-50, -5, 50));
	//_entManager->AddEntity(pack2);

	//HealthPack* pack3 = new HealthPack(Vector4(50, -5, -50));
	//_entManager->AddEntity(pack3);

	//HealthPack* pack4 = new HealthPack(Vector4(-50, -5, -50));
	//_entManager->AddEntity(pack4);

	//CreatePlayerTank(Vector4(), Vector4(), TANK_ID::PLAYER, TEAM_ID::TEAM_2);
	_playerCam = new PlayerCamera();
	_entManager->AddEntity(_playerCam);
	_playerCam->SetPlayerTank(_localPlayer);
	_playerCount++;

	// add game scene
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "Player Count", TW_TYPE_INT32, &_playerCount, " readonly='true' group='Game Info' ");
	TwAddVarRW(Game::myGame->GetTweakBar()->GetTweakBarByID(0), "AI Count", TW_TYPE_INT32, &_aiCount, " readonly='true' group='Game Info' ");

	NetworkManager* manager = (NetworkManager*)Game::myGame->GetManager("NetworkManager");
//	manager->SendNetworkMessage("IDRequest");

//	CreateLocalPlayerTank(0, TEAM_ID::TEAM_1, Vector4(0,0,0));
	CreateAITank(TEAM_ID::TEAM_2, Vector4(50, 0, 50));
	CreateAITank(TEAM_ID::TEAM_2, Vector4(-50, 0, -50));
	CreateAITank(TEAM_ID::TEAM_1, Vector4(70, 0, -50));
	Scene::OnInitialise();
}

void GameScene::CreateLocalPlayerTank(int playerID, TEAM_ID teamID, Vector4 pos)
{
	EntityManager* _entManager = (EntityManager*)GetManagerByName("EntityManager");
	_localPlayer = new PlayerTank(playerID, teamID, pos);
	_localPlayer->SetLocalPlayer(true);
	_entManager->AddEntity(_localPlayer);
	_tanks.push_back(_localPlayer);
	_playerTanks.push_back(_localPlayer);
	_playerCam->SetPlayerTank(_localPlayer);
}

void GameScene::CreatePlayerTank(int playerID, TEAM_ID teamID, Vector4 pos)
{
	EntityManager* _entManager = (EntityManager*)GetManagerByName("EntityManager");
	PlayerTank* newPlayer = new PlayerTank(playerID, teamID, pos);
	_entManager->AddEntity(newPlayer);
	_tanks.push_back(newPlayer);
	_playerTanks.push_back(newPlayer);
}

void GameScene::CreateAITank(TEAM_ID teamID, Vector4 pos)
{
	EntityManager* _entManager = (EntityManager*)GetManagerByName("EntityManager");
	AITank* newTank = new AITank(teamID, pos);
	_entManager->AddEntity(newTank);
	_tanks.push_back(newTank);
}

void GameScene::OnUpdate(float delta)
{
	_gameNetwork->OnUpdate(delta);

	Scene::OnUpdate(delta);
}

void GameScene::OnMessage(Message* msg)
{
	int x = 0;

	if (msg->GetType() == "KeyPress")
	{
		KeyPressMessage* keyMsg = (KeyPressMessage*)msg;
		int key = keyMsg->GetKey();
		bool down = keyMsg->GetKeyPress();

		if (key == 80 && down) // p
		{
			NetworkManager* manager = (NetworkManager*)Game::myGame->GetManager("NetworkManager");
			manager->SendNetworkMessage("Pause");
		}
	}
	else if (msg->GetType() == "NetworkMessage")
	{
		NetworkMessage* networkMessage = (NetworkMessage*)msg;
		std::string newMsg = networkMessage->GetNetworkMessage();

		std::cout << "Recieved network message: " << newMsg << std::endl;
		_gameNetwork->OnMessage(networkMessage);
	}

	Scene::OnMessage(msg);
}

void GameScene::OnRender(Renderer* renderer)
{
	//std::cout << "GameScene Render" << std::endl;
	Scene::OnRender(renderer);
}

void GameScene::OnShutdown()
{
	//std::cout << "GameScene Shutdown" << std::endl;

	Scene::OnShutdown();
}
