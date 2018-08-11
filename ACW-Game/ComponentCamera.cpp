#include "ComponentCamera.h"

using namespace GameEngine;
using namespace DirectX;

ComponentCamera::ComponentCamera(Entity* ent, int width, int height) : Component("CAMERA_COMPONENT", ent)
{
	ReconstructProjection(PROJECTION_FOV, width, height, PROJECTION_NEAR_PLANE, PROJECTION_FAR_PLANE);
	ReconstructView(VIEW_POSITION, VIEW_LOOK_AT, VIEW_UP);
	_world = XMMatrixIdentity();
}

ComponentCamera::ComponentCamera(Entity* ent, int width, int height, Vector4 pos, Vector4 lookAt, Vector4 up) : Component("CAMERA_COMPONENT", ent)
{
	ReconstructProjection(PROJECTION_FOV, width, height, PROJECTION_NEAR_PLANE, PROJECTION_FAR_PLANE);
	ReconstructView(pos, lookAt, up);
	_world = XMMatrixIdentity();
}

ComponentCamera::ComponentCamera(Entity* ent, Vector4 pos, Vector4 lookAt, Vector4 up) : Component("CAMERA_COMPONENT", ent)
{
	ReconstructProjection(PROJECTION_FOV, PROJECTION_WIDTH, PROJECTION_HEIGHT, PROJECTION_NEAR_PLANE, PROJECTION_FAR_PLANE);
	ReconstructView(pos, lookAt, up);
	_world = XMMatrixIdentity();
}

ComponentCamera::ComponentCamera(Entity* ent) : Component("CAMERA_COMPONENT", ent)
{
	ReconstructProjection(PROJECTION_FOV, PROJECTION_WIDTH, PROJECTION_HEIGHT, PROJECTION_NEAR_PLANE, PROJECTION_FAR_PLANE);
	ReconstructView(VIEW_POSITION, VIEW_LOOK_AT, VIEW_UP);
	_world = XMMatrixIdentity();
}

void ComponentCamera::RotateWorld(Vector4 rotate)
{
	_world = XMMatrixIdentity();
	XMMATRIX matRot = XMMatrixRotationX(XMConvertToRadians(rotate.x())) * XMMatrixRotationY(XMConvertToRadians(rotate.y())) * XMMatrixRotationZ(XMConvertToRadians(rotate.z()));
	_world = matRot * _world;

}

void ComponentCamera::ReconstructProjection(float fov, int width, int height, float n, float f)
{
	// update projection values
	_projectionWidth = width;
	_projectionHeight = height;
	_projectionFov = fov;
	_projectionNearPlane = n;
	_projectionFarPlane = f;

	// create projection
	_projection = DirectX::XMMatrixPerspectiveFovLH(fov, width / height, n, f);
}

void ComponentCamera::ReconstructView(Vector4 position, Vector4 lookAt, Vector4 up)
{
	// position
	XMFLOAT3 viewPos = XMFLOAT3(position.x(), position.y(), position.z());
	XMVECTOR viewPosV = XMLoadFloat3(&viewPos);

	// look at
	XMFLOAT3 viewLookAt = XMFLOAT3(lookAt.x(), lookAt.y(), lookAt.z());
	XMVECTOR viewLookAtV = XMLoadFloat3(&viewLookAt);

	// up
	XMFLOAT3 viewUp = XMFLOAT3(up.x(), up.y(), up.z());
	XMVECTOR viewUpV = XMLoadFloat3(&viewUp);

	// update local view values
	_up = up;
	_lookAt = lookAt;
	_eyePos = position;

	_view = DirectX::XMMatrixLookAtLH(viewPosV, viewLookAtV, viewUpV);
}


void ComponentCamera::ReconstructView()
{
	// position
	XMFLOAT3 viewPos = XMFLOAT3(_eyePos.x(), _eyePos.y(), _eyePos.z());
	XMVECTOR viewPosV = XMLoadFloat3(&viewPos);

	// look at
	XMFLOAT3 viewLookAt = XMFLOAT3(_lookAt.x(), _lookAt.y(), _lookAt.z());
	XMVECTOR viewLookAtV = XMLoadFloat3(&viewLookAt);

	// up
	XMFLOAT3 viewUp = XMFLOAT3(_up.x(), _up.y(), _up.z());
	XMVECTOR viewUpV = XMLoadFloat3(&viewUp);

	_view = DirectX::XMMatrixLookAtLH(viewPosV, viewLookAtV, viewUpV);
}