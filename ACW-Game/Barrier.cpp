#include "Barrier.h"


Barrier::Barrier(Vector4 pos, Vector4 scale) : RenderedEntity("Cube", "bricks")
{
	SetScale(scale);
	SetPosition(pos);
	SetEntityName("Barrier");

	Vector4 collisionScale = GetScale();
	scale.multiply(1.6f);
	ComponentCollision* collision = new ComponentCollision(this, scale, true);
}