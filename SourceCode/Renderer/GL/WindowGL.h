#ifndef WINDOWGL_H
#define WINDOWGL_H

#include "CommonGL.h"

#include "../../Common.h"
#include "../Window.h"
#include "../../Singleton.h"
#include "../../Messaging/ObserverDirector.h"
#include "../../Messaging/SubscriptionMsg.h"
#include "../../Messaging/MsgGlut.h"
#include "../../Messaging/MsgGlutCallback.h"

class WindowGL : public Window
{
private:
	int		argc;
	char**	argv;

	void glutCallback(Msg* msg);
	void glutCallbackDisplayFunc(MsgGlutCallback*		callbackMsg);
	void glutCallbackIdleFunc(MsgGlutCallback*			callbackMsg);
	void glutCallbackSpecialFunc(MsgGlutCallback*		callbackMsg);
	void glutCallBackPassiveMotionFunc(MsgGlutCallback*	callbackMsg);
	void glutCallbackKeyboardFunc(MsgGlutCallback*		callbackMsg);

	void glut(Msg* msg);
	void glutWarpPointerMsg(MsgGlut* glutMsg);
protected:
public:
	WindowGL(int argc, char** argv);
	~WindowGL();

	virtual void init();
	virtual void update(double delta);
};

#endif //WINDOWGL_H