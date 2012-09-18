#ifndef CONSTANTBUFFERS_H
#define CONSTANTBUFFERS_H

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

struct CBufferPerFrame
{
	D3DXMATRIX final;
	D3DXMATRIX world;
};

#endif