#pragma once
#include "Renderer.h"
#include <vector>
#include <DirectXMath.h>

namespace GameEngine
{

	struct SimpleVertexType {
		float x, y, z;
	};

	struct SimpleVertex
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 Tex;

	};

	class VIBO
	{
	public:
		VIBO() : _numVertices(0)
		{}
		virtual ~VIBO() = default;

		// data
	protected:
		int _numVertices;
		int _numIndices;

		// getters & setters
	public:
		virtual void Create(Renderer* renderer, std::vector<SimpleVertex> vertices, std::vector<unsigned short> indices) = 0;
		virtual void Draw(Renderer* renderer) = 0;
		virtual void Shutdown() = 0;
	};
}