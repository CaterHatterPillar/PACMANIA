#ifndef MSGMOUSEMOVE_H
#define MSGMOUSEMOVE_H

#include "Msg.h"

class MsgMouseMove : public Msg
{
private:
	long dX;
	long dY;
protected:
public:
	MsgMouseMove(long dX, long dY) : Msg(INPUT_MOUSE_MOVE)
	{
		this->dX = dX;
		this->dY = dY;
	}
	MsgMouseMove(MsgMouseMove* msgMouseMove) : Msg(INPUT_MOUSE_MOVE)
	{
		dX = msgMouseMove->DX();
		dY = msgMouseMove->DY();
	}
	~MsgMouseMove() {}

	long DY() { return dY;	}
	long DX() { return dX;	}
};

#endif //MSGMOUSEMOVE_H