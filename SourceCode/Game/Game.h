#ifndef GAME_H
#define GAME_H

#include "GameEntity.h"
#include "../GameEntityFactory.h"

#include "../Camera.h"
#include "../Window.h"
#include "../Renderer.h"

class Game
{
private:
	/*Members*/
	bool running;

	/*Ext*/
	Camera*				camera;
	Window*				window;
	Renderer*			renderer;
	GameEntityFactory*	entityFac;
protected:
public:
	void run();

	double tickTimer()
	{
		#ifdef _WIN32

		// Compute seconds per count
		static bool first = true;
		static double secondsPerCount = 0;
		// BAD HACK: It's not pretty, but it's works without affecting other code, should probably be refactored into separate class later on
		if(first)
		{
			__int64 countsPerSec;
			QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
			secondsPerCount=1.0/(double)countsPerSec;
		}

		// Get current time
		__int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		// BAD HACK: Fist time init of previousTime
		static __int64 previousTime = currentTime;

		// Compute "deltaTime"
		double deltaTime = (currentTime-previousTime)*secondsPerCount;

		// Update previous time
		previousTime = currentTime;

		// Prevent scenario where "deltaTime" can become negative 
		if(deltaTime < 0.0)
			deltaTime = 0.0;

		return deltaTime;
		#else
		
		return 1.0/1000;

		#endif //_WIN32
	}
	Game(
		Camera*				camera,
		Window*				window,
		Renderer*			renderer,
		GameEntityFactory*	entityFac)
	{
		running = true;

		this->camera	= camera;
		this->window	= window;
		this->renderer	= renderer;
		this->entityFac = entityFac;
	}
	~Game()
	{
		if(camera)
			delete camera;
		if(window)
			delete window;
		if(renderer)
			delete renderer;
		if(entityFac)
			delete entityFac;
	}
};

#endif //GAME_H