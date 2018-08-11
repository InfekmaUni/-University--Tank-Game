#include "Mesh.h"

using namespace GameEngine;

void Mesh::Shutdown()
{
	_vibo->Shutdown();
	delete _vibo; _vibo = 0;
}