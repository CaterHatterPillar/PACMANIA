#ifndef GAMETIMER_H
#define GAMETIMER_H

#include "Timer.h"

class GameTimer
{
private:
	bool ticking;
	Timer* timer;

	/*Milli Secs*/
	double deltaTime;
	double prevTime;
	double curTime;	
protected:
public:
	double tick();
	void reset();
	void start();
	void stop();

	GameTimer();
	virtual ~GameTimer();
};

#endif //GAMETIMER_H