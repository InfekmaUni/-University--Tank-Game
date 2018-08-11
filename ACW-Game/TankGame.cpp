#include "TankGame.h"

using namespace GameEngine;

void TankGame::Initialise(ApplicationWindow* window)
{
	Game::Initialise(window);

	// create default managers
	AddManager(new SceneManager());
	AddManager(new ResourceManager());
	AddManager(new NetworkManager("Network"));

	for (auto const& manager : _managerList)
	{
		manager->Initialise();
	}

	// first scene
	GameEngine::SceneManager* sceneManager = (GameEngine::SceneManager*)GetManager("SceneManager");
	GameScene* gameScene = new GameScene(0);
	sceneManager->AddAndSetScene(gameScene);
}

void TankGame::OnNetwork()
{
	Game::OnNetwork();
}

int TankGame::Run()
{
	Game::Run();

	return 1;
}

void TankGame::OnUpdate()
{
	Game::OnUpdate();
}

void TankGame::OnRender()
{
	Game::OnRender();
}

void TankGame::ListenMessage(Message* msg)
{

	Game::ListenMessage(msg);

}

void TankGame::Shutdown()
{
	Game::Shutdown();
}