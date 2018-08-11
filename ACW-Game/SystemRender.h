#pragma once
#include "RenderableSystem.h"
#include "Game.h"

#include <d3d11_1.h>
#include <vector>

// cross
#include "Shader.h"
#include "Renderer.h"
#include "Entity.h"

//dx
#include "Renderer_DX.h"
#include "VIBO_DX.h"
#include "Shader_DX.h"

// managers
#include "ResourceManager.h"
#include "EntityManager.h"

// components
#include "ComponentCamera.h"
#include "ComponentTexture.h"
#include "ComponentTransform.h"
#include "ComponentMesh.h"
#include "ComponentRender.h"

class SystemRender : public GameEngine::RenderableSystem
{
	// structors
public:
	SystemRender() : GameEngine::RenderableSystem("SystemRender")
	{}
	~SystemRender() = default;

protected:
	GameEngine::ResourceManager* _rManager = 0;
	ComponentCamera* _activeCamera = 0;
	GameEngine::Shader* _activeShader = 0;

	// placeholder for default camera
	bool _defaultCamera = true;
	GameEngine::Entity* _placeHolderEnt;

public:
	ComponentCamera* GetActiveCamera() { return _activeCamera; }

	// functions
public:
	void Shutdown();
	void Initialise();
	void Render(GameEngine::Renderer* renderer, GameEngine::Entity* ent);
	void RenderEntity(GameEngine::Renderer* renderer, GameEngine::Entity* ent);
	void OnMessage(GameEngine::Message* msg);
};