#ifndef WINDOWGL_H
#define WINDOWGL_H

/*OpenGL*/
#include <Windows.h> //obs, tmep
#include <glew.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "../../Common.h"
#include "../Window.h"
#include "../../Singleton.h"
#include "../../Messaging/ObserverDirector.h"
#include "../../Messaging/SubscriptionMsg.h"
#include "../../Messaging/MsgGlutCallback.h"

class WindowGL : public Window
{
private:
	int		argc;
	char**	argv;

	void glutCallback(Msg* msg);
protected:
public:
	WindowGL(int argc, char** argv);
	~WindowGL();

	virtual void init();
	virtual void update(double delta);

	void startGlutMain();
};

#endif //WINDOWGL_H