#pragma once
#include <vector>

// dx
#include "VIBO_DX.h"
#include "Shader_DX.h"
#include "Texture_DX.h"

#include "Mesh.h"
#include "BaseManager.h"
#include "OBJLoader.h"
#include "Shader.h"
#include "Texture.h"

namespace GameEngine
{
	class ResourceManager : public BaseManager
	{
	public:
		ResourceManager() : BaseManager("ResourceManager")
		{}
		~ResourceManager() = default;

		// data
	private:
		std::vector<Mesh*> _meshes;
		std::vector<Shader*> _shaders;
		std::vector<Texture*> _textures;

		// functions
	public:
		Mesh* LoadMesh(Renderer* renderer, std::string name);
		Mesh* CheckExistingMesh(std::string name);

		Shader* LoadShader(Renderer* renderer, std::string vName, std::string pName);
		Shader* CheckExistingShader(std::string vName, std::string pName);

		Texture* LoadTexture(Renderer* renderer, std::string name);
		Texture* CheckExistingTexture(std::string name);

		void Update(float dt);
		void Render();
		void Shutdown();
		void Initialise();
	};
}
