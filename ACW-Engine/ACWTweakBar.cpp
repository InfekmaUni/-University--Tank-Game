#include "ACWTweakBar.h"

#include "ApplicationWindow.h"
#include "Renderer_DX.h"

using namespace GameEngine;

ACWTweakBar::ACWTweakBar()
{
}

ACWTweakBar::~ACWTweakBar()
{}

int ACWTweakBar::CreateNewBar(std::string barName, int pos[2], int size[2])
{
	TwBar* newBar = TwNewBar(barName.c_str());

	TwSetParam(newBar, nullptr, "position", TW_PARAM_INT32, 2, pos);
	TwSetParam(newBar, nullptr, "size", TW_PARAM_INT32, 2, size);
	//TwDefine(" System refresh=0.5 "); // increase refresh rate
	std::string define = barName + std::string(" visible = true ");
	TwDefine(define.c_str());

	_tweakBars.push_back(newBar);

	return _tweakBars.size() - 1;
}

void ACWTweakBar::CreateVarRWInt(int id, std::string varName, ETwType type, int* val, std::string extra, std::string defineVal)
{
	TwRemoveVar(_tweakBars.at(id), varName.c_str());
	TwAddVarRW(_tweakBars.at(id), varName.c_str(), type, &val, extra.c_str());
	TwDefine(defineVal.c_str());
}

void ACWTweakBar::CreateVarRWFloat(int id, std::string varName, ETwType type, float* val, std::string extra, std::string defineVal)
{
	TwRemoveVar(_tweakBars.at(id), varName.c_str());
	TwAddVarRW(_tweakBars.at(id), varName.c_str(), type, &val, extra.c_str());
	TwDefine(defineVal.c_str());
}

