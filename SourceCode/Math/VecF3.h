#ifndef VECF3_H
#define VECF3_H

#include "CommonMath.h"
#include "Quaternion.h"
#include "MatF4.h"

struct VecF3
{
	float x;
	float y;
	float z;

	VecF3();
	VecF3(float x, float y, float z);
	virtual ~VecF3();

	/*Operators*/
	VecF3& operator+=(const VecF3& vec);
	VecF3& operator-=(const VecF3& vec);
	VecF3& operator*=(float scalar);
	 
	/*Helper functions*/
	VecF3 cross(const VecF3& vec) const;
	VecF3& normalize();
	void rotate(float angle, const VecF3& axis);
	float dot(VecF3 right);
};

/*Inline*/
inline VecF3 operator+(const VecF3& left, const VecF3& right)
{
	VecF3 ret(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z);
	return ret;
}
inline VecF3 operator-(const VecF3& left, const VecF3& right)
{
	VecF3 ret(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z);
	return ret;
}
inline VecF3 operator*(const VecF3& left, float scalar)
{
	VecF3 ret(
		left.x * scalar,
		left.y * scalar,
		left.z * scalar);
	return ret;
}

#endif //VECF3_H