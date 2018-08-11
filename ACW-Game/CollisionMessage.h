#pragma once
#include "Message.h"
#include "Entity.h"

namespace GameEngine
{
	class CollisionMessage : public Message
	{
	public:
		CollisionMessage(Entity* ent, Entity* collidedEnt) : Message("Collision"), _ent(ent), _collidedEnt(collidedEnt)
		{}
		~CollisionMessage() = default;

	private:
		Entity* _ent;
		Entity* _collidedEnt;

		// getters & setters
	public:
		Entity* GetCollidedEnt() { return _collidedEnt; }
		Entity* GetEnt() { return _ent; }
		Entity* GetOtherEnt(Entity* ent) 
		{
			if (ent == _ent) return _collidedEnt; 
			else return _ent;
		}
	};
}