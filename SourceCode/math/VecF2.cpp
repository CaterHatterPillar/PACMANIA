#include "VecF2.h"

VecF2::VecF2() {}
VecF2::VecF2(float x, float y)
{
	this->x = x;
	this->y = y;
}
VecF2::~VecF2() {}

/*Operators*/
VecF2& VecF2::operator+=(const VecF2& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}
VecF2& VecF2::operator-=(const VecF2& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}
VecF2& VecF2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

/*Helper Functions*/
VecF2& VecF2::normalize()
{
	const float length = sqrtf(x * x + y * y);
	x /= length;
	y /= length;

	return *this;
}