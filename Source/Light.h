#ifndef LIGHT_H
#define LIGHT_H

#include "Math/PacMath.h"

static const int MAX_NUM_LIGHTS = 10;

struct Light
{
	VecF3 pos;
	float spotPow;
	VecF3 dir;
	float range;
	VecF4 ambient;
	VecF4 diffuse;
	VecF4 specular;
	VecF3 att;
	float pad1;

	Light()
	{
		pos			= VecF3(0.0f, 0.0f, 0.0f);
		spotPow		= 0;
		dir			= VecF3(0.0f, 0.0f, 0.0f);
		range		= 0;
		ambient		= VecF4(0.0f, 0.0f, 0.0f, 0.0f);
		diffuse		= VecF4(0.0f, 0.0f, 0.0f, 0.0f);
		specular	= VecF4(0.0f, 0.0f, 0.0f, 0.0f);
		att			= VecF3(0.0f, 0.0f, 0.0f);
	}
};

#endif