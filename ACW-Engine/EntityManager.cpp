#include "EntityManager.h"

using namespace GameEngine;

void EntityManager::Update(float dt)
{
	for (auto const& ent : _entityList)
	{
		if (ent == nullptr)
			continue;

		if (!ent->GetIsAlive())
			continue;

		std::lock_guard<std::mutex> lock(ent->GetMutex());

		if (!ent->GetInit()) 
		{
			ent->OnInitialise();
			ent->SetInit(true);
		}

		ent->OnUpdate(dt);
	}

	for (auto& ent : _entityList)
	{
		if (!ent->GetIsAlive()) // is deleted
		{
			RemoveEntity(ent);
			break;
		}
	}
}

void EntityManager::OnMessage(Message* msg)
{
	for (auto const& ent : _entityList) 
	{
		if (ent == nullptr)
			continue;

		if (!ent->GetIsAlive())
			continue;

		std::lock_guard<std::mutex> lock(ent->GetMutex());

		ent->OnMessage(msg);
	}
}

void EntityManager::Render()
{
	for (auto const& ent : _entityList)
	{
		if (ent == nullptr)
			continue;

		if (!ent->GetIsAlive())
			continue;

		std::lock_guard<std::mutex> lock(ent->GetMutex());

		ent->OnRender();
	}
}

void EntityManager::Shutdown()
{
	for (auto ent : _entityList) {
		std::lock_guard<std::mutex> lock(ent->GetMutex());

		ent->OnShutdown();
		delete ent;
	}
	_entityList.clear();
}

void EntityManager::Initialise()
{
}

Entity* EntityManager::AddEntity(Entity* ent)
{
	_entityList.push_back(ent);
	_entityList.back()->OnInitialise();
	_entityList.back()->SetID(EntitiesCount());

	return _entityList.back();
}

Entity* EntityManager::FindEntity(int entID)
{
	for (auto const& ent : _entityList)
	{
		if (ent->GetID() == entID)
			return ent;
	}
	return nullptr;
}

bool EntityManager::RemoveEntity(int entID)
{
	if (FindEntity(entID) != nullptr)
	{
		for (int i = 0; i < _entityList.size(); i++)
		{
			Entity* ent = _entityList.at(i);

			if (ent->GetID() == entID) 
			{
				delete _entityList.at(i);
				_entityList.at(i) = nullptr;
				_entityList.erase(_entityList.begin() + i);
				return true;
			}
		}
	}
	return false;
}

bool EntityManager::RemoveEntity(Entity* ent)
{
	return RemoveEntity(ent->GetID());
}