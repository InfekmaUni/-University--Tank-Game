#include "SceneShader.h"

#include "SystemRender.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "Game.h"

#include "SystemManager.h"

void SceneShader::Initialise(GameEngine::Renderer* renderer)
{
	GameEngine::Renderer_DX* dxRender = (GameEngine::Renderer_DX*)renderer;

	Shader_DX::Initialise(renderer);

	CreateBuffer(dxRender, sizeof(ShaderConstBuffer));

	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);
	CreateInputLayout(dxRender, layout, numElements);
}

void SceneShader::Update(GameEngine::Renderer* renderer, GameEngine::Entity* ent)
{
	if (!_realInit)
	{
		Initialise(renderer);
		Bind(renderer);
		_realInit = true;
	}

	GameEngine::Renderer_DX* dxRender = (GameEngine::Renderer_DX*)renderer;
	GameEngine::SystemManager* manager = (GameEngine::SystemManager*)GameEngine::SceneManager::myScene->GetManagerByName("SystemManager");
	SystemRender* systemRender = (SystemRender*)manager->GetRenderSystem("SystemRender");

	ComponentTransform* transform = (ComponentTransform*)ent->GetComponent("TRANSFORM_COMPONENT");
	ComponentCamera* camera = systemRender->GetActiveCamera();

	if (camera != nullptr)
	{
		// update c buffer
		ShaderConstBuffer cBuffer = ShaderConstBuffer();
		cBuffer.model = DirectX::XMMatrixTranspose(transform->GetModelSpace());
		cBuffer.world = DirectX::XMMatrixTranspose(camera->GetWorld());
		cBuffer.projection = DirectX::XMMatrixTranspose(camera->GetProjection());
		cBuffer.view = DirectX::XMMatrixTranspose(camera->GetView());

		dxRender->GetContext()->UpdateSubresource(_cBuffers.at((int)BUFFER_ID::ShaderConstBuffer), 0, nullptr, &cBuffer, 0, 0);
	}
	else {
		std::cout << "Camera is null while trying to set buffers" << std::endl;
	}
}

void SceneShader::Render(GameEngine::Renderer* renderer, GameEngine::Entity* ent)
{
	GameEngine::Renderer_DX* dxRender = (GameEngine::Renderer_DX*)renderer;
	// after updating
}


void SceneShader::Shutdown()
{

}