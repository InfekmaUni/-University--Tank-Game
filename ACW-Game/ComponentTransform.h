#pragma once
#include "Vector4.h"
#include "Component.h"
#include <DirectXMath.h>

class Component;
class ComponentTransform : public  GameEngine::Component
{
public:
	ComponentTransform(GameEngine::Entity* ent, Vector4 pos = Vector4(0, 0, 0), Vector4 rot = Vector4(0, 0, 0), Vector4 scale = Vector4(1, 1, 1)) : Component("TRANSFORM_COMPONENT", ent), _position(pos), _rotation(rot), _scale(scale)
	{
		_init = true;
		ReconstructModelSpace();
	}
	~ComponentTransform() = default;
	//ComponentTransform& operator=(const ComponentTransform& toCopy);

	// data
private:
	Vector4 _position;
	Vector4 _oldPosition;
	Vector4 _rotation;
	Vector4 _scale; // stored as radians
	DirectX::XMMATRIX _modelSpace;

	// getters & setters
public:
	DirectX::XMMATRIX GetModelSpace() { ReconstructModelSpace(); return _modelSpace; }
	Vector4 GetOldPosition() { return _oldPosition; }
	Vector4 GetPosition() { return _position; }
	void SetPosition(const Vector4 newPosition) { _oldPosition = _position; _position.set(newPosition); ReconstructModelSpace(); }
	void AddPosition(const Vector4 addPosition) { _oldPosition = _position; _position.add(addPosition); ReconstructModelSpace(); }

	Vector4 GetRotation() { return _rotation; }
	void SetRotation(const Vector4 newRotation) { _rotation.set(newRotation); ReconstructModelSpace(); }
	void AddRotation(const Vector4 addRotation) { _rotation.add(addRotation);  ReconstructModelSpace(); }

	Vector4 GetScale() { return _scale; }
	void SetScale(const Vector4 newScale) { _scale.set(newScale);  ReconstructModelSpace(); }
	void AddScale(const Vector4 addScale) { _scale.add(addScale);  ReconstructModelSpace(); }

public:
	void ReconstructModelSpace();
};