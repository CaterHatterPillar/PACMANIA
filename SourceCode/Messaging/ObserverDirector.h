#ifndef OBSERVERDIRECTOR_H
#define OBSERVERDIRECTOR_H

#include "../Common.h"
#include "Observer.h"

/*Msgs*/
#include "SubscriptionMsg.h"
#include "MsgGlut.h"
#include "MsgGlutCallback.h"
#include "MsgRender.h"
#include "MsgCamera.h"
#include "MsgMouseClick.h"
#include "MsgMouseMove.h"
#include "MsgKeyboard.h"

class ObserverDirector : public Component
{
private:
	std::vector<Observer*>* observers;

	void subscribeMsg(Msg* msg);
	void subscribe(
		Component*	subscriber, 
		MsgType		subscription);
	void msgGlut(Msg* msg);
	void msgGlutCallback(Msg* msg);
	void msgRender(Msg* msg);
	void msgMouseClick(Msg* msg);
	void msgMouseMove(Msg* msg);
	void msgKeyboard(Msg* msg);
	void msgCamera(Msg* msg);
protected:
public:
	ObserverDirector();
	~ObserverDirector();

	void init();
	void update(double delta);
};

#endif //OBSERVERDIRECTOR_H