#ifndef POSNORMTEX_H
#define POSNORMTEX_H

#include "PosNorm.h"

enum POS_NORM_TEX
{
	PosNormTex_POS,
	PosNormTex_NORM,
	PosNormTex_TEX,
	PosNormTex_NUM_ATTRIBUTES
};

struct PosNormTex : public PosNorm
{
	VecF2 tex;

	PosNormTex() {}
	PosNormTex(VecF3 position, VecF3 normal, VecF2 tex) : PosNorm(position, normal)
	{
		this->tex = tex;
	}
};

#endif //POSNORMTEX_H