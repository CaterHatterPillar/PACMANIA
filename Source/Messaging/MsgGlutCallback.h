#ifndef MSGGLUTCALLBACK_H
#define MSGGLUTCALLBACK_H

#include "Msg.h"

enum CALLBACK_TYPE
{ 
	DISPLAY_FUNC, 
	IDLE_FUNC,

	SPECIAL_FUNC,
	PASSIVE_MOTION_FUNC,
	KEYBOARD_FUNC,
};

//Modify so that several  callback-types may use the same msg
class MsgGlutCallback : public Msg
{
private:
	void*			callback;
	CALLBACK_TYPE	callbackType;
protected:
public:
	MsgGlutCallback(
		void*			callback, 
		CALLBACK_TYPE	callbackType) : Msg(MSG_GLUT_CALLBACK)
	{
		this->callback		= callback;
		this->callbackType	= callbackType;
	}
	MsgGlutCallback(MsgGlutCallback* msgGlutCallback) : Msg(MSG_GLUT_CALLBACK)
	{
		callback		= msgGlutCallback->Callback();
		callbackType	= msgGlutCallback->CallBackType();
	}
	virtual ~MsgGlutCallback() {}

	void*			Callback()		{ return callback;		}
	CALLBACK_TYPE	CallBackType()	{ return callbackType;	}
};

#endif //MSGGLUTCALLBACK_H