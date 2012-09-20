#include "VecF3.h"

VecF3::VecF3() {}
VecF3::VecF3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
VecF3::~VecF3() {}

/*Operators*/
VecF3& VecF3::operator+=(const VecF3& vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;

	return *this;
}
VecF3& VecF3::operator-=(const VecF3& vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;

	return *this;
}
VecF3& VecF3::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;

	return *this;
}

/*Helper functions*/
VecF3 VecF3::cross(const VecF3& vec) const
{
	const float x = this->y * vec.z - this->z * vec.y;
	const float y = this->z * vec.x - this->x * vec.z;
	const float z = this->x * vec.y - this->y * vec.x;

	return VecF3(x, y, z);
}
VecF3& VecF3::normalize()
{
	const float length = sqrtf(x * x + y * y + z * z);
	x /= length;
	y /= length;
	z /= length;

	return *this;
}
void VecF3::rotate(float angle, const VecF3& axis)
{
	const float sinHalfAngle = sinf((float)RADIAN(angle / 2));
	const float cosHalfAngle = cosf((float)RADIAN(angle / 2));

	const float rX = axis.x * sinHalfAngle;
	const float rY = axis.y * sinHalfAngle;
	const float rZ = axis.z * sinHalfAngle;
	const float rW = cosHalfAngle;
	Quaternion rotationQ(rX, rY, rZ, rW);

	Quaternion conjugateQ = rotationQ.conjugate();
	//ConjugateQ.Normalize();
	Quaternion w = rotationQ * (*this) * conjugateQ;

	x = w.x;
	y = w.y;
	z = w.z;
}

float VecF3::dot(VecF3 right)
{
	float result = x*right.x + y*right.y + z*right.z;
	return result;
}