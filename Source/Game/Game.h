#ifndef GAME_H
#define GAME_H

#include "GameEntity.h"
#include "GameEntityFactory.h"

#include "../Camera.h"
#include "../Window.h"
#include "../Renderer.h"
#include "../GameTimer.h"

class Game
{
private:
	/*Members*/
	bool running;
	GameTimer* gameTimer;

	/*Ext*/
	Camera*				camera;
	Window*				window;
	Renderer*			renderer;
	GameEntityFactory*	entityFac;
protected:
public:
	void run();

	Game(
		Camera*				camera,
		Window*				window,
		Renderer*			renderer,
		GameEntityFactory*	entityFac)
	{
		running		= true;
		gameTimer	= new GameTimer();

		this->camera	= camera;
		this->window	= window;
		this->renderer	= renderer;
		this->entityFac = entityFac;
	}
	~Game()
	{
		if(gameTimer)
			delete gameTimer;

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