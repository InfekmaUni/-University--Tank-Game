#pragma once
#include "UpdateableSystem.h"
#include "EntityManager.h"
#include "SceneManager.h"
#include <string>

#include "CollisionMessage.h"
#include "ComponentTransform.h"
#include "ComponentCollision.h"
#include "ComponentVelocity.h"

using namespace GameEngine;

const Vector4 GRAVITIONAL_CONSTANT = Vector4(0, -9.8f, 0);
class SystemPhysics : public GameEngine::UpdateableSystem
{
public:
	SystemPhysics() : GameEngine::UpdateableSystem("SystemPhysics")
	{}
	~SystemPhysics() = default;

private:
	Vector4 _gravity;
	GameEngine::EntityManager* _eManager;

public:
	virtual void Update(float dt, Entity* ent);
	void Shutdown() {}
	void Initialise() {}
	bool HasCollided(ComponentTransform* thisT, ComponentCollision* thisC, ComponentTransform* otherT, ComponentCollision* otherC);
	void ProcessCollision(GameEngine::Entity* ent);
};

