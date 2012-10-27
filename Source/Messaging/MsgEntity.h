#ifndef MSGENTITY_H
#define MSGENTITY_H

#include "Msg.h"
#include "../Math/PacMath.h"

class MsgEntityPlayerPos : public Msg
{
public:
	VecF3 pos;
	MsgEntityPlayerPos(VecF3 pos) : Msg(ENTITY_PLAYER_POS)
	{
		this->pos = pos;
	}
	MsgEntityPlayerPos(MsgEntityPlayerPos* msg) : Msg(ENTITY_PLAYER_POS)
	{
		pos = msg->pos;
	}
};

class MsgEntityPacmanPos : public Msg
{
public:
	VecI2 pos;
	MsgEntityPacmanPos(VecI2 pos) : Msg(ENTITY_PACMAN_POS)
	{
		this->pos = pos;
	}
	MsgEntityPacmanPos(MsgEntityPacmanPos* msg) : Msg(ENTITY_PACMAN_POS)
	{
		pos = msg->pos;
	}
};

class MsgEntityGhostPos : public Msg
{
public:
	VecI2 pos;
	VecF3 position;
	MsgEntityGhostPos(VecI2 pos, VecF3 position) : Msg(ENTITY_GHOST_POS)
	{
		this->pos = pos;
		this->position = position;
	}
	MsgEntityGhostPos(MsgEntityGhostPos* msg) : Msg(ENTITY_GHOST_POS)
	{
		pos = msg->pos;
		position = msg->position;
	}
};

class MsgEntityPillPos : public Msg
{
public:
	VecI2 pos;
	MsgEntityPillPos(VecI2 pos) : Msg(ENTITY_PILL_POS)
	{
		this->pos = pos;
	}
	MsgEntityPillPos(MsgEntityPillPos* msg) : Msg(ENTITY_PILL_POS)
	{
		pos = msg->pos;
	}
};

#endif