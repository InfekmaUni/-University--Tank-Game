#include "Shader.h"

using namespace GameEngine;

Shader::Shader(std::string vName, std::string pName) 
	: _vName(vName), _pName(pName), 
	_vEntryPoint(VS_ENTRYPOINT), _pEntryPoint(PS_ENTRYPOINT),
	_vShaderModel(VS_SHADER_MODEL), _pShaderModel(PS_SHADER_MODEL)

{}

Shader::Shader(std::string vName, std::string pName, std::string vEntry, std::string pEntry, std::string vModel, std::string pModel)
	: _vName(vName), _pName(pName),
	_vEntryPoint(vEntry), _pEntryPoint(pEntry),
	_vShaderModel(vModel), _pShaderModel(pModel)

{

}