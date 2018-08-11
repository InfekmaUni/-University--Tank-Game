#pragma once
#include "Component.h"

enum class SCORE_CREDIT
{
	KILL = 50,
	DIED = 25,
};
class ComponentScore : public GameEngine::Component
{
public:
	ComponentScore(GameEngine::Entity* ent);
	~ComponentScore() = default;

private:
	int _score;

public:
	void ScoreIncrement(int val) { _score += val; }
	void ScoreIncrement(SCORE_CREDIT val) { _score += static_cast<int>(val); }

	int GetScore() { return _score; }
};