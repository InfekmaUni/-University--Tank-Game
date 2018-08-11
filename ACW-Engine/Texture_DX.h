#pragma once
#include "Texture.h"
#include "Renderer_DX.h"

#include <d3d11.h>
#include <directxmath.h>
#include "DDSTextureLoader.h"

namespace GameEngine
{
	class Texture_DX : public Texture
	{
	public:
		Texture_DX(std::string name);
		~Texture_DX() = default;

		// data
	protected:
		ID3D11ShaderResourceView* _textureRV;

		// getters & Setters
	public:
		ID3D11ShaderResourceView * GetTexture() { return _textureRV; }

		// functions
	public:
		virtual void Bind(Renderer* renderer, int startSlot, int numText);
		virtual void Shutdown();
		virtual void Create(Renderer* renderer);
	};
}