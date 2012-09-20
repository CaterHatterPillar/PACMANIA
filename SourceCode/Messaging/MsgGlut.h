#ifndef MSGGLUT_H
#define MSGGLUT_H

#include "Msg.h"

enum GLUT_BEHAVIOUR
{
	WARP_POINTER
};

class MsgGlut : public Msg
{
private:
	GLUT_BEHAVIOUR behaviour;

	int intFirst;
	int intSecond;
protected:
public:
	MsgGlut(
		GLUT_BEHAVIOUR behaviour, 
		int intFirst, 
		int intSecond) : Msg(MSG_GLUT)
	{
		this->behaviour	= behaviour;
		this->intFirst	= intFirst;
		this->intSecond	= intSecond;
	}
	MsgGlut(MsgGlut* glutMsg) : Msg(MSG_GLUT)
	{
		this->behaviour = glutMsg->Behaviour();
		this->intFirst	= glutMsg->IntFirst();
		this->intSecond	= glutMsg->IntSecond();
	}
	~MsgGlut()
	{

	}

	GLUT_BEHAVIOUR Behaviour() { return behaviour; }
	int IntFirst()	{ return intFirst;	}
	int IntSecond()	{ return intSecond;	}
};

#endif //MSGGLUT_H