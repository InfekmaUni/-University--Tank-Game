#pragma once
#include "Tank.h"

#include "GameScene.h"

#include <random>

enum class AI_STATE
{
	PATROLLING = 0,
	ENGAGED = 1,
};

const float ACQUISITION_RANGE = 20;

class AITank : public Tank
{
public:
	AITank(TEAM_ID teamID, Vector4 pos);
	~AITank() = default;

private:
	AI_STATE _curAiState = AI_STATE::PATROLLING;
	Vector4 _moveToPos;
	Tank* _target;
	bool _movingToPos;

public:
	virtual void OnUpdate(float dt);
	virtual void OnMessage(GameEngine::Message* msg);

	void PatrolToNewPosition();
	Tank* EnemyInRange();
};