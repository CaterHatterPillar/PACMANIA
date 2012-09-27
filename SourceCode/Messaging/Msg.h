#ifndef MSG_H
#define MSG_H

#include "MsgType.h"

class Msg
{
private:
	MsgType type;
protected:
public:
	Msg(MsgType type) 
	{ 
		this->type = type; 
	}
	Msg(const Msg& msg)
	{
		type = msg.type;
	}

	virtual ~Msg() {}

	MsgType Type() { return type; }
};

#endif //MSG_H