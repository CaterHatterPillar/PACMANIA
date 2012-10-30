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
#include "MsgEntity.h"
#include "MsgLight.h"
#include "MsgZoom.h"

#include "MsgDXWindowHandle.h"

class ObserverDirector : public Component
{
private:
	std::vector<Observer*>* observers;

	void subscribeMsg(Msg* msg);
	void subscribe(
		Component*	subscriber, 
		MsgType		subscription);
	void msgRender(Msg* msg);
	void msgMouseClick(Msg* msg);
	void msgMouseMove(Msg* msg);
	void msgKeyboard(Msg* msg);
	void msgCamera(Msg* msg);
	void msgLight(Msg* msg);
	void msgZoom(Msg* msg);

	// Entity messages
	void msgEntityPlayerPos(Msg* msg)
	{
		MsgType type = msg->Type();
		MsgEntityPlayerPos* msgCast = (MsgEntityPlayerPos*)msg;
		for(unsigned int i = 0; i < observers->size(); i++)
		{
			Observer* observer = observers->at(i);
			if(observer->isSubscriber(type))
			{
				MsgEntityPlayerPos* newInstance = new MsgEntityPlayerPos(msgCast);
				observer->getComponent()->push(newInstance);
			}
		}
		delete msgCast;
	}
	void msgEntityPacmanPos(Msg* msg)
	{
		MsgType type = msg->Type();
		MsgEntityPacmanPos* msgCast = (MsgEntityPacmanPos*)msg;
		for(unsigned int i = 0; i < observers->size(); i++)
		{
			Observer* observer = observers->at(i);
			if(observer->isSubscriber(type))
			{
				MsgEntityPacmanPos* newInstance = new MsgEntityPacmanPos(msgCast);
				observer->getComponent()->push(newInstance);
			}
		}
		delete msgCast;
	}
	void msgEntityGhostPos(Msg* msg)
	{
		MsgType type = msg->Type();
		MsgEntityGhostPos* msgCast = (MsgEntityGhostPos*)msg;
		for(unsigned int i = 0; i < observers->size(); i++)
		{
			Observer* observer = observers->at(i);
			if(observer->isSubscriber(type))
			{
				MsgEntityGhostPos* newInstance = new MsgEntityGhostPos(msgCast);
				observer->getComponent()->push(newInstance);
			}
		}
		delete msgCast;
	}
	void msgEntityPillPos(Msg* msg)
	{
		MsgType type = msg->Type();
		MsgEntityPillPos* msgCast = (MsgEntityPillPos*)msg;
		for(unsigned int i = 0; i < observers->size(); i++)
		{
			Observer* observer = observers->at(i);
			if(observer->isSubscriber(type))
			{
				MsgEntityPillPos* newInstance = new MsgEntityPillPos(msgCast);
				observer->getComponent()->push(newInstance);
			}
		}
		delete msgCast;
	}

	/*win*/
	void msgDXWindowHandle(Msg* msg);

	/*linux*/
	void msgGlut(Msg* msg);
	void msgGlutCallback(Msg* msg);
protected:
public:
	ObserverDirector();
	virtual ~ObserverDirector();

	void init();
	void update(double delta);
};

#endif //OBSERVERDIRECTOR_H
