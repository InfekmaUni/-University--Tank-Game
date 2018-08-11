#pragma once
#include "Message.h"
#include "Entity.h"

class TankKilledMessage : public GameEngine::Message
{
public:
	TankKilledMessage(GameEngine::Entity* killer, GameEngine::Entity* killed);
	~TankKilledMessage() = default;

private:
	GameEngine::Entity* _killer;
	GameEngine::Entity* _killed;

public:
	GameEngine::Entity* GetKiller() { return _killer; }
	GameEngine::Entity* GetKilled() { return _killed; }
};

