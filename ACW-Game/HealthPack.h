#pragma once
#include "RenderedEntity.h"
#include "Tank.h"

#include "CollisionMessage.h"

const int HEAL_AMOUNT = 1;
class HealthPack : public RenderedEntity
{
public:
	HealthPack(Vector4 pos);
	~HealthPack() = default;

public:
	virtual void OnMessage(GameEngine::Message* msg);
};