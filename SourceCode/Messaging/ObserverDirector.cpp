#include "ObserverDirector.h"

void ObserverDirector::init()
{
}
void ObserverDirector::update(double delta)
{
	while(peek() != nullptr)
	{
		Msg* msg = pop();

		MsgType type = msg->Type();
		switch(type)
		{
		case SUBSCRIBE:
			subscribeMsg(msg);
			break;
		case DX_WINDOW_HANDLE:
			msgDXWindowHandle(msg);
			break;
		default:
			throw 0; //temp, make fix
			break;
		}
	}
}

void ObserverDirector::subscribeMsg(Msg* msg)
{
	SubscriptionMsg* subMsg = (SubscriptionMsg*)msg;
	subscribe(subMsg->Subscriber(), subMsg->Subscription());
	delete subMsg;
}

void ObserverDirector::msgDXWindowHandle(Msg* msg)
{
	MsgDXWindowHandle* msgDX = (MsgDXWindowHandle*)msg;

	for(int i=0; i<observers->size(); i++)
	{
		Observer* observer = observers->at(i);
		if(observer->isSubscriber(msg->Type()))
			observer->getComponent()->push(msgDX);
	}
}

void ObserverDirector::subscribe(Component* subscriber, MsgType subscription)
{	//todoist, check if observer already exists - modify original subscriber
	observers->push_back(new Observer(subscriber, subscription));
}

ObserverDirector::ObserverDirector() : Component()
{
	observers = new std::vector<Observer*>();
}
ObserverDirector::~ObserverDirector()
{
	if(observers != nullptr)
	{
		for(unsigned int i = 0; i < observers->size(); i++)
			if(observers->at(i) != nullptr)
				delete observers->at(i);
		delete observers;
	}
}