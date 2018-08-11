#include "Scene.h"

using namespace GameEngine;

Scene::Scene(int id) : _sceneID(id)
{
	_gameInstance = Game::myGame;
}

void Scene::OnInitialise()
{
	for (auto const& manager : _managers)
	{
		manager->Initialise();
	}
}

void Scene::OnShutdown()
{
	for (auto const& manager : _managers)
	{
		manager->Shutdown();
	}
}

void Scene::Quit()
{
	_gameInstance->SetQuitFlag();
}

void Scene::OnUpdate(float dt)
{
	for (auto const& manager : _managers)
	{
		manager->Update(dt);
	}
}

void Scene::OnRender(Renderer* renderer)
{
	for (auto const& manager : _managers)
	{
		manager->Render(renderer);
	}
}

void Scene::OnMessage(Message* msg)
{
	for (auto const& manager : _managers)
	{
		manager->OnMessage(msg);
	}
}