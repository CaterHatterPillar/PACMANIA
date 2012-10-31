#include "ConsumeBehaviour.h"

void ConsumeBehaviour::init()
{
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
			default:
				throw 0;
				break;
			}
		}
	}
}

ConsumeBehaviour::ConsumeBehaviour(GameEntity* entity)
{
	this->entity = entity;

	eventTimer = new ConditionTimer(eventCondition);
}
ConsumeBehaviour::~ConsumeBehaviour()
{
	if(entity)
		delete entity;
}