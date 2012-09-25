#include "InputGL.h"

int InputGL::lastMouseX;
int InputGL::lastMouseY;

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

	lastMouseX = 0;
	lastMouseY = 0;
}
void InputGL::update(double delta)
{

}

/*Callback*/
void InputGL::keyboardSpecialSpec(int key, int x, int y)
{
	bool validKey = false;

	KEY k;
	switch(key)
	{
	case GLUT_KEY_UP:
		k = KEY_UP;
		validKey = true;
		break;
	case GLUT_KEY_DOWN:
		k = KEY_DOWN;
		validKey = true;
		break;
	case GLUT_KEY_LEFT:
		k = KEY_LEFT;
		validKey = true;
		break;
	case GLUT_KEY_RIGHT:
		k = KEY_RIGHT;
		validKey = true;
		break;
	default:
		throw 0; //tmep
	}

	if(validKey)
	{
		MsgKeyboard* keyboardMsg = new MsgKeyboard(k);
		Singleton<ObserverDirector>::get().push(keyboardMsg);
	}
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
	bool mouseMoved = false;
	if(x != lastMouseX)
	{
		mouseMoved = true;
		lastMouseX = x;
	}
	else if(y != lastMouseY)
	{
		mouseMoved = true;
		lastMouseY = y;
	}

	if(mouseMoved)
	{
		MsgMouseMove* mouseMoveMsg
			= new MsgMouseMove((long)x, (long)y);
		Singleton<ObserverDirector>::get().push(mouseMoveMsg);
	}
}

InputGL::InputGL()
{

}
InputGL::~InputGL()
{

}