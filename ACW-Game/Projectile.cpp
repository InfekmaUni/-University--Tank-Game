#include "Projectile.h"

Projectile::Projectile(Entity* owner, Vector4 pos, Vector4 dir, float dist) : RenderedEntity("Bullet", "Metal"), _owner(owner),_startPos(pos), _dist(dist)
{
	SetEntityName("Projectile");
	SetPosition(pos);

	SetRotation(dir);
	SetScale(Vector4(2, 2, 2));

	_vel = new ComponentVelocity(this);
	_vel->SetVelocity(Vector4(0, 0, 0));
	_vel->SetGravity(false);
	Vector4 scale = GetScale();
	scale.multiply(2);
	ComponentCollision* collision = new ComponentCollision(this, scale);

	Vector4 rot = GetRotation();
	Vector4 projDir = Vector4(0, 0, 0);
	if (rot.y() == 0)
	{
		projDir = Vector4(0, 0, -1);
	}
	else if (rot.y() == 90)
	{
		projDir = Vector4(-1, 0, 0);
	}
	else if (rot.y() == -90)
	{
		projDir = Vector4(1, 0, 0);
	}
	else if (rot.y() == -180)
	{
		projDir = Vector4(0, 0, 1);
	}
	projDir.multiply(PROJECTILE_SPEED);

	_dir = projDir;
}

void Projectile::OnUpdate(float dt)
{
	Vector4 distance = GetPosition();
	distance.subtract(_startPos);

	if (distance.length() > _dist)
	{
		SetIsAlive(false); // projectile reached its projectile lifespan
		std::cout << "Projectile traveled its lifespan" << std::endl;
	}
	else
	{
		_vel->SetVelocity(_dir);
	}
}

void Projectile::OnMessage(GameEngine::Message* msg)
{
	if (msg->GetType() == "Collision")
	{
		CollisionMessage* colMsg = (CollisionMessage*)msg;
		Entity* ent = colMsg->GetEnt();
		Entity* ent2 = colMsg->GetCollidedEnt();

		bool generalCollisionResponse = true;
		// determine which ent is the other entity
		Entity* other;
		Entity* self;
		if (ent->GetID() == GetID()) {
			other = ent2;
			self = ent;
		}
		else {
			other = ent;
			self = ent2;
		}
		
		if(!IsOwner(other) && other->GetEntityName() != "Floor") // do not collide with other projectile
			SetIsAlive(false); // collided - died

	}

	RenderedEntity::OnMessage(msg);
}