#include "RenderedEntity.h"

#include "SceneShader.h"
#include "GameScene.h"

RenderedEntity::RenderedEntity(std::string meshName, std::string textureName) : Entity()
{
	_transformComp = new ComponentTransform(this);
	_meshComp = new ComponentMesh(this, meshName);

	_renderComp = new ComponentRender(this, GameScene::myGameScene->GetSceneShader(), GameScene::myGameScene->GetSceneShader()->GetVertexShaderName(), GameScene::myGameScene->GetSceneShader()->GetPixelShaderName());
	_textureComp = new ComponentTexture(this, textureName);
}