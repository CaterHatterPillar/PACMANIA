#ifndef TIMER_H
#define TIMER_H

#include <stdlib.h>

//High precision time measurements are system specific
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif //_WIN32_GAMETIMER::INCLUDES

class Timer
{
private:
	bool	ticking;

	double	startTimeMicroSec;
	double	endTimeMicroSec;

#ifdef _WIN32
	LARGE_INTEGER frequency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
#else
	timeval startCount;
	timeval endCount;
#endif //_WIN32_TIMER

protected:
public:
	void start();
    void stop();
	void reset();

    double getElapsedTimeMicroSec();
	double getElapsedTimeMilliSec();
	double getElapsedTimeSec();

	Timer();
	~Timer();
};

#endif //TIMER_H