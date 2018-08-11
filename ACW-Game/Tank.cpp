#include "Tank.h"

#include "KeyPressMessage.h"
#include "GameScene.h"

Tank::Tank(TANK_ID id, TEAM_ID teamID) : RenderedEntity("Tank", TEAM_CAMO[(int)teamID]), _tankID(id), _teamID(teamID), _curHealth(TANK_MAX_HEALTH)
{
	SetScale(Vector4(1, 1, 1.5f));
	SetPosition(Vector4(0, 50, 0));

	_vel = new ComponentVelocity(this);
	_vel->SetVelocity(Vector4(0, 0, 0));
	_vel->SetGravity(false);
	Vector4 scale = GetScale();
	scale.multiply(2);
	ComponentCollision* collision = new ComponentCollision(this, scale);

	_score = new ComponentScore(this);
	_reloadPeroid = new ACWTimer(TANK_RELOAD_TIME); // reload timer is done
}

void Tank::Heal(int heal)
{
	if(_curHealth <= TANK_MAX_HEALTH) // only heal if health is less then max health
		_curHealth += heal;
}

void Tank::TakeDamage(int dmg)
{
	_curHealth -= dmg;
	
	if (_curHealth <= 0)
	{
		OnDeath();
	}
}

void Tank::OnDeath()
{
	SetFakeDeath(true);
	_score->ScoreIncrement(SCORE_CREDIT::DIED);
}

void Tank::OnRevive()
{
	SetFakeDeath(false);
}

void Tank::Respawn(Vector4 pos)
{
	SetPosition(pos);
	OnRevive();
}

void Tank::Killed()
{
	_score->ScoreIncrement(SCORE_CREDIT::KILL);
}

void Tank::Fire()
{
	if (_reloadPeroid->IsDone())
	{
		// create projectile
		Vector4 projectilePos = GetPosition();
		projectilePos.add(GetScale());
		projectilePos.y(projectilePos.y() - GetScale().y());

		Projectile* projectile = new Projectile(this, projectilePos, GetRotation(), 500);
		EntityManager* manager = (EntityManager*)GameScene::myGameScene->GetManagerByName("EntityManager");
		manager->AddEntity(projectile);

		// start reload
		_reloadPeroid->Start(TANK_RELOAD_TIME);
	}
}

void Tank::OnMessage(Message* msg)
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

		if (other->GetEntityName() == "Projectile")
		{
			generalCollisionResponse = false;
			Projectile* proj = static_cast<Projectile*>(other);

			Tank* ownerTank = (Tank*)proj->GetOwner();

			if (!proj->IsOwner(this) && ownerTank->GetTeamID() != GetTeamID() ) // if not owner and not same team
			{
				TakeDamage();
			}

			if (GetHealth() <= 0)
			{
				TankKilledMessage* msg = new TankKilledMessage(proj->GetOwner(), this);
				proj->GetOwner()->OnMessage(msg);
			}
		}
		else if (other->GetEntityName() == "HealthPack")
		{
			Heal();
		}

		if (generalCollisionResponse)
		{
			Vector4 thisPos = _transformComp->GetPosition();
			Vector4 oldPos = _transformComp->GetOldPosition();

			// collision response
			Vector4 response = oldPos;
			response.subtract(thisPos);

			_transformComp->AddPosition(response);
		}
	}
	else if (msg->GetType() == "TankKilled")
	{
		TankKilledMessage* killMsg = (TankKilledMessage*)msg;

		if(killMsg->GetKiller()->GetID() == GetID()) // got a kill
			Killed();
	}

	RenderedEntity::OnMessage(msg);
}
