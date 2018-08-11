#pragma once
#include <string>
#include "Renderer.h"
#include "Entity.h"

namespace GameEngine
{
	const std::string VS_SHADER_MODEL = "vs_4_0";
	const std::string PS_SHADER_MODEL = "ps_4_0";

	const std::string VS_ENTRYPOINT = "VS";
	const std::string PS_ENTRYPOINT = "PS";

	class Shader
	{
	public:
		Shader(std::string vName, std::string pName);
		Shader(std::string vName, std::string pName, std::string vEntry, std::string pEntry, std::string vModel, std::string pModel);
		~Shader() = default;

		// data
	protected:
		// shader names
		std::string _vName;
		std::string _pName;

		// entry point
		std::string _vEntryPoint;
		std::string _pEntryPoint;

		// shader model
		std::string _vShaderModel;
		std::string _pShaderModel;

		// getters & setters
	public:
		std::string GetVertexShaderName() { return _vName; }
		std::string GetPixelShaderName() { return _pName; }

		// functions
	public:
		virtual void Initialise(Renderer* renderer) = 0;
		virtual void Shutdown() = 0;
		virtual void Bind(Renderer* renderer) = 0;
		virtual void Update(Renderer* renderer, Entity* ent) = 0;
		virtual void Render(Renderer* renderer, Entity* ent) = 0;
	};
}