#ifndef MSGMOUSECLICK_H
#define MSGMOUSECLICK_H

#include "Msg.h"

class MsgMouseClick : public Msg
{
private:
	bool mouse1;
	bool mouse2;
protected:
public:
	MsgMouseClick(bool mouse1, bool mouse2)	: Msg(INPUT_MOUSE_CLICK)
	{
		this->mouse1 = mouse1;
		this->mouse2 = mouse2;
	}
	MsgMouseClick(MsgMouseClick* mouseClickMsg)	: Msg(INPUT_MOUSE_CLICK)
	{
		mouse1 = mouseClickMsg->Mouse1();
		mouse2 = mouseClickMsg->Mouse2();
	}
	~MsgMouseClick() {}

	bool Mouse1() { return mouse1; }
	bool Mouse2() { return mouse2; }
};

#endif //MSGMOUSECLICK_H