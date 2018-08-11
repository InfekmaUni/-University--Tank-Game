#pragma once
#include "RenderedEntity.h"
#include "ComponentVelocity.h"
#include "ComponentCollision.h"
#include "ComponentScore.h"

#include "MousePressMessage.h"
#include "CollisionMessage.h"
#include "TankKilledMessage.h"

#include "Vector4.h"
#include "Projectile.h"


using namespace GameEngine;

enum class TANK_ID
{
	SELF = 0,
	PLAYER = 1,
	AI = 2
};

enum class TEAM_ID
{
	TEAM_1 = 0,
	TEAM_2 = 1
};

const std::string TEAM_CAMO[2] = { "Team-1-Camo", "Team-2-Camo" };
const float TANK_ACCELERATION = 10;
const float TANK_ROTATE_SPEED = 10;
const float TANK_ROTATE_FRICTION = 0.5f;
const int TANK_MAX_HEALTH = 3;
const float TANK_RELOAD_TIME = 1;

class Projectile;
class Tank : public RenderedEntity
{
public:
	Tank(TANK_ID id, TEAM_ID teamID);
	~Tank() = default;
protected:
	TANK_ID _tankID;
	TEAM_ID _teamID;
	ComponentVelocity* _vel;
	ComponentScore* _score;
	Vector4 _forward = Vector4(0, 0, -1);
	ACWTimer* _reloadPeroid;

	int _curHealth;

public:
	TEAM_ID GetTeamID() { return _teamID; }
	TANK_ID GetTankID() { return _tankID; }
	int GetHealth() { return _curHealth; }
	bool IsDead() { return _curHealth <= 0; }

public:
	virtual void OnMessage(GameEngine::Message* msg);

	void TakeDamage(int dmg = 1);
	void Heal(int heal = 1);
	void Respawn(Vector4 pos);
	void Fire();

	void Killed();

	virtual void OnDeath();
	virtual void OnRevive();
};