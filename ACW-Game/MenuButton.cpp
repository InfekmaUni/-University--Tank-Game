#include "MenuButton.h"



MenuButton::MenuButton(std::string textureName, Vector4 pos) : RenderedEntity("Plane", textureName)
{
	Vector4 scale = Vector4(10, 10);
	SetPosition(pos);
}

bool MenuButton::ContainsMouse(Vector4 pos)
{
	Vector4 curPos = GetPosition();
	curPos.subtract(pos);

	return false;
}

void MenuButton::OnMessage(GameEngine::Message* msg)
{
	if (msg->GetType() == "MouseMove")
	{
		MouseMoveMessage* mouseMsg = (MouseMoveMessage*)msg;
		Vector4 mousePos = mouseMsg->GetPosition();


	}
	RenderedEntity::OnMessage(msg);
}