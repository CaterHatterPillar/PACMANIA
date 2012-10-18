#include "Timer.h"

void Timer::start()
{
	ticking = true;

#ifdef _WIN32
	QueryPerformanceCounter((LARGE_INTEGER*)&startCount);
	startTimeMicroSec = startCount.QuadPart	* (1000000.0 / frequency.QuadPart);
#else
	gettimeofday(&startCount, NULL);
	startTimeMicroSec	= (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
#endif //_WIN32_GAMETIMER::START

	double secondsLol = startTimeMicroSec * 0.000001;
}
void Timer::stop()
{
	ticking = false;

#ifdef _WIN32
	QueryPerformanceCounter(&endCount);
	endTimeMicroSec = endCount.QuadPart	* (1000000.0 / frequency.QuadPart);
#else
	gettimeofday(&endCount, NULL);
	endTimeMicroSec		= (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
#endif //_WIN32_GAMETIMER_STOP
}
void Timer::reset()
{
	ticking				= true;
    startTimeMicroSec	= 0;
    endTimeMicroSec		= 0;

#ifdef _WIN32
    startCount.QuadPart	= 0;
    endCount.QuadPart	= 0;
#else
    startCount.tv_sec	= startCount.tv_usec	= 0;
    endCount.tv_sec		= endCount.tv_usec		= 0;
#endif //_WIN32_GAMETIMER::RESET
}

double Timer::getElapsedTimeMicroSec()
{
	if(ticking)
		stop();

	return endTimeMicroSec - startTimeMicroSec;
}
double Timer::getElapsedTimeMilliSec()
{
	float ms = getElapsedTimeMicroSec() * 0.001;
	return ms;
}
double Timer::getElapsedTimeSec()
{
	float s = getElapsedTimeMicroSec() * 0.000001;
	return s;
}

Timer::Timer()
{
	ticking				= true;
    startTimeMicroSec	= 0;
    endTimeMicroSec		= 0;

#ifdef _WIN32
    QueryPerformanceFrequency(&frequency);
    startCount.QuadPart	= 0;
    endCount.QuadPart	= 0;
#else
    startCount.tv_sec	= startCount.tv_usec	= 0;
    endCount.tv_sec		= endCount.tv_usec		= 0;
#endif //_WIN32_GAMETIMER::GAMETIMER
}
Timer::~Timer()
{
}