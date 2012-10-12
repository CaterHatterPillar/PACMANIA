#ifndef CONSTANTBUFFERS_H
#define CONSTANTBUFFERS_H

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include "../Math/PacMath.h"

struct CBufferPerFrame
{
	MatF4 final;
	MatF4 world;
};

#endif