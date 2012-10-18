#include "Timer.h"

void Timer::start()
{
	ticking = true;

#ifdef _WIN32
	QueryPerformanceCounter((LARGE_INTEGER*)&startCount);
#else
	gettimeofday(&startCount, NULL);
#endif //_WIN32_GAMETIMER::START
}
void Timer::stop()
{
	ticking = false;

#ifdef _WIN32
	QueryPerformanceCounter(&endCount);
#else
	gettimeofday(&endCount, NULL);
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
#ifdef _WIN32
	if(ticking)
		QueryPerformanceCounter(&endCount);

	startTimeMicroSec	= startCount.QuadPart	* (1000000.0 / frequency.QuadPart);
	endTimeMicroSec		= endCount.QuadPart		* (1000000.0 / frequency.QuadPart);
#else
	if(ticking)
		gettimeofday(&endCount, NULL);
	
	startTimeMicroSec	= (startCount.tv_sec	* 1000000.0) + startCount.tv_usec;
	endTimeMicroSec		= (endCount.tv_sec		* 1000000.0) + endCount.tv_usec;
#endif //_WIN32_GAMETIMER::getElapsedTimeMicroSec

	return endTimeMicroSec - startTimeMicroSec;
}
double Timer::getElapsedTimeMilliSec()
{
	float ms = getElapsedTimeMicroSec();
	return ms * 0.001;
}
double Timer::getElapsedTimeSec()
{
	float ms = getElapsedTimeMicroSec();
	return  ms * 0.000001;
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