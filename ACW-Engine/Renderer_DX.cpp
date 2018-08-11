#include "Renderer_DX.h"
using namespace GameEngine;

void Renderer_DX::Initialise(int width, int height)
{
	_height = height;
	_width = width;

	HRESULT hr;
	// create a struct to hold information about the swap chain
	//DXGI_SWAP_CHAIN_DESC scd;

	//// clear out the struct for use
	//ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	//// fill the swap chain description struct
	//scd.BufferCount = 1;                                   // one back buffer
	//scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
	//scd.BufferDesc.Width = width;                   // set the back buffer width
	//scd.BufferDesc.Height = height;                 // set the back buffer height
	//scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
	//scd.OutputWindow = _hWND;                             // the window to be used
	//scd.SampleDesc.Count = 4;                              // how many multisamples
	//scd.Windowed = TRUE;                                   // windowed/full-screen mode
	//scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

	//													   // create a device, device context and swap chain using the information in the scd struct
	//hr = D3D11CreateDeviceAndSwapChain(NULL,
	//	D3D_DRIVER_TYPE_HARDWARE,
	//	NULL,
	//	NULL,
	//	NULL,
	//	NULL,
	//	D3D11_SDK_VERSION,
	//	&scd,
	//	&_swapChain,
	//	&_d3dDevice,
	//	NULL,
	//	&_immediateContext);
	//if (FAILED(hr))
	//{
	//	std::cout << "failed to create swap chain" << std::endl;
	//	return;
	//}
	//// get the address of the back buffer
	//ID3D11Texture2D *p_backbuffer;
	//hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&p_backbuffer);
	//if (FAILED(hr))
	//{
	//	std::cout << "failed to get backbuffer" << std::endl;
	//	return;
	//}

	//hr = _d3dDevice->CreateRenderTargetView(p_backbuffer, nullptr, &_renderTargetView);
	//p_backbuffer->Release();

	//if (FAILED(hr))
	//{
	//	std::cout << "failed to create Render Target View" << std::endl;
	//	return;
	//}

	////// Create depth stencil texture
	////D3D11_TEXTURE2D_DESC descDepth;
	////ZeroMemory(&descDepth, sizeof(descDepth));
	////descDepth.Width = width;
	////descDepth.Height = height;
	////descDepth.MipLevels = 1;
	////descDepth.ArraySize = 1;
	////descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	////descDepth.SampleDesc.Count = 1;
	////descDepth.SampleDesc.Quality = 0;
	////descDepth.Usage = D3D11_USAGE_DEFAULT;
	////descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	////descDepth.CPUAccessFlags = 0;
	////descDepth.MiscFlags = 0;
	////hr = _d3dDevice->CreateTexture2D(&descDepth, nullptr, &_depthStencil);

	////if (FAILED(hr))
	////{
	////	std::cout << "failed to create Depth Stencil" << std::endl;
	////	return;
	////}

	////// Create the depth stencil view
	////D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	////ZeroMemory(&descDSV, sizeof(descDSV));
	////descDSV.Format = descDepth.Format;
	////descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	////descDSV.Texture2D.MipSlice = 0;
	////hr = _d3dDevice->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView);

	////if (FAILED(hr))
	////{
	////	std::cout << "failed to create Depth Stencil View" << std::endl;
	////	return;
	////}

	//// set render target
	//_immediateContext->OMSetRenderTargets(1, &_renderTargetView, NULL);

	//// Setup the viewport
	//D3D11_VIEWPORT vp;
	//ZeroMemory(&vp, sizeof(D3D11_VIEWPORT));
	//vp.Width = width;
	//vp.Height = height;
	//vp.TopLeftX = 0;
	//vp.TopLeftY = 0;
	//vp.MinDepth = 0.0f;
	//vp.MaxDepth = 1.0f;
	//_immediateContext->RSSetViewports(1, &vp);

	UINT createDeviceFlags = 0;
	#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
	{
		_driverType = &driverTypes[driverTypeIndex];
		hr = D3D11CreateDevice(nullptr, *_driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &_d3dDevice, &_featureLevel, &_immediateContext);

		if (hr == 0x80070057L) // E_INVALIDARG 
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, *_driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, &_d3dDevice, &_featureLevel, &_immediateContext);
		}

		if (SUCCEEDED(hr))
			break;
	}
	if (FAILED(hr))
		return;

	// Obtain DXGI factory from device (since we used nullptr for pAdapter above)
	IDXGIFactory1* dxgiFactory = nullptr;
	{
		IDXGIDevice* dxgiDevice = nullptr;
		hr = _d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice));
		if (SUCCEEDED(hr))
		{
			IDXGIAdapter* adapter = nullptr;
			hr = dxgiDevice->GetAdapter(&adapter);
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(&dxgiFactory));
				adapter->Release();
			}
			dxgiDevice->Release();
		}
	}
	if (FAILED(hr))
		return;

	// Create Swap Chain (works for dx11 only)
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWND;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = dxgiFactory->CreateSwapChain(_d3dDevice, &sd, &_swapChain);

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(_hWND, DXGI_MWA_NO_ALT_ENTER);

	dxgiFactory->Release();

	if (FAILED(hr))
		return;

	// Create a render target view
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	if (FAILED(hr))
		return;

	hr = _d3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &_renderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return;

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC descDepth;
	ZeroMemory(&descDepth, sizeof(descDepth));
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = _d3dDevice->CreateTexture2D(&descDepth, nullptr, &_depthStencil);
	if (FAILED(hr))
		return;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	hr = _d3dDevice->CreateDepthStencilView(_depthStencil, &descDSV, &_depthStencilView);
	if (FAILED(hr))
		return;

	_immediateContext->OMSetRenderTargets(1, &_renderTargetView, _depthStencilView);

	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	_immediateContext->RSSetViewports(1, &vp);
}

void Renderer_DX::Shutdown()
{
	if (_depthStencil) _depthStencil->Release(); _depthStencil = nullptr;
	if (_depthStencilView) _depthStencilView->Release(); _depthStencilView = nullptr;
	if (_renderTargetView) _renderTargetView->Release(); _renderTargetView = nullptr;
	if (_swapChain) _swapChain->Release(); _swapChain = nullptr;
	if (_immediateContext) _immediateContext->Release(); _immediateContext = nullptr;
	if (_d3dDevice) _d3dDevice->Release(); _d3dDevice = nullptr;
}

void Renderer_DX::ClearScreen()
{
	float color[4] = { _clearColor.r(), _clearColor.g(), _clearColor.b(), _clearColor.a() }; // clear
	_immediateContext->ClearRenderTargetView(_renderTargetView, color);
	_immediateContext->ClearDepthStencilView(_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}

void Renderer_DX::SwapBuffers()
{
	_swapChain->Present(0, 0);
}