#ifndef COMPONENT_H
#define COMPONENT_H

#include "Common.h"
#include "Msg.h"

class Component
{
private:
	std::queue<Msg*> msgs;
protected:

	Msg* pop();
	Msg* peek();
public:
	Component();
	virtual ~Component();

	virtual void update(double delta)	= 0;
	virtual void init()					= 0;

	void push(Msg* msg);
};

#endif //COMPONENT_H