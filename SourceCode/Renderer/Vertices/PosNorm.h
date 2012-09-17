#ifndef POSNORM_H
#define POSNORM_H

#include "Pos.h"

struct PosNorm : public Pos
{
	VecF3 norm;
};

#endif //POSNORM_H