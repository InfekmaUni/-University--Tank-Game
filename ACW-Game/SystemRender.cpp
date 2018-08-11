#include "SystemRender.h"

// components

using namespace GameEngine;

void SystemRender::Initialise()
{
	_rManager = (ResourceManager*)Game::myGame->GetManager("ResourceManager");
	_placeHolderEnt = new Entity(false);
}

void SystemRender::Shutdown()
{
}

const std::string RENDER_MASK[3] = { "TRANSFORM_COMPONENT", "MESH_COMPONENT", "RENDER_COMPONENT" };
const std::string CAMERA_MASK[1] = { "CAMERA_COMPONENT" };
const std::string TEXTURE_MASK[1] = { "TEXTURE_COMPONENT" };

void SystemRender::OnMessage(Message* msg)
{
	int y = 0;
}

//void SystemRender::Render(Renderer* renderer)
//{
//	EntityManager* entManager = (EntityManager*)Game::myGame->GetManager("EntityManager");
//	std::vector<Entity*> entList = entManager->GetEntityList();
//	if (entList.size() <= 0)
//		return;
//
//	for (auto const& ent : entList)
//	{
//		Process(renderer, ent);
//	}
//}

void SystemRender::Render(Renderer* renderer, Entity* ent)
{
	if (_activeCamera == nullptr) // if theres no active camera
	{
		_activeCamera = new ComponentCamera(_placeHolderEnt);
		_defaultCamera = true;
	}

	bool hasTextureMask = ent->HasComponent(TEXTURE_MASK, (sizeof(TEXTURE_MASK) / sizeof(TEXTURE_MASK[0])));
	if (hasTextureMask)
	{
		ComponentTexture* textureComp = (ComponentTexture*)ent->GetComponent("TEXTURE_COMPONENT");
		Texture* texture = textureComp->GetTexture();
		if (!textureComp->IsInit()) // init texture
		{
			texture = _rManager->LoadTexture(renderer, textureComp->GetName());
			texture->Create(renderer);
			textureComp->SetTexture(texture);
			textureComp->SetInit(true);
		}
		texture->Bind(renderer, 0, 1); // slot 0 - 1 texture
	}

	bool hasRenderMask = ent->HasComponent(RENDER_MASK, (sizeof(RENDER_MASK) / sizeof(RENDER_MASK[0])));
	if (hasRenderMask)
	{
		RenderEntity(renderer, ent);
	}

	bool hasCameraMask = ent->HasComponent(CAMERA_MASK, (sizeof(CAMERA_MASK) / sizeof(CAMERA_MASK[0])));
	if (hasCameraMask)
	{
		ComponentCamera* cam = (ComponentCamera*)ent->GetComponent("CAMERA_COMPONENT");
		if (_defaultCamera) // remove default camera
		{
			delete _activeCamera;
			_activeCamera = nullptr;
			_defaultCamera = false;

			_activeCamera = cam;
		}
	}
}

void SystemRender::RenderEntity(Renderer* renderer, Entity* ent)
{
	ComponentMesh* mesh = (ComponentMesh*)ent->GetComponent("MESH_COMPONENT");
	if (!mesh->IsInit()) //not yet initialisd mesh
	{
		mesh->SetMesh(_rManager->LoadMesh(renderer, mesh->GetMeshName()));
		mesh->SetInit(true);
	}
	ComponentTransform* transform = (ComponentTransform*)ent->GetComponent("TRANSFORM_COMPONENT");
	ComponentRender* render = (ComponentRender*)ent->GetComponent("RENDER_COMPONENT");
	Shader* shader = render->GetShader();
	if ( !render->IsInit()) // not yet initialised
	{
		shader = _rManager->LoadShader(renderer, render->GetVShaderName(), render->GetPShaderName());
		render->SetShader(shader);
		render->SetInit(true);
	}
	
	if (_activeShader != shader)	// if not the same shader
	{
		_activeShader = shader;
		shader->Bind(renderer);
	}

	// update shader
	shader->Update(renderer, ent);

	// render shader
	shader->Render(renderer, ent);

	// get mesh buffer and draw
	VIBO* vibo = mesh->GetMesh()->GetVIBO();
	vibo->Draw(renderer);
}