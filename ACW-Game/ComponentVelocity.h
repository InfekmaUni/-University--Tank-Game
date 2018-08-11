#pragma once
#include "Component.h"
#include "Vector4.h"
#include <DirectXMath.h>

using namespace GameEngine;

const float FRICTION = 0.90f;
const float TERMINAL_VELOCITY = 1000;
class ComponentVelocity : public GameEngine::Component
{
public:
	ComponentVelocity(Entity* ent, bool grav = true, float fric = FRICTION) : Component("VELOCITY_COMPONENT", ent), _gravity(grav), _vel(Vector4(0,0,0)), _fric(fric)
	{}
	~ComponentVelocity() = default;

private:
	Vector4 _vel;
	bool _gravity;
	float _fric;

public:
	Vector4 GetVelocity() { return _vel; };
	void SetVelocity(Vector4 newVel) { _vel = newVel; Clamp(_vel, -TERMINAL_VELOCITY, TERMINAL_VELOCITY); }
	void AddVelocity(Vector4 newVel) { _vel.add(newVel); Clamp(_vel, -TERMINAL_VELOCITY, TERMINAL_VELOCITY); }

	float GetFriction() { return _fric; }
	float GetTerminalVelocity() { return TERMINAL_VELOCITY; }

	bool HasGravity() { return _gravity; }
	void SetGravity(bool val) { _gravity = val; }
	bool IsMoving() { if (_vel.x() != 0 || _vel.y() != 0 || _vel.z() != 0)return true; else return false; }
public:
	Vector4 Clamp(Vector4 vec, float min, float max);
	float Clamp(float numb, float min, float max);
};

