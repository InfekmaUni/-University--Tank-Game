#pragma once
#include "ACWThread.h"
#include "Game.h"

namespace GameEngine
{
	class Game;
	class RenderThread : public ACWThread
	{
	public:
		RenderThread(Game* game, int freq = DEFAULT_FREQUENCY) : ACWThread(game, freq)
		{}
		~RenderThread() = default;

	public:
		void Run();
		void AddTweakbarVars();
	};
}