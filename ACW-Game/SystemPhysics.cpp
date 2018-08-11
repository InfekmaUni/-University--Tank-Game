#include "SystemPhysics.h"


const std::string MOVEMENT_MASK[2] = { "TRANSFORM_COMPONENT", "VELOCITY_COMPONENT" };
const std::string COLLISION_MASK[2] = { "TRANSFORM_COMPONENT", "COLLISION_COMPONENT" };
void SystemPhysics::Update(float dt, Entity* ent)
{

	_eManager = (EntityManager*)SceneManager::myScene->GetManagerByName("EntityManager");
	if (_eManager == nullptr) // manager doesn't exist
		return;

	std::vector<Entity*> entList = _eManager->GetEntityList();
	if (entList.size() <= 0)
		return;

	std::vector<Entity*> gravityEnts;

	bool hasCollisionMask = ent->HasComponent(COLLISION_MASK, (sizeof(COLLISION_MASK) / sizeof(COLLISION_MASK[0])));
	if (hasCollisionMask)
	{
		ComponentCollision* colComp = (ComponentCollision*)ent->GetComponent("COLLISION_COMPONENT");

		if (!colComp->IsStatic()) // we do not process collision for static objects, only those acting upon it
		{
			ProcessCollision(ent);
		}
	}
	bool hasMovementMask = ent->HasComponent(MOVEMENT_MASK, (sizeof(MOVEMENT_MASK) / sizeof(MOVEMENT_MASK[0])));
	if (hasMovementMask)
	{
		ComponentTransform* transformComp = (ComponentTransform*)ent->GetComponent("TRANSFORM_COMPONENT");
		ComponentVelocity* velComp = (ComponentVelocity*)ent->GetComponent("VELOCITY_COMPONENT");

		Vector4 temp = velComp->GetVelocity();
		Vector4 newVel = velComp->GetVelocity();
		newVel.multiply(velComp->GetFriction());
		temp.multiply(dt); // delta time

		// movement
		Vector4 newPos = transformComp->GetPosition();
		newPos.add(temp);
		transformComp->SetPosition(newPos);

		velComp->SetVelocity(newVel); // set new vel equal to friction

		// gravity
		if (velComp->HasGravity())
		{
			gravityEnts.push_back(ent);
		}
	}

	for (auto const& ent : gravityEnts) // list generated from movement mask who have gravity enabled
	{
		ComponentTransform* transformComp = (ComponentTransform*)ent->GetComponent("TRANSFORM_COMPONENT");
		ComponentVelocity* velComp = (ComponentVelocity*)ent->GetComponent("VELOCITY_COMPONENT");

		Vector4 temp = GRAVITIONAL_CONSTANT;
		temp.multiply(dt);

		// add gravity
		transformComp->AddPosition(temp);

		// check for collision caused due to gravity
		ProcessCollision(ent);
	}
}

void SystemPhysics::ProcessCollision(Entity* ent)
{
	ComponentTransform* transformComp = (ComponentTransform*)ent->GetComponent("TRANSFORM_COMPONENT");
	ComponentCollision* colComp = (ComponentCollision*)ent->GetComponent("COLLISION_COMPONENT");

	std::vector<Entity*> entList = _eManager->GetEntityList();
	// iterate through list
	for (auto const& other : entList)
	{
		if (other->GetID() != ent->GetID() && !colComp->IsStatic() && !other->GetFakeDeath()) // if not same entity
		{
			bool hasCollisionMask2 = other->HasComponent(COLLISION_MASK, (sizeof(COLLISION_MASK) / sizeof(COLLISION_MASK[0])));
			if (hasCollisionMask2)
			{
				ComponentTransform* transformCompOther = (ComponentTransform*)other->GetComponent("TRANSFORM_COMPONENT");
				ComponentCollision* colCompOther = (ComponentCollision*)other->GetComponent("COLLISION_COMPONENT");

				// check for collision
				bool collided = HasCollided(transformComp, colComp, transformCompOther, colCompOther);
				if (collided) // if collision
				{
					// send message collision occureds
					CollisionMessage* msg = new CollisionMessage(ent, other);
					other->OnMessage(msg);
					ent->OnMessage(msg);

					//Vector4 thisPos = transformComp->GetPosition();
					//Vector4 oldPos = transformComp->GetOldPosition();

					//// collision response
					//Vector4 response = oldPos;
					//response.subtract(thisPos);

					//transformComp->AddPosition(response);

					//while (collided)
					//{
					//	// update position relative to collision response
					//	transformComp->AddPosition(response);

					//	// check again if colliding
					//	collided = HasCollided(transformComp, colComp, transformCompOther, colCompOther);
					//}
				}
			}
		}
	}
}

bool SystemPhysics::HasCollided(ComponentTransform* thisT, ComponentCollision* thisC, ComponentTransform* otherT, ComponentCollision* otherC)
{
	// update component
	Vector4 thisPos = thisT->GetPosition();
	thisC->SetCenter(thisPos);

	Vector4 otherPos = otherT->GetPosition();
	otherC->SetCenter(otherPos);

	if (thisC->GetBounds().Contains(otherC->GetBounds())) // collision
	{	
		return true;
	}
	return false;
}