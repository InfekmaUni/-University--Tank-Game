#include "MainMenuScene.h"

using namespace GameEngine;

MainMenuScene::MainMenuScene(int sceneID) : Scene(sceneID)
{}

void MainMenuScene::OnInitialise()
{
	EntityManager* _entManager;
	AddManager(_entManager = new EntityManager());
	SystemManager* _sysManager;
	AddManager(_sysManager = new SystemManager());

	SystemRender* renderSystem;
	_sysManager->AddRenderableSystem(renderSystem = new SystemRender());
	renderSystem->Initialise();

	Scene::OnInitialise();
}

void MainMenuScene::OnUpdate(float delta)
{
	Scene::OnUpdate(delta);
}

void MainMenuScene::OnRender(GameEngine::Renderer* renderer)
{
	Scene::OnRender(renderer);
}

void MainMenuScene::OnShutdown()
{
	Scene::OnShutdown();
}

void MainMenuScene::OnMessage(GameEngine::Message* msg)
{
	Scene::OnMessage(msg);
}