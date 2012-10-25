#ifndef CONSTANTBUFFERS_H
#define CONSTANTBUFFERS_H

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include "../Math/PacMath.h"

#include "../Light.h"

struct CBufferPerFrame
{
	MatF4 final;
	MatF4 world;
	VecF3 cameraPosition;
};

struct CBufferLights
{
	Light lights[MAX_NUM_LIGHTS];
	unsigned int numLights;
};

struct CBufferEffects
{
	VecF4 effect;
};

#endif