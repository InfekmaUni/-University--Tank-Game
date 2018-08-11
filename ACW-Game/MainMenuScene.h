#pragma once
#include "Scene.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include "SystemRender.h"

#include "MenuButton.h"

using namespace GameEngine;

class MainMenuScene : public GameEngine::Scene
{
public:
	MainMenuScene(int id);
	~MainMenuScene() = default;

public:
	void OnInitialise();
	void OnUpdate(float delta);
	void OnRender(GameEngine::Renderer* renderer);
	void OnShutdown();
	void OnMessage(GameEngine::Message* msg);
};

