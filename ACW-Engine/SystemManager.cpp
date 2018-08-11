#include "SystemManager.h"

using namespace GameEngine;

void SystemManager::Initialise()
{
}

void SystemManager::Shutdown()
{
	for (auto const& system : _updateSystemList)
	{
		system->Shutdown();
	}

	for (auto const& system : _renderSystemList)
	{
		system->Shutdown();
	}
}

void SystemManager::OnMessage(Message* msg)
{
	for (auto const& system : _updateSystemList)
	{
		system->OnMessage(msg);
	}

	for (auto const& system : _renderSystemList)
	{
		system->OnMessage(msg);
	}
}

void SystemManager::Update(float dt)
{
	EntityManager* entManager = (EntityManager*)SceneManager::myScene->GetManagerByName("EntityManager");
	if (entManager == nullptr)
		return;

	std::vector<Entity*> entList = entManager->GetEntityList();
	if (entList.size() <= 0)
		return;

	//while (entManager->GetEntityRenderList().size() != 0)
	//{
	//	// wait for render thread to clear the render entity list
	//}
	//entManager->RestartEntityUpdateList(); // unlocks render thread

	for (auto const& ent : entList)
	{
		if (ent == nullptr || !ent->GetIsAlive() || ent->GetFakeDeath())
			continue;

		ent->LockEntity();

		for (auto const& system : _updateSystemList)
		{
			system->Update(dt, ent);

		}

		if (ent != nullptr)
			ent->UnlockEntity();
		//entManager->AddEntityToRenderList(ent); // adds ent to list for the render stage
		//entManager->IncrementEntUpdateFrameCounter(); // counts how many ents have been updated
	}

	//while (!entManager->DoneRenderingEnts())
	//{
	//	// wait for render thread to catch up
	//}
}

void SystemManager::Render(Renderer* renderer)
{
	EntityManager* entManager = (EntityManager*)SceneManager::myScene->GetManagerByName("EntityManager");
	if (entManager == nullptr)
		return;

	std::vector<Entity*> entListcheck = entManager->GetEntityList();
	if (entListcheck.size() <= 0)
		return;

	renderer->ClearScreen();

	//while (!entManager->DoneUpdatingAndRendering()) // while not done rendering all
	//{
	//	std::vector<Entity*> entList = entManager->GetEntityRenderList();
	//	if (entList.size() <= 0)
	//		continue;

		for (auto const& ent : entListcheck)
		{
			if (ent == nullptr || !ent->GetIsAlive() || ent->GetFakeDeath())
				continue;

			ent->LockEntity();

			for (auto const& system : _renderSystemList)
			{
				system->Render(renderer, ent);
			}

			if(ent != nullptr)
				ent->UnlockEntity();
			//entManager->RemoveEntityFromRenderList(ent);
			//entManager->IncrementEntRenderFrameCounter();
		}
	//}

	Game::myGame->GetTweakBar()->Draw();
	//entManager->ResetEntCounters();
	renderer->SwapBuffers();
}