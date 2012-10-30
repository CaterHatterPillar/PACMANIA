#ifndef CONDITIONTIMER_H
#define CONDITIONTIMER_H

#include "Timer.h"

class ConditionTimer
{
private:
	bool	ticking;
	double	timeSec;
	double	conditionSec;

	bool condition;

	Timer* timer;
protected:
	bool poll();
public:
	void tick();
	void reset();
	void start();
	void stop();

	ConditionTimer(double conditionSec);
	~ConditionTimer();

	bool Condition()	{ return condition;	}
	bool Ticking()		{ return ticking;	}	
	void Condition(double conditionSec) { this->conditionSec = conditionSec; }
};

#endif //CONDITIONTIMER_H