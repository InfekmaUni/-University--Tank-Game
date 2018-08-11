#include "Entity.h"

using namespace GameEngine;

Entity::Entity()
{
	//EntityManager* entManager = (EntityManager*)Game::myGame->GetManager("EntityManager");
	//_entityID = entManager->EntitiesCount();
	//entManager->AddEntity(this);
}

Entity::Entity(bool add)
{
	if (add == false)
	{
		// for placeholders
	}
	else {
		//EntityManager* entManager = (EntityManager*)Game::myGame->GetManager("EntityManager");
		//_entityID = entManager->EntitiesCount();
		//entManager->AddEntity(this);
	}
}

void Entity::OnUpdate(float dt)
{}

void Entity::OnShutdown()
{}

void Entity::OnMessage(Message* msg)
{
	for (auto const& msgMap : _messageListener)	// check listeners to see if we have a listener for the message
	{
		if (msgMap.first == msg->GetType())		// check if we are listening for this msg
		{
			for (auto const& component : msgMap.second) // components listening to this msg
			{
				component->OnMessage(msg); // send message
			}
			break; // we processed the message, no reason to check further
		}
	}
}

void Entity::AddListener(std::string msg, Component* component)
{
	if (_messageListener.find(msg) != _messageListener.end()) // find listener
	{
		_messageListener[msg].push_back(component); // add to component to list
		return; // dont have to go any further
	}

	// there doesn't exist a listener - create one and add component
	_messageListener[msg] = std::vector<Component*>();
	_messageListener[msg].push_back(component); // add to list
}

void Entity::RemoveMessageListener(std::string msg, Component* component)
{
	if (_messageListener.find(msg) != _messageListener.end()) // find listener
	{
		for(int i = 0; i < _messageListener[msg].size();i++)
		{
			Component* c = _messageListener[msg].at(i);
			if (component == c)
			{
				_messageListener[msg].erase(_messageListener[msg].begin() + i); // remove component from listener
				break;
			}
		}
	}
}

bool Entity::AddComponent(Component* component)
{
	std::lock_guard<std::mutex> lock(_mut);
	if (_components.find(component->GetComponentType()) != _components.end())
	{
		return false; // already have object
	}
	_components[component->GetComponentType()] = component; // key value mapping

	return true;
}

Component* Entity::GetComponent(std::string type)
{
	for (auto const& component : _components)
	{
		if (component.first == type) // match keys
			return component.second; // return value
	}

	return nullptr;
}

bool Entity::HasComponent(std::string type)
{
	for (auto const& component : _components)
	{
		if (component.first == type) // match keys
			return true;
	}
	return false;
}

bool Entity::HasComponent(std::vector<std::string> types)
{
	for (auto type : types) // iterate through component list type
	{
		if (_components.find(type) != _components.end())
		{
			return true; // has component
		}
		else
		{
			return false; // unable to find component from list
		}
	}
	return false;
}

bool Entity::HasComponent(const std::string types[], int length)
{
	for(int i = 0; i < length; i ++)
	{
		if (_components.find(types[i]) != _components.end())
		{

		}
		else
		{
			return false; // unable to find component from list
		}
	}
	return true;
}