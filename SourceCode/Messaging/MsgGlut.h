#ifndef MSGGLUT_H
#define MSGGLUT_H

#include "Msg.h"

enum GLUT_BEHAVIOUR
{
	WARP_POINTER,
	QUIT
};

class MsgGlut : public Msg
{
private:
	GLUT_BEHAVIOUR behaviour;

	int intFirst;
	int intSecond;
protected:
public:
	MsgGlut(GLUT_BEHAVIOUR behaviour) : Msg(MSG_GLUT)
	{
		this->behaviour	= behaviour;

		this->intFirst	= 0;
		this->intSecond	= 0;
	}
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
	virtual ~MsgGlut()
	{

	}

	GLUT_BEHAVIOUR Behaviour() { return behaviour; }
	int IntFirst()	{ return intFirst;	}
	int IntSecond()	{ return intSecond;	}
};

#endif //MSGGLUT_H