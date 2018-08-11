#pragma once
#include "RenderedEntity.h"
#include "ComponentCollision.h"
#include "MouseMoveMessage.h"
#include "MousePressMessage.h"

class MenuButton : public RenderedEntity
{
public:
	MenuButton(std::string texture, Vector4 pos);
	~MenuButton() = default;

public:
	virtual void OnMessage(GameEngine::Message* msg);

	bool ContainsMouse(Vector4 pos);
};