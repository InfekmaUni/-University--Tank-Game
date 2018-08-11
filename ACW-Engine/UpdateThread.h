#pragma once
#include "ACWThread.h"
#include "Game.h"
#include <thread>

namespace GameEngine
{
	class Game;
	class UpdateThread : public ACWThread
	{
	public:
		UpdateThread(Game* game, int freq = DEFAULT_FREQUENCY) : ACWThread(game, freq)
		{}
		~UpdateThread() = default;

	private:
		std::vector<float> timeStep;
		float _averageTimeStep;
		ACWTimer _averageTimeStepTimer;

		// getters
	public:
		float& GetAverageTimeStep() { return _averageTimeStep; }

	public:
		void Run();
		void UpdateAverageTimeStep(float dt);
		void AddTweakbarVars();
	};
}