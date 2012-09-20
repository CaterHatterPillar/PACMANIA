#include "InputGL.h"

void InputGL::init()
{
	/*Init GLUT callbacks*/
	MsgGlutCallback* callbackMsg
		= new MsgGlutCallback(keyboardSpecialSpec, SPECIAL_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	callbackMsg = new MsgGlutCallback(keyboardSpec, KEYBOARD_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	callbackMsg = new MsgGlutCallback(mouseSpec, PASSIVE_MOTION_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);
}
void InputGL::update(double delta)
{

}

/*Callback*/
void InputGL::keyboardSpecialSpec(int key, int x, int y)
{
	KEY k;
	switch(key)
	{
	case GLUT_KEY_UP:
		k = UP;
		break;
	case GLUT_KEY_DOWN:
		k = DOWN;
		break;
	case GLUT_KEY_LEFT:
		k = LEFT;
		break;
	case GLUT_KEY_RIGHT:
		k = RIGHT;
		break;
	//default:
	//	throw 0; //tmep
	}

	MsgKeyboard* keyboardMsg = new MsgKeyboard(k);
	Singleton<ObserverDirector>::get().push(keyboardMsg);
}
void InputGL::keyboardSpec(unsigned char key, int x, int y)
{
	//Send msg of exiting glut
	switch (key)
	{
	case 'q':
		throw 0;
		break;
	//default:
	//	break;
	}
}
void InputGL::mouseSpec(int x, int y)
{
	MsgMouseMove* mouseMoveMsg
		= new MsgMouseMove((long)x, (long)y);
	Singleton<ObserverDirector>::get().push(mouseMoveMsg);
}

InputGL::InputGL()
{

}
InputGL::~InputGL()
{

}