#ifndef OBSERVERDIRECTOR_H
#define OBSERVERDIRECTOR_H

#include "../Common.h"
#include "Observer.h"

/*Msgs*/
#include "SubscriptionMsg.h"
#include "MsgDXWindowHandle.h"

class ObserverDirector : public Component
{
private:
	std::vector<Observer*>* observers;

	void subscribeMsg(Msg* msg);

	void msgDXWindowHandle(Msg* msg);

	void subscribe(
		Component*	subscriber, 
		MsgType		subscription);
protected:
public:
	ObserverDirector();
	~ObserverDirector();

	void init();
	void update(double delta);
};

#endif //OBSERVERDIRECTOR_H