#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <time.h>
#include <atomic>
#include <functional>

#define _WINSOCKAPI_
#include <Windows.h>
#include <mutex>

#include "ACWTimer.h"
const float DEFAULT_FREQUENCY = 60;

namespace GameEngine
{
	enum class THREAD_CORE_AFFINITY
	{
		CORE_ONE = 0x01,
		CORE_TWO = 0x02,
		CORE_THREE = 0x04,
		CORE_FOUR = 0x08,
		CORE_FIVE = 0x016,
	};

	class Game;
	class ACWThread
	{
	public:
		ACWThread() = default;
		ACWThread(Game* game, int freq) : _game(game)
		{
			_frequency = 1.0f / static_cast<float>(freq);
			_fps = freq;
		}
		~ACWThread() = default;

		// data
	protected:
		Game * _game;
		int taskID = 0;
		std::thread myThread;

		// changes if join is called 
		std::atomic<bool> _isRunning = false;

		// forced paused
		std::atomic<bool> _forcePause = false;
		
		// check whether thread is idling
		std::atomic<bool> _idle = false;

		// timer vars
		float _lastTime;
		float _actualLastTime;

		int _fps;
		int _actualFps;

		// updates per second
		float _frequency;

		const static int FREQUENCY_SAMPLE_SIZE = 100; 
		float _actualFrequency[FREQUENCY_SAMPLE_SIZE];
		int _currentSampleId = 0;

		ACWTimer _updateTimer;
		ACWTimer _fpsTimer;
		int _fpsCounter = 0;

		std::shared_ptr<std::mutex> _mutex;

		// getters & setters
	public:
		bool IsIdle() { return _idle; }
		bool IsRunning() { return _isRunning; }
		void ForcePause(bool val) { _forcePause = val; }

		void LowerFrequency(int lower) { if (_fps == 1) return; _fps -= lower; }
		void IncreaseFrequency(int higher) { _fps += higher; }

		int& GetFPS() { return _fps; }
		void SetFPS(int fps) { _fps = fps; }

		int& GetActualFPS() { return _actualFps; }
		void SetActualFPS(int fps) { _actualFps = fps; }

		// functions
	public:
		bool FreqWait();
		virtual void Start(std::shared_ptr<std::mutex> mutex);
		virtual void Run() = 0;
		virtual void Stop();
		virtual void UpdateActualFreqTime();
	};
}