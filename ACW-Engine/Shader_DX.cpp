#include "Shader_DX.h"

using namespace GameEngine;

Shader_DX::Shader_DX(std::string vName, std::string pName) : Shader(vName, pName)
{}

Shader_DX::Shader_DX(std::string vName, std::string pName, std::string vEntry, std::string pEntry, std::string vModel, std::string pModel) 
: Shader(vName, pName, vEntry, pEntry, vModel, pModel)
{}

void Shader_DX::Initialise(Renderer* renderer)
{
	Renderer_DX* dxRender = (Renderer_DX*)renderer;
	CreateShader(dxRender, _vName, _pName);
	
	// rasterizer description
	_rasterDesc.CullMode = D3D11_CULL_NONE;
	_rasterDesc.FillMode = D3D11_FILL_SOLID;
	_rasterDesc.ScissorEnable = false;
	_rasterDesc.DepthBias = 0;
	_rasterDesc.DepthBiasClamp = 0.0f;
	_rasterDesc.DepthClipEnable = true;
	_rasterDesc.MultisampleEnable = false;
	_rasterDesc.SlopeScaledDepthBias = 0.0f;

	if (FAILED(dxRender->GetDevice()->CreateRasterizerState(&_rasterDesc, &_rasterizer))) {
		std::cout << "Failed to init rasterizer" << std::endl;
		return;
	}

	// sampler
	D3D11_SAMPLER_DESC samplerDesc;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	HRESULT result = dxRender->GetDevice()->CreateSamplerState(&samplerDesc, &_sampleState);
	if (FAILED(result))
	{
		std::cout << "Error initilisaing sampler wrap" << std::endl;
		return;
	}
}

void Shader_DX::Shutdown()
{
	_VSBlob->Release();  _VSBlob = 0;
	_PSBlob->Release();  _PSBlob = 0;

	_vertexShader->Release(); _vertexShader = 0;
	_pixelShader->Release();  _pixelShader = 0;

	_vertexLayout->Release(); _vertexLayout = 0;
	//_cBuffer->Release(); _cBuffer = 0;
	for (auto& buffer : _cBuffers)
	{
		buffer->Release();
		delete buffer;
		buffer = 0;
	}

	_sampleState->Release(); _sampleState = 0;
	_rasterizer->Release();_rasterizer = 0;
}

void Shader_DX::CreateInputLayout(Renderer_DX* renderer, const D3D11_INPUT_ELEMENT_DESC* const layout, const UINT numElements)
{
	// Create the input layout
	HRESULT hr = renderer->GetDevice()->CreateInputLayout(layout, numElements, _VSBlob->GetBufferPointer(),
		_VSBlob->GetBufferSize(), &_vertexLayout);

	if (FAILED(hr))
	{
		std::cout << "Failed to create vertex input layout" << std::endl;
	}
}

void Shader_DX::Bind(Renderer* renderer)
{
	Renderer_DX* dxRender = (Renderer_DX*)renderer;

	dxRender->GetContext()->RSSetState(_rasterizer);	// set rasterizer state
	dxRender->GetContext()->PSSetSamplers(0, 1, &_sampleState);	// set samplerState

	BindShaders(dxRender);
	BindBuffers(dxRender);
}

void Shader_DX::BindShaders(Renderer_DX* renderer)
{
	// set/switch shaders
	renderer->GetContext()->VSSetShader(_vertexShader, 0, 0);
	renderer->GetContext()->PSSetShader(_pixelShader, 0, 0);

	renderer->GetContext()->IASetInputLayout(_vertexLayout);	// Set the input layout
}

void Shader_DX::BindBuffers(Renderer_DX* renderer)
{
	// set c buffers for pixel and vertex shader
	int counter = 0;
	for (auto& buffer : _cBuffers)
	{
		renderer->GetContext()->PSSetConstantBuffers(counter, 1, &_cBuffers.at(counter));
		renderer->GetContext()->VSSetConstantBuffers(counter, 1, &_cBuffers.at(counter));
		counter++;
	}

}

ID3D11Buffer* Shader_DX::CreateBuffer(Renderer_DX* dxRender, const unsigned size)
{
	ID3D11Buffer* buffer;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT hr = dxRender->GetDevice()->CreateBuffer(&bd, nullptr, &buffer);
	if (FAILED(hr))
	{
		std::cout << "Failed to create Constant Buffer" << std::endl;
	}

	_cBuffers.push_back(buffer);
	return _cBuffers.back();
};

void Shader_DX::CreateShader(Renderer_DX* dxRender, std::string vName, std::string pName)
{
	HRESULT hr; HRESULT hr1;
	// convert string to wchar
	std::wstring wideVName = std::wstring(vName.begin(), vName.end());
	const wchar_t* vertexName = wideVName.c_str();
	// Create the vertex shader
	hr = CompileShaderFromFile(vertexName, "VS", "vs_4_0", &_VSBlob);
	hr1 = dxRender->GetDevice()->CreateVertexShader(_VSBlob->GetBufferPointer(), _VSBlob->GetBufferSize(), nullptr, &_vertexShader);
	if (FAILED(hr || hr1))
	{
		std::cout << "Failed to create vertex shader" << std::endl;
	}

	std::wstring widePName = std::wstring(pName.begin(), pName.end());
	const wchar_t* pixelName = widePName.c_str();
	// Create the pixel shader
	hr = CompileShaderFromFile(pixelName, "PS", "ps_4_0", &_PSBlob);
	hr1 = dxRender->GetDevice()->CreatePixelShader(_PSBlob->GetBufferPointer(), _PSBlob->GetBufferSize(), nullptr, &_pixelShader);
	if (FAILED(hr || hr1))
	{
		std::cout << "Failed to create pixel shader" << std::endl;
	}
}

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DCompile
//
// With VS 11, we could load up prebuilt .cso files instead...
//--------------------------------------------------------------------------------------
HRESULT Shader_DX::CompileShaderFromFile(const WCHAR* const szFileName, const LPCSTR szEntryPoint, const LPCSTR szShaderModel, ID3DBlob** const ppBlobOut)
{
	HRESULT hr = TRUE;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, const_cast<ID3DBlob**>(ppBlobOut), &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return TRUE;
}