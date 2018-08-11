#include "PlayerCamera.h"

#include "SceneManager.h"

PlayerCamera::PlayerCamera() : Entity()
{
	_activeCamera = new ComponentCamera(this);
}

void PlayerCamera::OnUpdate(float dt)
{
	if (_player == nullptr) // double check
		return;

	SetCameraPosition();
	SetCameraLookAt();
}

void PlayerCamera::SetCameraPosition()
{
	Vector4 cameraPos = _player->GetPosition();
//	Vector4 cameraHeightOffset = Vector4(0, 25, 15);
	Vector4 cameraHeightOffset = Vector4(0, 100, 50);
	cameraPos.add(cameraHeightOffset);

	// set camera update
	_activeCamera->SetEyePos(cameraPos);
}

void PlayerCamera::SetCameraLookAt()
{
	// camera initialisation
	Vector4 cameraLookAt = _player->GetPosition();
	//Vector4 cameraLookAtOffset = Vector4(0, 10, 0);
	//cameraLookAt.add(cameraLookAtOffset);

	// set look at
	_activeCamera->SetLookAt(cameraLookAt);
}
