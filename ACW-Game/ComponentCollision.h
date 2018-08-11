#pragma once
#include "Component.h"
#include "Vector4.h"

#include <DirectXCollision.h>

using namespace GameEngine;
using namespace DirectX;

class ComponentCollision : public  GameEngine::Component
{
public:
	ComponentCollision(Entity* ent, Vector4 extend, bool isStatic = false) : Component("COLLISION_COMPONENT", ent), _extends(extend), _isStatic(isStatic)
	{
		SetExtends(_extends);
	}
	~ComponentCollision() = default;

private:
	BoundingBox _box;
	Vector4 _extends;
	bool _isStatic;

public:
	bool IsStatic() { return _isStatic; }
	BoundingBox GetBounds() { return _box; }
	Vector4 Extends() { return _extends; }
	void SetExtends(Vector4 newExtend);
	XMFLOAT3 GetCenter() { return _box.Center; }
	void SetCenter(Vector4 pos) {
		_box.Center = XMFLOAT3(pos.x(), pos.y(), pos.z());
	};
};