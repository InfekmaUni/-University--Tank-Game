#include "VIBO_DX.h"

using namespace GameEngine;


void VIBO_DX::Create(Renderer* renderer, std::vector<SimpleVertex> vertices, std::vector<unsigned short> indices)
{
	_numVertices = vertices.size();
	_numIndices = indices.size();

	HRESULT hr;
	Renderer_DX* dxRender = (Renderer_DX*)renderer;

	// create vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * _numVertices;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &vertices[0];
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	hr = dxRender->GetDevice()->CreateBuffer(&bd, &InitData, &_vbo);
	if (FAILED(hr))
	{
		std::cout << "Failed to create Vertex Buffer Object for mesh" << std::endl;
	}
	// Create index buffex
	D3D11_BUFFER_DESC bd1;
	ZeroMemory(&bd1, sizeof(bd1));
	bd1.Usage = D3D11_USAGE_DEFAULT;
	bd1.ByteWidth = sizeof(unsigned short) * _numIndices;
	bd1.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd1.CPUAccessFlags = 0;
	bd1.MiscFlags = 0;
	InitData.pSysMem = &indices.at(0);
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = dxRender->GetDevice()->CreateBuffer(&bd1, &InitData, &_ibo);
	if (FAILED(hr))
	{
		std::cout << "Failed to create Index Buffer Object for mesh" << std::endl;
	}
}

void VIBO_DX::Shutdown()
{
	_ibo->Release();
	_ibo = 0;

	_vbo->Release();
	_vbo = 0;
}

void VIBO_DX::Draw(Renderer* renderer)
{
	Renderer_DX* dxRender = (Renderer_DX*)renderer;
	ID3D11DeviceContext* context = dxRender->GetContext();

	const unsigned stride = sizeof(SimpleVertex);
	const unsigned offset = 0;
	context->IASetVertexBuffers(0, 1, &_vbo, &stride, &offset);

	// Set primitive topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Set index buffer
	context->IASetIndexBuffer(_ibo, DXGI_FORMAT_R16_UINT, 0);

	// Set primitive topology
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw
	context->DrawIndexed(_numIndices, 0, 0);
}