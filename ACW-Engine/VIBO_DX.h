#pragma once
#include "VIBO.h"
#include "Vector4.h"
#include "Renderer_DX.h"

// dx headers
#include <d3d11.h>


namespace GameEngine
{

	class VIBO_DX : public VIBO
	{
	public:
		VIBO_DX()
		{}
		~VIBO_DX() = default;

		// data
	private:
		ID3D11Buffer* _vbo;
		ID3D11Buffer* _ibo;

		// getters
	public:
		ID3D11Buffer const* GetVBO() { return _vbo; }
		ID3D11Buffer const* GetIBO() { return _ibo; }

		// functions
	public:
		virtual void Create(Renderer* renderer, std::vector<SimpleVertex> vertices, std::vector<unsigned short> indices);
		virtual void Draw(Renderer* renderer);
		virtual void Shutdown();
	};
}