#include "Texture_DX.h"

using namespace GameEngine;

Texture_DX::Texture_DX(std::string name) : Texture(name)
{
}

void Texture_DX::Shutdown()
{
	_textureRV->Release(); _textureRV = 0;
}

void Texture_DX::Create(Renderer* renderer)
{
	Renderer_DX* dxRender = (Renderer_DX*)renderer;

	std::string texturePath = "Textures/"+_textureName+".dds";
	std::wstring wideTName = std::wstring(texturePath.begin(), texturePath.end());
	const wchar_t* textureName = wideTName.c_str();

	//// Load the Texture
	HRESULT hr = DirectX::CreateDDSTextureFromFile(dxRender->GetDevice(), textureName, nullptr, &_textureRV);
	if (FAILED(hr)) {
		std::cout << "Failed to create texture" << std::endl;
	}
}

void Texture_DX::Bind(Renderer* renderer, int startSlot, int numText)
{
	Renderer_DX* dxRender = (Renderer_DX*)renderer;
	dxRender->GetContext()->PSSetShaderResources(startSlot, numText, &_textureRV);
}