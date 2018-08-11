#include "HealthPack.h"



HealthPack::HealthPack(Vector4 pos) : RenderedEntity("HealthPack", "HealthPack")
{
	SetScale(Vector4(80, 80, 80));
	SetPosition(pos);

	SetEntityName("HealthPack");

	Vector4 scale = GetScale();
	scale.multiply(2);
	ComponentCollision* collision = new ComponentCollision(this, scale, true);
}

void HealthPack::OnMessage(GameEngine::Message* msg)
{
	if (msg->GetType() == "Collision")
	{
		CollisionMessage* colMsg = (CollisionMessage*)msg;
		Entity* ent = colMsg->GetEnt();
		Entity* ent2 = colMsg->GetCollidedEnt();

		bool generalCollisionResponse = true;
		// determine which ent is the other entity
		Entity* other;
		if (ent->GetID() == GetID())
			other = ent2;
		else
			other = ent;

		if (other->GetEntityName() != "Projectile" && other->GetEntityName() != "Floor")
		{
			SetIsAlive(false);
		}
	}
}