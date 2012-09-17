#ifndef VECF3_H
#define VECF3_H

#include "VecF2.h"

struct VecF3 : VecF2
{
	float z;

	VecF3() {}
	VecF3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	virtual ~VecF3() {}

	/*Operators*/
	virtual VecF3& operator+=(const VecF3& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}
	virtual VecF3& operator-=(const VecF3& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}
	virtual VecF3& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	/*Helper functions*/
	virtual VecF3 cross(const VecF3& vec) const
	{
		const float x = this->y * vec.z - this->z * vec.y;
		const float y = this->z * vec.x - this->x * vec.z;
		const float z = this->x * vec.y - this->y * vec.x;

		return VecF3(x, y, z);
	}
	virtual VecF3& normalize()
	{
		const float length = sqrtf(x * x + y * y + z * z);
		x /= length;
		y /= length;
		z /= length;

		return *this;
	}
};

#endif //VECF3_H