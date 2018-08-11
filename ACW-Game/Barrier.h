#pragma once
#include "RenderedEntity.h"
#include "Vector4.h"

#include "ComponentCollision.h"

class Barrier : public RenderedEntity
{
public:
	Barrier(Vector4 pos = Vector4(0,0,0), Vector4 scale = Vector4(1,1,1));
	~Barrier() = default;

public:

};

