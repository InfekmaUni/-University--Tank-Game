#include "AITank.h"


AITank::AITank(TEAM_ID teamID, Vector4 pos) : Tank(TANK_ID::AI, teamID)
{
	SetPosition(pos);
	SetEntityName("AITank");
}

Tank* AITank::EnemyInRange()
{
	Vector4 myPos = GetPosition();

	std::vector<Tank*> tankList = GameScene::myGameScene->GetTankList();

	for (auto& tank : tankList)
	{
		if (tank == nullptr)
			continue;

		if ( GetID() == tank->GetID() || GetTeamID() == tank->GetTeamID() ) // self or same team
			continue;

		Vector4 tankPos = tank->GetPosition();
		Vector4 posDiff = myPos;
		posDiff.subtract(tankPos);

		if (posDiff.length() < ACQUISITION_RANGE)
		{
			return tank;
		}
	}

	return false;
}

void AITank::PatrolToNewPosition()
{
	//srand(time(NULL));
	int min = -10;
	int max = 10;

	// https://stackoverflow.com/questions/7887941/random-number-from-9-to-9-in-c
	std::mt19937 gen;
	gen.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dis(10, -10);

	int xPos = dis(gen);

	gen.seed(std::random_device()());
	int zPos = dis(gen);

	_moveToPos = Vector4(xPos, 0, zPos);
}

void AITank::OnMessage(GameEngine::Message* msg)
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

		if(_curAiState == AI_STATE::PATROLLING) // collided
			PatrolToNewPosition();
	}

	Tank::OnMessage(msg);
}

void AITank::OnUpdate(float dt)
{
	switch (_curAiState)
	{
		case AI_STATE::PATROLLING:

			if (!_movingToPos)
			{
				PatrolToNewPosition();
				_movingToPos = true;
			}
			else
			{
				Vector4 dir = _moveToPos;
				dir.subtract(GetPosition());

				float dist = dir.length();
				if (dist < 5)
				{
					_movingToPos = false;
					break;
				}
				dir.normalise();
				dir.multiply(TANK_ACCELERATION);

				_vel->SetVelocity(dir); // set vel to direction to object
			}

			//_target = EnemyInRange();
			//if (_target != nullptr)
			//	_curAiState = AI_STATE::ENGAGED;

			break;
		case AI_STATE::ENGAGED:
			_target = EnemyInRange();
			if (_target == nullptr) // no target in range
			{
				AI_STATE::PATROLLING;
			}

			Fire();
			break;
	};

}