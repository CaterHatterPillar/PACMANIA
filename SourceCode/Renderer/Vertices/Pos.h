#ifndef POS_H
#define POS_H

#include "../../Math/PacMath.h"

struct Pos
{
	VecF3 pos;

	Pos() {}
	Pos(VecF3 position)
	{
		this->pos = position;
	}
};

#endif //POS_H