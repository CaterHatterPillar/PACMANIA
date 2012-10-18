#ifndef MSGENTITY_POS_H
#define MSGENTITY_POS_H

#include "Msg.h"
#include "../Math/PacMath.h"

class MsgEntityState : public Msg
{
public:
	VecF3 pos;
	int id;
	MsgEntityState(VecF3 pos, int id) : Msg(ENTITY_STATE)
	{
		this->pos = pos;
		this->id = id;
	}
	MsgEntityState(MsgEntityState* msg) : Msg(ENTITY_STATE)
	{
		pos = msg->pos;
		id = msg->id;
	}
};

#endif