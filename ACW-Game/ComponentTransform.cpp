#include "ComponentTransform.h"

using namespace GameEngine;
using namespace DirectX;

void ComponentTransform::ReconstructModelSpace() {
	XMMATRIX matPos = XMMatrixTranslation(_position.x(), _position.y(), _position.z());
	XMMATRIX matScale = XMMatrixScaling(_scale.x(), _scale.y(), _scale.z());;
	XMMATRIX matRot = XMMatrixRotationX(XMConvertToRadians(_rotation.x())) * XMMatrixRotationY(XMConvertToRadians(_rotation.y())) * XMMatrixRotationZ(XMConvertToRadians(_rotation.z()));
	_modelSpace = matScale * matRot * matPos;
}