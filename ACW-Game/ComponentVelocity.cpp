#include "ComponentVelocity.h"

Vector4 ComponentVelocity::Clamp(Vector4 vec, float min, float max)
{
	Vector4 temp;
	float iterate[3] = { vec.x(), vec.y(), vec.z() };
	for (int i = 0; i < 3; i++)
	{
		if (iterate[i] > max)
		{
			iterate[i] = max;
		}
		else if (iterate[i] < min)
		{
			iterate[i] = min;
		}
	}
	temp.x(iterate[0]);
	temp.y(iterate[1]);
	temp.z(iterate[2]);
	return temp;
}

float ComponentVelocity::Clamp(float numb, float min, float max)
{
	if (numb > max)
	{
		return max;
	}
	else if (numb < min)
	{
		return min;
	}
	else
	{
		return numb;
	}
}