#ifndef VECF2_H
#define VECF2_H

#include "CommonMath.h"

struct VecF2
{
	float x;
	float y;

	VecF2() {}
	VecF2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	virtual ~VecF2() {}

	/*Operators*/
	virtual VecF2& operator+=(const VecF2& vec)
	{
		x += vec.x;
		y += vec.y;

		return *this;
	}
	virtual VecF2& operator-=(const VecF2& vec)
	{
		x -= vec.x;
		y -= vec.y;

		return *this;
	}
	virtual VecF2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	/*Helper Functions*/
	virtual VecF2& normalize()
	{
		float length = sqrtf(x * x + y * y);
		x /= length;
		y /= length;

		return *this;
	}
};

#endif //VECF2_H