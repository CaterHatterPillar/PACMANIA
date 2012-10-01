#include "MoveBehaviourPlayer.h"

MoveBehaviourPlayer::MoveBehaviourPlayer()
{

}

MoveBehaviourPlayer::~MoveBehaviourPlayer()
{

}

void MoveBehaviourPlayer::keyboard(KEY key)
{
	switch(key)
	{
	case KEY_UP:
		direction = VecF3(0.0f, 1.0f, 0.0f);
		break;
	case KEY_LEFT:
		direction = VecF3(-1.0f, 0.0f, 0.0f);
		break;
	case KEY_DOWN:
		direction = VecF3(0.0f, -1.0f, 0.0f);
		break;
	case KEY_RIGHT:
		direction = VecF3(1.0f, 0.0f, 0.0f);
		break;
	}
}

void MoveBehaviourPlayer::init()
{
	SubscriptionMsg* subscription = new SubscriptionMsg(this, INPUT_KEYBOARD_MSG);
	Singleton<ObserverDirector>::get().push(subscription);
}

void MoveBehaviourPlayer::update(double delta)
{
	Msg* msg = peek();
	while(msg)
	{
		msg = pop();
		if(msg)
		{
			MsgType type = msg->Type();
			switch(type)
			{
			case INPUT_KEYBOARD_MSG:
				msgKeyboard(msg);
				break;
			}
		}
	}
}

void MoveBehaviourPlayer::msgKeyboard(Msg* msg)
{
	MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;
	keyboard(keyboardMsg->Key());
	delete keyboardMsg;
}