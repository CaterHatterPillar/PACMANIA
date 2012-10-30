#include "ConditionTimer.h"

void ConditionTimer::tick()
{
	if(ticking)
	{
		//Stop timer to get estimate
		timer->stop();

		timeSec += timer->getElapsedTimeSec();
		condition = poll();

		//Reset and start timer to measure next
		timer->reset();
		timer->start();
	} 
}
void ConditionTimer::reset()
{
	timeSec = 0.0;
	timer->reset();
	timer->start();

	ticking		= true;
	condition	= false;
}
void ConditionTimer::start()
{
	timer->reset();
	timer->start();
		
	ticking	= true;
}
void ConditionTimer::stop()
{
	ticking = false;
}

bool ConditionTimer::poll()
{
	bool condition;
	if(timeSec >= conditionSec)
		condition = true;
	else
		condition = false;
	return condition;
}

ConditionTimer::ConditionTimer(double conditionSec)
{
	timeSec		= 0.0;
	ticking		= false;
	condition	= false;

	timer = new Timer();

	this->conditionSec = conditionSec;
}
ConditionTimer::~ConditionTimer()
{
}