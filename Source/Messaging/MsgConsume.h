#ifndef MSGCONSUME_H
#define MSGCONSUME_H

#include "Msg.h"

enum ConsumeState { CONSUME_STATE_DISPLAY, CONSUME_NO_STATE };

class MsgConsume : public Msg
{
private:
	ConsumeState state;
protected:
public:
	MsgConsume(ConsumeState state) : Msg(CONSUME)
	{
		this->state = state;
	}
	MsgConsume(MsgConsume* consumeMsg) : Msg(CONSUME)
	{
		this->state = consumeMsg->getState();
	}
	virtual ~MsgConsume()
	{
	}

	ConsumeState getState() { return state; }
};

#endif //MSGCONSUME_H