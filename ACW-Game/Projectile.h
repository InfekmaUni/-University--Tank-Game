#pragma once
#include "RenderedEntity.h"

#include "ComponentVelocity.h"
#include "ComponentCollision.h"

#include "TankKilledMessage.h"
#include "CollisionMessage.h"

#include "Tank.h"

const int PROJECTILE_SPEED = 100;
class Tank;
class Projectile : public RenderedEntity
{
public:
	Projectile(Entity* owner, Vector4 pos, Vector4 dir, float distance);
	~Projectile() = default;

protected:
	Entity* _owner;
	ComponentVelocity* _vel;
	Vector4 _startPos;
	Vector4 _dir;
	float _dist;

public:
	Entity* GetOwner() { return _owner; }
	bool IsOwner(Entity* ent) { return (ent->GetID() == _owner->GetID()); }

public:
	virtual void OnUpdate(float dt);
	virtual void OnMessage(GameEngine::Message* msg);
};