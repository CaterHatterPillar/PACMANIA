#include "ObserverDirector.h"

void ObserverDirector::init()
{
}
void ObserverDirector::update(double delta)
{
	while(peek())
	{
		Msg* msg = pop();

		MsgType type = msg->Type();
		switch(type)
		{
		case SUBSCRIBE:
			subscribeMsg(msg);
			break;
		case MSG_GLUT:
			msgGlut(msg);
			break;
		case MSG_GLUT_CALLBACK:
			msgGlutCallback(msg);
			break;
		case RENDER:
			msgRender(msg);
			break;
		case INPUT_MOUSE_MOVE:
			msgMouseMove(msg);
			break;
		case INPUT_MOUSE_CLICK:
			msgMouseClick(msg);
			break;
		case INPUT_KEYBOARD_MSG:
			msgKeyboard(msg);
			break;
		case CAMERA:
			msgCamera(msg);
			break;
		case DX_WINDOW_HANDLE:
			msgDXWindowHandle(msg);
			break;
		case ENTITY_STATE:
			msgEntityState(msg);
			break;
		case LIGHT:
			msgLight(msg);
			break;
		default:
			throw 0; //temp, make fix
			break;
		}
	}
}

void ObserverDirector::msgDXWindowHandle(Msg* msg)
{
	MsgDXWindowHandle* msgDX = (MsgDXWindowHandle*)msg;

	for(int i=0; i<(int)observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
			observer->getComponent()->push(msgDX);
	}
}

void ObserverDirector::subscribeMsg(Msg* msg)
{
	SubscriptionMsg* subMsg = (SubscriptionMsg*)msg;
	subscribe(subMsg->Subscriber(), subMsg->Subscription());
	delete subMsg;
}

void ObserverDirector::subscribe(Component* subscriber, MsgType subscription)
{	//todoist, check if observer already exists - modify original subscriber
	observers->push_back(new Observer(subscriber, subscription));
}
void ObserverDirector::msgGlut(Msg* msg)
{
	MsgType type = msg->Type();
	MsgGlut* glutMsg = (MsgGlut*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgGlut* newInstance = new MsgGlut(glutMsg);
			observer->getComponent()->push(newInstance);
		}
	}
	delete glutMsg;
}
void ObserverDirector::msgGlutCallback(Msg* msg)
{
	MsgType type = msg->Type();
	MsgGlutCallback* glutCallback = (MsgGlutCallback*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgGlutCallback* newInstance = new MsgGlutCallback(glutCallback);
			observer->getComponent()->push(newInstance);
		}
	}
	delete glutCallback;
}
void ObserverDirector::msgRender(Msg* msg)
{
	MsgType type = msg->Type();
	MsgRender* renderMsg = (MsgRender*)msg;

	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{

			MsgRender* newInstance = new MsgRender(renderMsg);
			observer->getComponent()->push(newInstance);
		}
	}
	delete renderMsg;
}
void ObserverDirector::msgMouseClick(Msg* msg)
{
	MsgType type = msg->Type();
	MsgMouseClick* msgClick = (MsgMouseClick*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgMouseClick* newInstance = new MsgMouseClick(msgClick);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgClick;
}
void ObserverDirector::msgMouseMove(Msg* msg)
{
	MsgType type = msg->Type();
	MsgMouseMove* msgMove = (MsgMouseMove*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgMouseMove* newInstance = new MsgMouseMove(msgMove);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgMove;
}
void ObserverDirector::msgKeyboard(Msg* msg)
{
	MsgType type = msg->Type();
	MsgKeyboard* msgKeyboard = (MsgKeyboard*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgKeyboard* newInstance = new MsgKeyboard(msgKeyboard);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgKeyboard;
}
void ObserverDirector::msgCamera(Msg* msg)
{
	MsgType type = msg->Type();
	MsgCamera* msgCam = (MsgCamera*)msg;
	for(unsigned int i = 0; i < observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgCamera* newInstance = new MsgCamera(msgCam);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgCam;
}

void ObserverDirector::msgLight(Msg* msg)
{
	MsgType type = msg->Type();
	MsgLight* msgLight = (MsgLight*)msg;
	for(unsigned int i = 0; i<observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(type))
		{
			MsgLight* newInstance = new MsgLight(msgLight);
			observer->getComponent()->push(newInstance);
		}
	}
	delete msgLight;
}

ObserverDirector::ObserverDirector() : Component()
{
	observers = new std::vector<Observer*>();
}
ObserverDirector::~ObserverDirector()
{
	if(observers != NULL)
	{
		for(unsigned int i = 0; i < observers->size(); i++)
			if(observers->at(i) != NULL)
				delete observers->at(i);
		delete observers;
	}
}
