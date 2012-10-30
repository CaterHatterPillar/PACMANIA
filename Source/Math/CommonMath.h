#ifndef COMMONMATH_H
#define COMMONMATH_H

#include <math.h>

#define PI 3.141592654

#define RADIAN(x) ((x) * PI / 180.0f)
#define DEGREE(x) ((x) * 180.0f / PI)

static float lerp(float x, float y, float f)
{
	float result =  x * (1.0f - f) + y * f;
	return result;
}

#endif //COMMONMATH_H