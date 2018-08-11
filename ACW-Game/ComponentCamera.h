#pragma once
#include <DirectXMath.h>

#include "Component.h"
#include "Vector4.h"

// default projection vals
const float PROJECTION_NEAR_PLANE = 0.01f;
const float PROJECTION_FAR_PLANE = 100000.0f;
const float PROJECTION_FOV = DirectX::XM_PIDIV2;
const int PROJECTION_WIDTH = 800;
const int PROJECTION_HEIGHT = 600;

// default view vals
const Vector4 VIEW_LOOK_AT = Vector4(0, 1, 1);
const Vector4 VIEW_POSITION = Vector4(0, 1, -5);
const Vector4 VIEW_UP = Vector4(0, 1, 0);

class ComponentCamera : public  GameEngine::Component
{
public:
	ComponentCamera(GameEngine::Entity* ent);
	ComponentCamera(GameEngine::Entity* ent, int width, int height);
	ComponentCamera(GameEngine::Entity* ent, int width, int height, Vector4 pos, Vector4 lookAt = VIEW_LOOK_AT, Vector4 up = VIEW_UP);
	ComponentCamera(GameEngine::Entity* ent, Vector4 pos, Vector4 lookAt = VIEW_LOOK_AT, Vector4 up = VIEW_UP);
	~ComponentCamera() = default;

	// data
private:
	int _projectionWidth;
	int _projectionHeight;
	float _projectionFov;
	float _projectionNearPlane;
	float _projectionFarPlane;

	Vector4 _lookAt;
	Vector4 _eyePos;
	Vector4 _up;

	DirectX::XMMATRIX	_projection;
	DirectX::XMMATRIX	_view;
	DirectX::XMMATRIX	_world;

	// getters & setters
public:
	DirectX::XMMATRIX GetProjection() { return _projection; }
	DirectX::XMMATRIX GetView() { return _view; }
	DirectX::XMMATRIX GetWorld() { return _world; }

	void SetLookAt(Vector4 newLook) { _lookAt = newLook; ReconstructView(); }
	void SetEyePos(Vector4 newPos) { _eyePos = newPos; ReconstructView(); }
	void SetUp(Vector4 newUp) { _up = newUp; ReconstructView(); }

	Vector4 GetLookAt() { return _lookAt; }
	Vector4 GetEyePos() { return _eyePos; }
	Vector4 GetUp() { return _up; }

	// functions
public:
	void ReconstructView();
	void ReconstructView(Vector4 position, Vector4 lookAt, Vector4 up);
	void ReconstructProjection(float fov, int width, int height, float near, float far);
	void RotateWorld(Vector4 rotate);
	void ResetWorld() { _world = DirectX::XMMatrixIdentity(); }


};