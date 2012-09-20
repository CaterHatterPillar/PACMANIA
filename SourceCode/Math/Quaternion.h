#ifndef QUATERNION_H
#define QUATERNION_H

#include "CommonMath.h"
#include "VecF3.h"

struct VecF3;
struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	/*Helper Funcs*/
	Quaternion& normalize();
	Quaternion conjugate();
};

Quaternion operator*(const Quaternion& left, const Quaternion& right);
Quaternion operator*(const Quaternion& quaternion, const VecF3& vec);

#endif //QUATERNION_H