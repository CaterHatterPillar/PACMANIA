#ifndef POSNORM_H
#define POSNORM_H

#include "Pos.h"

struct PosNorm : public Pos
{
	VecF3 norm;

	PosNorm(VecF3 position, VecF3 normal) : Pos(position)
	{
		this->norm = normal;
	}
};

#endif //POSNORM_H