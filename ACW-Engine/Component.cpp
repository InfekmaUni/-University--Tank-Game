#include "Component.h"

using namespace GameEngine;
Component::Component(std::string type, Entity* parent) : _componentType(type), _parent(parent)
{
	parent->AddComponent(this);
}

void Component::BroadcastMessage(Message* msg)
{
	Game::myGame->BroadcastMessage(msg);
}