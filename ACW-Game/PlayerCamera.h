#pragma once
#include <DirectXMath.h>

#include "Tank.h"
#include "ComponentCamera.h"

class PlayerCamera : public Entity
{
public:
	PlayerCamera();
	~PlayerCamera() = default;

	// data
private:
	ComponentCamera* _activeCamera;
	Tank* _player;
	Vector4 _cameraPos;
	Vector4 _cameraLookAt;

	// getters & setters
public:
	void SetPlayerTank(Tank* tank) { _player = tank; }

	// functions
public:
	void OnUpdate(float dt);
	void SetCameraPosition();
	void SetCameraLookAt();
};

