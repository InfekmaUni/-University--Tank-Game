#pragma once
#include "Renderer.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include "ApplicationWindow_DX.h"
#include <iostream>

namespace GameEngine
{
	class Renderer_DX : public Renderer
	{
	public:
		Renderer_DX(HWND hwnd) : Renderer(), _hWND(hwnd)
		{}
		~Renderer_DX() = default;

		// data
	private:
		D3D_DRIVER_TYPE * _driverType = nullptr;
		D3D_FEATURE_LEVEL       _featureLevel = D3D_FEATURE_LEVEL_11_0;
		ID3D11Device*           _d3dDevice = nullptr;
		ID3D11DeviceContext*    _immediateContext = nullptr;
		IDXGISwapChain*         _swapChain = nullptr;
		ID3D11RenderTargetView* _renderTargetView = nullptr;
		ID3D11Texture2D*        _depthStencil = nullptr;
		ID3D11DepthStencilView* _depthStencilView = nullptr;
		int _height = 0; int _width = 0;

		HWND _hWND; // window handle

		// getters & setters
	public:
		ID3D11Device * GetDevice() const { return _d3dDevice; }
		ID3D11DeviceContext* GetContext() const { return _immediateContext; }

		// functions
	public:
		virtual void Initialise(int width, int height);
		virtual void Shutdown();
		virtual void ClearScreen();
		virtual void SwapBuffers();
	};
}
