#pragma once
#include "ACWThread.h"
#include "Game.h"

namespace GameEngine
{
	class Game;
	class NetworkThread : public ACWThread
	{
	public:
		NetworkThread(Game* game, int freq = DEFAULT_FREQUENCY) : ACWThread(game, freq)
		{}
		~NetworkThread() = default;

		//
	public:
		void Run();
		void AddTweakbarVars();
	};
}