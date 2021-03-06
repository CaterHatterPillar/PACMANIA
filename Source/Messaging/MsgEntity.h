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
	virtual ~MsgEntityPlayerPos() {}
};

class MsgEntityPacmanPos : public Msg
{
public:
	VecI2 pos;
	VecF3 position;
	MsgEntityPacmanPos(VecI2 pos, VecF3 position) : Msg(ENTITY_PACMAN_POS)
	{
		this->pos = pos;
		this->position = position;
	}
	MsgEntityPacmanPos(MsgEntityPacmanPos* msg) : Msg(ENTITY_PACMAN_POS)
	{
		pos = msg->pos;
		position = msg->position;
	}
	virtual ~MsgEntityPacmanPos() {}
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
	virtual ~MsgEntityGhostPos() {}
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
	virtual ~MsgEntityPillPos() {}
};

class MsgEntityGhostSpawn : public Msg
{
public:
	MsgEntityGhostSpawn() : Msg(ENTITY_GHOST_SPAWN)
	{
	}
	virtual ~MsgEntityGhostSpawn() {}
};

class MsgEntityPillEaten : public Msg
{
public:
	MsgEntityPillEaten() : Msg(ENTITY_PILL_EATEN)
	{
	}
	virtual ~MsgEntityPillEaten() {}
};

class MsgEntityPillBloodyEaten : public Msg
{
public:
	MsgEntityPillBloodyEaten() : Msg(ENTITY_PILL_BLOODY_EATEN)
	{
	}
	virtual ~MsgEntityPillBloodyEaten() {}
};

class MsgGameOver : public Msg
{
public:
	MsgGameOver() : Msg(GAME_OVER)
	{
	}
	virtual ~MsgGameOver() {}
};

class MsgGameWon : public Msg
{
public:
	MsgGameWon() : Msg(GAME_WON)
	{
	}
	virtual ~MsgGameWon() {}
};

#endif