void ACWTweakBar::Initialise(Renderer* renderer)
{
	// DX setup
	// initialise tweakbar
	Renderer_DX* dxRender = (Renderer_DX*)renderer;
	TwInit(TW_DIRECT3D11, dxRender->GetDevice());

	// set tweakbar window size
	TwWindowSize(ApplicationWindow::Window->GetWidth(), ApplicationWindow::Window->GetHeight()); // set tweakbar window
	TwDefine(" GLOBAL fontsize=2 ");
	TwDefine(" GLOBAL refresh=0.2 ");

	//_sceneBar = TwNewBar("Scene"); // create twarkbar bar
	//_systemBar = TwNewBar("System");

	//int objectBarSize[2] = { 250,350 };
	//int objectBarPos[2] = { 0, 0 };
	//TwSetParam(_systemBar, nullptr, "size", TW_PARAM_INT32, 2, objectBarSize);
	//TwSetParam(_systemBar, nullptr, "position", TW_PARAM_INT32, 2, objectBarPos);
	//TwDefine(" System refresh=0.5 "); // increase refresh rate

	//TwAddVarRW(_systemBar, "FPS", TW_TYPE_FLOAT, const_cast<float*>(&system->GetFPS()), " ");
	//TwDefine(" System/FPS readonly=true ");
	//TwAddVarRW(_systemBar, "ElapsedTime", TW_TYPE_INT8, const_cast<float*>(&system->GetProgramLifeTime()), " ");
	//TwDefine(" System/ElapsedTime readonly=true ");
	//TwAddVarRW(_systemBar, "TimestepMultiplier", TW_TYPE_FLOAT, const_cast<float*>(&system->GetCurrentTimeMultiplier()), " ");

	//int barSize[2] = { 224,320 };
	//int objectPos[2] = { 275, 0 };
	//TwSetParam(_sceneBar, nullptr, "size", TW_PARAM_INT32, 2, barSize);
	//TwSetParam(_sceneBar, nullptr, "position", TW_PARAM_INT32, 2, objectPos);

	//TwDefine(" GLOBAL fontsize=2 ");
	////
	//// types
	////
	//TwStructMember vector[] =
	//{
	//	{ "x", TW_TYPE_FLOAT, offsetof(XMFLOAT3, x), " step=0.5 " },
	//	{ "y", TW_TYPE_FLOAT, offsetof(XMFLOAT3, y), " step=0.5 " },
	//	{ "z", TW_TYPE_FLOAT, offsetof(XMFLOAT3, z), " step=0.5 " },
	//};

	//const TwType vectorType = TwDefineStruct("Vector", vector, 3, sizeof(XMFLOAT3), nullptr, nullptr); // cry vector type

	//// renderable object type
	//TwStructMember lightMembers[] =
	//{
	//	{ "Position", vectorType, offsetof(SpotLight, Pos), " " },
	//	{ "Direction", TW_TYPE_DIR3F, offsetof(SpotLight, Dir), " " },
	//	{ "Color", TW_TYPE_COLOR4F, offsetof(SpotLight, Color), " " },
	//	{ "Attenuation", vectorType, offsetof(SpotLight, Attenuation), " " },
	//	{ "Range", TW_TYPE_FLOAT, offsetof(SpotLight, Range), " " },
	//	{ "ConeSize", TW_TYPE_FLOAT, offsetof(SpotLight, ConeSize), " " },
	//	//{ "Intensity", TW_TYPE_FLOAT, offsetof(SpotLight, Intensity), " " },

	//};
	//const TwType lightType = TwDefineStruct("Light", lightMembers, 6, sizeof(SpotLight), nullptr, nullptr); // cry vector type

	//std::vector<size_t> objectoffsets = RenderableObject::GetVariableOffsets();
	//// light type
	//TwStructMember renderObjectMembers[] =
	//{
	//	{ "Position", vectorType, objectoffsets.at(0), " " },
	//	{ "Rotation", vectorType, objectoffsets.at(1), " " },
	//	{ "Scale", vectorType, objectoffsets.at(2), " " },
	//	{ "Ambient", TW_TYPE_COLOR4F, objectoffsets.at(3), " " },
	//	{ "Diffuse", TW_TYPE_COLOR4F, objectoffsets.at(4), " " },
	//	{ "Specular", TW_TYPE_COLOR4F, objectoffsets.at(5), " " },
	//	{ "Shininess", TW_TYPE_COLOR4F, objectoffsets.at(6), " " },
	//};
	//const TwType renderObjectType = TwDefineStruct("RenderObject", renderObjectMembers, 7, sizeof(RenderableObject), nullptr, nullptr); // cry vector type

	//std::vector<size_t> particleOffsets = Particle::GetParticleVariablesOffsets();
	//TwStructMember particleObjectMembers[] =
	//{
	//	{ "Position", vectorType, objectoffsets.at(0), " " },
	//	{ "Velocity", TW_TYPE_DIR3F, particleOffsets.at(0), " " },
	//	{ "Amplification", TW_TYPE_FLOAT, particleOffsets.at(1), " " },
	//	{ "Lifespan", TW_TYPE_FLOAT, particleOffsets.at(2), " " },
	//	{ "Frequency", TW_TYPE_FLOAT, particleOffsets.at(3), " " },
	//	{ "GrowthRate", TW_TYPE_FLOAT, particleOffsets.at(4), " " },
	//	{ "Radius", TW_TYPE_FLOAT, particleOffsets.at(5), " " },
	//	{ "Height", TW_TYPE_FLOAT, particleOffsets.at(6), " " },
	//	{ "ParticleSize", TW_TYPE_FLOAT, particleOffsets.at(7), " " },
	//};
	//const TwType particleObjectType = TwDefineStruct("ParticleObject", particleObjectMembers, 9, sizeof(Particle), nullptr, nullptr); // cry vector type
	//
	////
	//// Active object
	////

	//for (unsigned i = 0; i < static_cast<unsigned>(objectList.size()); i++)
	//{
	//	if (objectList.at(i)->IsParticle()) // if particle
	//	{
	//		TwAddVarRW(_sceneBar, objectList.at(i)->GetName().c_str(), particleObjectType, &*objectList.at(i), " group='Particles' ");
	//	}
	//	else
	//	{
	//		TwAddVarRW(_sceneBar, objectList.at(i)->GetName().c_str(), renderObjectType, &*objectList.at(i), " group='RenderableObjects' ");
	//	}
	//}

	////
	////	Lights
	////
	//for (unsigned i = 0; i < static_cast<unsigned>(lightList.size()); i++)
	//{
	//	TwAddVarRW(_sceneBar, std::to_string(i).c_str(), lightType, &*lightList.at(i), " group='SpotLights' ");
	//}

	//ToggleTweakBar(); // hide;
}

void ACWTweakBar::ToggleTweakBar(std::string name, bool visible)
{

	if (visible)
	{
		std::string param = " visible='true' ";
		std::string final = name + param;
		TwDefine(final.c_str());
	}
	else
	{
		std::string param = " visible='false' ";
		std::string final = name + param;
		TwDefine(final.c_str());
	}

}

void ACWTweakBar::Shutdown() const
{
	TwTerminate(); // cleanup anttweakbar
	//delete _sceneObjects; _sceneObjects = 0;
	//delete _lightBar; _lightBar = 0;
	//delete _objectBar; _objectBar = 0;
	for (int i = 0; i < _tweakBars.size(); ++i)
	{
		TwDeleteBar(_tweakBars.at(i));
	}
}
