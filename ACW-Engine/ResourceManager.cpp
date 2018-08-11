#include "ResourceManager.h"

using namespace GameEngine;

void ResourceManager::Update(float dt){}
void ResourceManager::Render(){}
void ResourceManager::Initialise(){}

void ResourceManager::Shutdown()
{
	// clear meshes
	for (auto& mesh : _meshes)
	{
		mesh->Shutdown();
		delete mesh;
		mesh = 0;
	}
	_meshes.clear();

	// clear textures
	for (auto& texture : _textures)
	{
		texture->Shutdown();
		delete texture;
		texture = 0;
	}
	_textures.clear();

	// clear shaders
	for (auto& shader : _shaders)
	{
		shader->Shutdown();
		delete shader;
		shader = 0;
	}
	_shaders.clear();
}

Texture* ResourceManager::LoadTexture(Renderer* renderer, std::string name)
{
	Texture* texture = CheckExistingTexture(name);

	if (texture == nullptr) // mesh does not exist > create
	{
		// if DX
		texture = new Texture_DX(name);
		texture->Create(renderer);
		_textures.push_back(texture);

		// if GL
		//
	}
	return texture;
}

Texture* ResourceManager::CheckExistingTexture(std::string name)
{
	for (auto const& texture : _textures)
	{
		if (texture->GetName() == name)
			return texture;
	}
	return nullptr;
}

Shader* ResourceManager::LoadShader(Renderer* renderer, std::string vName, std::string pName)
{
	Shader* shader = CheckExistingShader(vName, pName);

	if (shader == nullptr) // mesh does not exist > create
	{
		// if DX
		shader = new Shader_DX(vName, pName);
		shader->Initialise(renderer);
		_shaders.push_back(shader);

		// if GL
		//
	}
	return shader;
}

Shader* ResourceManager::CheckExistingShader(std::string vName, std::string pName)
{
	for (auto const& shader : _shaders)
	{
		if (shader->GetPixelShaderName() == pName && shader->GetVertexShaderName() == vName)
			return shader;
	}
	return nullptr;
}

Mesh* ResourceManager::LoadMesh(Renderer* renderer, std::string name)
{
	Mesh* mesh = CheckExistingMesh(name); // check if mesh already exist
	if (mesh == nullptr) // mesh does not exist > create
	{
		OBJLoader* loader = new OBJLoader(name);
		mesh = new Mesh(name);

		// if dx
		VIBO_DX* vibo = new VIBO_DX();
		vibo->Create(renderer, loader->GetVertices(), loader->GetIndices());

		// if gl
		//

		mesh->SetVIBO(vibo);
		_meshes.push_back(mesh);
	}
	return mesh;
}

Mesh* ResourceManager::CheckExistingMesh(std::string name)
{
	for (auto const& mesh : _meshes)
	{
		if (mesh->GetName() == name)
			return mesh;
	}
	return nullptr;
}