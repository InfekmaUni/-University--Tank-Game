#pragma once
#include "VIBO.h"
#include "Vector4.h"

#include <string>
#include <vector>
#include <fstream>

namespace GameEngine
{
	class Mesh
	{
	public:
		Mesh(std::string name) : _meshName(name)
		{}
		~Mesh() = default;

	protected:
		std::string _meshName;
		VIBO* _vibo;

		// getters & setters
	public:
		void SetVIBO(VIBO* vibo) { _vibo = vibo; }
		VIBO* GetVIBO() { return _vibo; }
		std::string GetName() { return _meshName; }

	public:
		void Shutdown();
	};

}