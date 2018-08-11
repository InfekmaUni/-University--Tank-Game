#pragma once
#include "Entity.h"
#include "EntityManager.h"
#include "ComponentTexture.h"
#include "ComponentRender.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"

class RenderedEntity : public GameEngine::Entity
{
public:
	RenderedEntity(std::string meshName, std::string textureName);
	~RenderedEntity() = default;

protected:
	ComponentTransform* _transformComp;
	ComponentMesh* _meshComp;
	ComponentRender* _renderComp;
	ComponentTexture* _textureComp;

public:
	Vector4 GetPosition() { return _transformComp->GetPosition(); }
	void SetPosition(Vector4 newPos) { _transformComp->SetPosition(newPos); }

	Vector4 GetRotation() { return _transformComp->GetRotation(); }
	void SetRotation(Vector4 newRot) { _transformComp->SetRotation(newRot); }
	void AddRotation(Vector4 addRot) { _transformComp->AddRotation(addRot); }

	Vector4 GetScale() { return _transformComp->GetScale(); }
	void SetScale(Vector4 newScale) { _transformComp->SetScale(newScale); }


public:
	virtual void OnUpdate(float dt) {}
	virtual void OnRender() {}
	virtual void OnShutdown() {}
	virtual void OnInitialise() {}
	virtual void OnMessage(GameEngine::Message* msg) { Entity::OnMessage(msg); }
};

