#ifndef WINDOWS

#include "WindowGL.h"

WindowGL::WindowGL(int argc, char** argv)
{
	this->argc = argc;
	this->argv = argv;
}
WindowGL::~WindowGL()
{

}

void WindowGL::init()
{
	/*Subcribe to msgs*/
	SubscriptionMsg* subscriptionMsg = new SubscriptionMsg(this, MSG_GLUT_CALLBACK);
	Singleton<ObserverDirector>::get().push(subscriptionMsg);

	/*Initialize window through GLUT*/
	glutInit(&argc, argv);
	glutInitDisplayMode(
		GLUT_DOUBLE	|	//Double-buffer
		GLUT_RGBA	|	//Back-buffer
		GLUT_DEPTH	|	//Depth-buffer
		GLUT_STENCIL);	//Stencil-buffer

	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);	//Initialize window
	glutInitWindowPosition(100, 100);					//...
	glutCreateWindow("PACMANIA");						//...

	glutSetOption(
		GLUT_ACTION_ON_WINDOW_CLOSE,
		GLUT_ACTION_CONTINUE_EXECUTION);
	
	//glutGameModeString("1920x1200@32");
	//glutEnterGameMode();

	/*Initialize GLEW,
	* must be initialized after glut
	*/
	GLenum result = glewInit();
	if (result != GLEW_OK)
		throw 0; //fix
}
void WindowGL::update(double delta)
{
	Msg* msg = peek();
	while(msg != nullptr)
	{
		msg = pop();
		if(msg)
		{
			switch(msg->Type())
			{
			case MSG_GLUT_CALLBACK:
				glutCallback(msg);
				break;
			default:
				throw 0; //tmep
				break;
			}
		}
	}

	glutMainLoopEvent();
}
void WindowGL::glutCallback(Msg* msg)
{
	MsgGlutCallback*	callbackMsg		= (MsgGlutCallback*)msg;
	CALLBACK_TYPE		callbackType	= callbackMsg->CallBackType();
	switch(callbackType)
	{
	case DISPLAY_FUNC:
		glutCallbackDisplayFunc(callbackMsg);
		break;
	case IDLE_FUNC:
		glutCallbackIdleFunc(callbackMsg);
		break;
	default:
		throw 0;
		break;
	}
	delete callbackMsg;
}
void WindowGL::glutCallbackDisplayFunc(MsgGlutCallback* callbackMsg)
{
	glutDisplayFunc(
		(void (__cdecl *)(void))
		(callbackMsg->Callback()));
}
void WindowGL::glutCallbackIdleFunc(MsgGlutCallback* callbackMsg)
{
	glutIdleFunc(
		(void (__cdecl *)(void))
		(callbackMsg->Callback())
		);
}

void WindowGL::startGlutMain()
{
	glutMainLoop();
}

