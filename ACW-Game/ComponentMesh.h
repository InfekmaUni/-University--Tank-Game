#pragma once
#include <vector>
#include <fstream>

#include "Component.h"
#include "Vector4.h"
#include "VIBO.h"

#include "Game.h"
#include "Mesh.h"

class ComponentMesh : public  GameEngine::Component
{
public:
	ComponentMesh(GameEngine::Entity* ent, std::string name) : Component("MESH_COMPONENT", ent), _meshName(name)
	{}


	ComponentMesh(GameEngine::Entity* ent, GameEngine::Mesh* mesh, std::string name) : Component("MESH_COMPONENT", ent), _meshName(name), _mesh(mesh)
	{
		SetInit(true);
	}

	~ComponentMesh() = default;

	// data
private:
	std::string _meshName;
	GameEngine::Mesh* _mesh;

	// setters & getters
public:
	GameEngine::Mesh * GetMesh() { return _mesh; }
	void SetMesh(GameEngine::Mesh* mesh) { _mesh = mesh; }
	std::string GetMeshName() { return _meshName; }
};