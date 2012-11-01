#include "ConsumeBehaviour.h"

void ConsumeBehaviour::init()
{
	/*Subscribe to relevant msgs*/
	SubscriptionMsg* sub = new SubscriptionMsg(this, CONSUME);
	Singleton<ObserverDirector>::get().push(sub);
	sub = new SubscriptionMsg(this, CAMERA);
	Singleton<ObserverDirector>::get().push(sub);

	entity->setPosition(VecF3(0.0f, 0.0f, ZOOMED_OUT + 250));
	entity->setScale(VecF3(1.0f, 1.0f, 1.0f));	//change this
	
	if(Singleton<PlatformCheck>::get().openGL)
		entity->setRotation(VecF3(180.0f, 0.0f, 0.0f));
}
void ConsumeBehaviour::update(double delta)
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
			case CONSUME:
				msgConsume(msg);
				break;
			case CAMERA:
				msgCamera(msg);
				break;
			default:
				throw 0;
				break;
			}
		}
	}
	
	/*Update event-timer*/
	if(eventTimer->Ticking())
	{
		eventTimer->tick();
		if(eventTimer->Condition())
		{
			switch(state)
			{
			case CONSUME_STATE_DISPLAY:
				displayConsume();
				break;
			case CONSUME_NO_STATE:
				throw 0; //someone made a mistake
				break;
			}

			/*Reset everything*/
			state = CONSUME_NO_STATE;
			eventTimer->stop();
			eventTimer->reset();
		}
	}

	if(interpolPos)
	{
		VecF3 pos = entity->getPosition();
		float lerpFac = interPolFac * delta;
		pos.z = lerp(pos.z, ZOOMED_OUT, lerpFac);
		entity->setPosition(pos);
		if(pos.z <= ZOOMED_OUT + 5)
		{
			pos.z = ZOOMED_OUT + 5;
			interpolPos = false;
		}
	}

	entity->update(delta);
}

void ConsumeBehaviour::displayEvent()
{
	state = CONSUME_STATE_DISPLAY;

	eventTimer->reset();
	eventTimer->start();
}
void ConsumeBehaviour::displayConsume()
{
	entity->setRender(true);
	interpolPos = true;
}

ConsumeBehaviour::ConsumeBehaviour(GameEntity* entity)
{
	this->entity = entity;
	this->entity->setRender(false);

	state = CONSUME_NO_STATE;
	eventTimer = new ConditionTimer(eventCondition);

	interpolPos = false;
}
ConsumeBehaviour::~ConsumeBehaviour()
{
	if(entity)
		delete entity;

	if(eventTimer)
		delete eventTimer;
}

void ConsumeBehaviour::msgConsume(Msg* msg)
{
	MsgConsume* consumeMsg = (MsgConsume*)msg;
	
	ConsumeState state = consumeMsg->getState();
	switch(state)
	{
	case CONSUME_STATE_DISPLAY:
		displayEvent();
		break;
	default:
		throw 0; //something went terribly wrong
		break;
	}
	
	delete consumeMsg;
}
void ConsumeBehaviour::msgCamera(Msg* msg)
{
	MsgCamera* posMsg = (MsgCamera*)msg;
	
	VecF3 newPos	= posMsg->CameraPosition();
	VecF3 curPos	= entity->getPosition();
	newPos.z		= curPos.z;	//keep z-val
	entity->setPosition(newPos);

	delete posMsg;
}