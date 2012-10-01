#ifndef POSNORMTEX_H
#define POSNORMTEX_H

#include "PosNorm.h"

struct PosNormTex //: public PosNorm
{
	VecF3 pos;
	VecF3 norm;
	VecF2 tex;

	PosNormTex(VecF3 position, VecF3 normal, VecF2 tex) //: PosNorm(position, normal)
	{
		this->pos = position;
		this->norm = normal;
		this->tex = tex;
	}
};

#endif //POSNORMTEX_H