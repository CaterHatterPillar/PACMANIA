#include "GameTimer.h"

double GameTimer::tick()
{
	if(!ticking)
		deltaTime = 0.0;
	else
	{
		//Stop timer to get estimate
		timer->stop();

		deltaTime = timer->getElapsedTimeSec();
		if(deltaTime < 0.0) //This may indeed happen
			deltaTime = 0.0;

		//Reset and start timer to measure next
		timer->reset();
		timer->start();
	} 

	return deltaTime;
}
void GameTimer::reset()
{
	timer->reset();
	timer->start();

	ticking = true;
}
void GameTimer::start()
{
	if(!ticking)
	{
		timer->reset();
		timer->start();
		
		ticking		= true;
	}
}
void GameTimer::stop()
{
	if(ticking)
		ticking = false;
}

GameTimer::GameTimer()
{
	ticking = true;

	deltaTime	= -1.0;

	timer = new Timer();
}
GameTimer::~GameTimer()
{
	if(timer)
		delete timer;
}