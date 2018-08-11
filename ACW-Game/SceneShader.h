#pragma once
#include "Shader_DX.h"

// buffer
struct ShaderConstBuffer
{
	DirectX::XMMATRIX model;
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX view;
};

enum class BUFFER_ID
{
	ShaderConstBuffer = 0,
};

class SceneShader : public GameEngine::Shader_DX
{
public:
	SceneShader(std::string vName, std::string pName) : GameEngine::Shader_DX(vName, pName)
	{}

	~SceneShader() = default;

	private:
		bool _realInit = false;

	public:

		// functions
	public:
		virtual void Initialise(GameEngine::Renderer* renderer);
		virtual void Shutdown();
		virtual void Update(GameEngine::Renderer* renderer, GameEngine::Entity* ent);
		virtual void Render(GameEngine::Renderer* renderer, GameEngine::Entity* ent);
};

