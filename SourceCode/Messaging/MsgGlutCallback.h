#ifndef MSGGLUTCALLBACK_H
#define MSGGLUTCALLBACK_H

#include "Msg.h"

//Modify so that several  callback-types may use the same msg
class MsgGlutCallback : public Msg
{
private:
	void* callback;
protected:
public:
	MsgGlutCallback(void* callback) : Msg(MSG_GLUT_CALLBACK)
	{
		this->callback = callback;
	}
	MsgGlutCallback(MsgGlutCallback* msgGlutCallback) : Msg(MSG_GLUT_CALLBACK)
	{
		callback = msgGlutCallback->Callback();
	}
	~MsgGlutCallback()
	{

	}

	void* Callback() { return callback; }
};

#endif //MSGGLUTCALLBACK_H