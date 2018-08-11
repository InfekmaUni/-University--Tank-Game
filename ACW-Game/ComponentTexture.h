#pragma once
#include "Component.h"
#include "Texture.h"

class ComponentTexture : public  GameEngine::Component
{
public:
	ComponentTexture(GameEngine::Entity* ent, std::string name) : Component("TEXTURE_COMPONENT", ent), _textureName(name)
	{}
	~ComponentTexture() = default;

protected:
	GameEngine::Texture * _texture;
	std::string _textureName;

	// getters & setters
public:
	GameEngine::Texture * GetTexture() { return _texture; }
	void SetTexture(GameEngine::Texture* texture) { _texture = texture; }
	std::string GetName() { return _textureName; }
};