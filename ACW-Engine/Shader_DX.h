#pragma once
#include "Shader.h"
#include "Renderer_DX.h"
#include "VIBO.h"

namespace GameEngine
{
	class Shader_DX : public Shader
	{
	public:
		Shader_DX(std::string vName, std::string pName);
		Shader_DX(std::string vName, std::string pName, std::string vEntry, std::string pEntry, std::string vModel, std::string pModel);
		~Shader_DX() = default;

		// data
	protected:
		// shader data
		ID3DBlob* _VSBlob = nullptr;
		ID3DBlob* _PSBlob = nullptr;
		ID3D11VertexShader* _vertexShader = nullptr;
		ID3D11PixelShader* _pixelShader = nullptr;
		ID3D11InputLayout* _vertexLayout = nullptr;	
		ID3D11SamplerState* _sampleState = nullptr;
		
		std::vector<ID3D11Buffer*> _cBuffers;

		// rasterizer
		D3D11_RASTERIZER_DESC _rasterDesc;
		ID3D11RasterizerState*	_rasterizer = nullptr;

		// getters & setters
	public:
		ID3D11Buffer * GetCBuffer(int id) 
		{
			if (_cBuffers.size() < static_cast<unsigned>(id)) return nullptr; 
			else return _cBuffers.at(id); 
		}
		ID3D11VertexShader* GetVertexShader() const { return _vertexShader; }
		ID3D11PixelShader* GetPixelShader() const { return _pixelShader; }

		// functions
	public:
		virtual void Initialise(Renderer* renderer);
		virtual void Shutdown();
		virtual void Bind(Renderer* renderer);
		virtual void Update(Renderer* renderer, Entity* ent) {}
		virtual void Render(Renderer* renderer, Entity* ent) {}

		virtual void BindBuffers(Renderer_DX* renderer);
		virtual void BindShaders(Renderer_DX* renderer);
		virtual void CreateInputLayout(Renderer_DX* renderer, const D3D11_INPUT_ELEMENT_DESC* const layout, const UINT numElements);
		
		void CreateShader(Renderer_DX* dxRender, std::string vName, std::string pName);
		ID3D11Buffer* CreateBuffer(Renderer_DX* dxRender, const unsigned size);
		HRESULT CompileShaderFromFile(const WCHAR* const szFileName, const LPCSTR szEntryPoint, const LPCSTR szShaderModel, ID3DBlob** const ppBlobOut);
	};
}