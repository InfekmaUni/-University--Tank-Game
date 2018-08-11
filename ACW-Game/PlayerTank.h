#pragma once
#include "Tank.h"

class PlayerTank : public Tank
{
public:
	PlayerTank(int playerID, TEAM_ID teamID, Vector4 pos);
	~PlayerTank();

private:
	int _playerID;
	bool _localPlayer;

	// get & set
public:
	int GetPlayerID() { return _playerID; }
	bool IsLocalPlayer() { return _localPlayer; }
	void SetLocalPlayer(bool val) { _localPlayer = val; }

	// functions
public:
	virtual void OnMessage(Message* msg);
};

