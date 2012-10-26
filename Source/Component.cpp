#include "Component.h"

Msg* Component::pop() 
{
	Msg* msg = NULL;
	if(!msgs.empty())
	{
		msg = msgs.front();
		msgs.pop();
	}

	return msg;
}
Msg* Component::peek()
{
	Msg* msg = NULL;
	if(!msgs.empty())
		msg = msgs.front();
	return msg;
}

Component::Component() {}
Component::~Component() 
{ 
	Msg* msg;
	for(unsigned int i = 0; i < msgs.size(); i++)
	{
		msg = msgs.front();
		msgs.pop();
		delete msg;
		//msgs.pop(); //calls message's destructor
	}
}

void Component::push(Msg* msg) 
{ 
	msgs.push(msg); 
}
