#pragma once
#include "Game.h"

#include "SceneManager.h"
#include "NetworkManager.h"

#include "GameScene.h"

using namespace GameEngine;

class TankGame : public Game
{
public:
	TankGame() : Game()
	{}
	~TankGame() = default;

	// data
private:

// functions
public:
	virtual void Initialise(ApplicationWindow* window);
	virtual void Shutdown();
	virtual int Run();

	virtual void OnUpdate();
	virtual void OnRender();

	virtual void OnNetwork();

	virtual void ListenMessage(Message* msg);
};

