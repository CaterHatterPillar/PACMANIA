#ifndef OBSERVER_H
#define OBSERVER_H

#include "Common.h"
#include "Component.h"

class Observer
{
private:
	Component* component;
	std::vector<MsgType>* subscriptions;
protected:
public:
	Component* getComponent()
	{
		return component;
	}
	bool isSubscriber(MsgType subscription)
	{
		bool subscribed = false;
		for(UINT i = 0; i < subscriptions->size(); i++)
		{
			if(subscriptions->at(i) == subscription)
				subscribed = true;
		}
		return subscribed;
	}

	Observer(Component* component, MsgType subscription) 
	{
		subscriptions = new std::vector<MsgType>();

		this->component = component;
		subscriptions->push_back(subscription);
	}
	~Observer() 
	{
		delete subscriptions;
	}
};

#endif //OBSERVER_H