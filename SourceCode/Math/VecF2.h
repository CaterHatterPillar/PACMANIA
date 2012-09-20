#ifndef VECF2_H
#define VECF2_H

#include "CommonMath.h"

struct VecF2
{
	float x;
	float y;

	VecF2();
	VecF2(float x, float y);
	virtual ~VecF2();

	/*Operators*/
	VecF2& operator+=(const VecF2& vec);
	VecF2& operator-=(const VecF2& vec);
	VecF2& operator*=(float scalar);

	/*Helper Functions*/
	VecF2& normalize();
};

#endif //VECF2_H