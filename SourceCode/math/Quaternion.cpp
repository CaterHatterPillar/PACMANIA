#include "Quaternion.h"

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Quaternion::~Quaternion()
{

}

Quaternion& Quaternion::normalize()
{
	float length = sqrtf(x * x + y * y + z * z + w * w);
	x /= length;
	y /= length;
	z /= length;
	w /= length;

	return *this;
}
Quaternion Quaternion::conjugate()
{
	Quaternion ret(-x, -y, -z, w);
	return ret;
}

/*Operators*/
Quaternion operator*(const Quaternion& left, const Quaternion& right)
{
	const float w = (left.w * right.w) - (left.x * right.x) - (left.y * right.y) - (left.z * right.z);
	const float x = (left.x * right.w) + (left.w * right.x) + (left.y * right.z) - (left.z * right.y);
	const float y = (left.y * right.w) + (left.w * right.y) + (left.z * right.x) - (left.x * right.z);
	const float z = (left.z * right.w) + (left.w * right.z) + (left.x * right.y) - (left.y * right.x);

	Quaternion ret(x, y, z, w);
	return ret;
}
Quaternion operator*(const Quaternion& quaternion, const VecF3& vec)
{
	const float w = - (quaternion.x * vec.x) - (quaternion.y * vec.y) - (quaternion.z * vec.z);
	const float x =   (quaternion.w * vec.x) + (quaternion.y * vec.z) - (quaternion.z * vec.y);
	const float y =   (quaternion.w * vec.y) + (quaternion.z * vec.x) - (quaternion.x * vec.z);
	const float z =   (quaternion.w * vec.z) + (quaternion.x * vec.y) - (quaternion.y * vec.x);

	Quaternion ret(x, y, z, w);
	return ret;
}