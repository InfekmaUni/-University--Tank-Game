#pragma once
#include "Component.h"

#include <string>
#include "Shader.h"

class Component;
class ComponentRender : public  GameEngine::Component
{
public:
	ComponentRender(GameEngine::Entity* ent, std::string vName, std::string pName) : Component("RENDER_COMPONENT", ent), _vName(vName), _pName(pName)
	{
	}
	// set premade shader
	ComponentRender(GameEngine::Entity* ent, GameEngine::Shader* shader, std::string vName, std::string pName) : Component("RENDER_COMPONENT", ent), _vName(vName), _pName(pName), _shader(shader)
	{
		SetInit(true);
	}
	~ComponentRender() = default;
private:
	GameEngine::Shader* _shader;
	std::string _vName;
	std::string _pName;

	// getters & setters
public:
	std::string GetVShaderName() { return _vName; }
	std::string GetPShaderName() { return _pName; }
	GameEngine::Shader* GetShader() { return _shader; }
	void SetShader(GameEngine::Shader* shader) { _shader = shader; }

};