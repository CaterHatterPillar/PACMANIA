#ifndef SUBSCRIPTIONMSG_H
#define SUBSCRIPTIONMSG_H

#include "Msg.h"

class SubscriptionMsg : public Msg
{
private:
	Component*	subscriber;
	MsgType		subscription;
protected:
public:
	Component*	Subscriber()		{ return subscriber;	}
	MsgType		Subscription()		{ return subscription;	}

	SubscriptionMsg(Component* subscriber, MsgType subscription) : Msg(SUBSCRIBE) 
	{
		this->subscriber	= subscriber;
		this->subscription	= subscription;
	}
	~SubscriptionMsg(){}
};

#endif //SUBSCRIPTIONMSG_H