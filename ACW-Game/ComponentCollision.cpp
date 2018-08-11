#include "ComponentCollision.h"

void ComponentCollision::SetExtends(Vector4 newExtend)
{
	_box.Extents = XMFLOAT3(_extends.x(), _extends.y(), _extends.z());
}