#include "InputGL.h"

int InputGL::halfWidth;
int InputGL::halfHeight;
bool InputGL::warpLock;

void InputGL::init()
{
	/*Init GLUT callbacks*/
	MsgGlutCallback* callbackMsg
		= new MsgGlutCallback((void*)keyboardSpecialSpec, SPECIAL_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	callbackMsg = new MsgGlutCallback((void*)keyboardSpec, KEYBOARD_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);

	callbackMsg = new MsgGlutCallback((void*)mouseSpec, PASSIVE_MOTION_FUNC);
	Singleton<ObserverDirector>::get().push(callbackMsg);
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
	case GLUT_KEY_F4:
		{
			MsgGlut* glutMsg = new MsgGlut(QUIT);
			Singleton<ObserverDirector>::get().push(glutMsg);
			break;
		}
	default:
	//	throw 0; //tmep
		break;
	}

	if(validKey)
	{
		MsgKeyboard* keyboardMsg = new MsgKeyboard(k);
		Singleton<ObserverDirector>::get().push(keyboardMsg);
	}
}
void InputGL::keyboardSpec(unsigned char key, int x, int y)
{
	KEY k;
	bool validKey = false;

	switch (key)
	{
	case 'w':
		k = KEY_W;
		validKey = true;
		break;
	case 'a':
		k = KEY_A;
		validKey = true;
		break;
	case 's':
		k = KEY_S;
		validKey = true;
		break;
	case 'd':
		k = KEY_D;
		validKey = true;
		break;
	default:
		break;
	}

	if(validKey)
	{
		MsgKeyboard* keyboardMsg = new MsgKeyboard(k);
		Singleton<ObserverDirector>::get().push(keyboardMsg);
	}
}
void InputGL::mouseSpec(int x, int y)
{
	if(!warpLock)
	{
		int posX = halfWidth - x;
		int posY = halfHeight - y;

		MsgMouseMove* mouseMoveMsg = new MsgMouseMove((long)posX, (long)posY);
		Singleton<ObserverDirector>::get().push(mouseMoveMsg);

		MsgGlut* glutMsg = new MsgGlut(WARP_POINTER, halfWidth, halfHeight);
		Singleton<ObserverDirector>::get().push(glutMsg);
		warpLock = true;
	}
	else
		warpLock = false;
}

InputGL::InputGL()
{
	halfWidth = SCREEN_WIDTH / 2;
	halfHeight = SCREEN_HEIGHT / 2;
	warpLock = false;
}
InputGL::~InputGL()
{

}
