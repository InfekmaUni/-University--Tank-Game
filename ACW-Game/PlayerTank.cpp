#include "PlayerTank.h"

PlayerTank::PlayerTank(int playerID, TEAM_ID teamID, Vector4 pos) : Tank(TANK_ID::PLAYER, teamID), _playerID(playerID)
{
	SetPosition(pos);
	SetEntityName("PlayerTank");
}

PlayerTank::~PlayerTank()
{
}

void PlayerTank::OnMessage(Message* msg)
{
	if (msg->GetType() == "KeyPress")
	{
		KeyPressMessage* keyMsg = (KeyPressMessage*)msg;
		int key = keyMsg->GetKey();
		bool down = keyMsg->GetDownState();
		if (key == 87) // w
		{
			_vel->AddVelocity(Vector4(0, 0, -TANK_ACCELERATION));
			SetRotation(Vector4(0, 0, 0));
		}
		if (key == 83) // s
		{
			_vel->AddVelocity(Vector4(0, 0, TANK_ACCELERATION));
			SetRotation(Vector4(0, -180, 0));
		}
		if (key == 65) // a
		{
			_vel->AddVelocity(Vector4(TANK_ACCELERATION, 0, 0));
			SetRotation(Vector4(0, -90, 0));
		}
		if (key == 68) // d
		{
			_vel->AddVelocity(Vector4(-TANK_ACCELERATION, 0, 0));
			SetRotation(Vector4(0, 90, 0));
		}
		if (key == 32 && _localPlayer && !GetFakeDeath() ) // spacebar
		{
			Fire();
		}
	}
	else if (msg->GetType() == "MousePress")
	{
		MousePressMessage* mousePressMessage = (MousePressMessage*)msg;
		bool leftDown = mousePressMessage->IsLeftMouseDown();
		bool rightDown = mousePressMessage->IsRightMouseDown();

		if (leftDown)
		{
			int x = 0;
		}
	}
	else if (msg->GetType() == "Collision")
	{
		CollisionMessage* colmsg = (CollisionMessage*)msg;
		Entity* ent = colmsg->GetEnt();
		Entity* ent2 = colmsg->GetOtherEnt(ent);

		// determine which ent is the other entity
		Entity* other;
		if (ent->GetID() == GetID())
			other = ent2;
		else
			other = ent;
	}

	Tank::OnMessage(msg);
}