#include "Game.h"

#include <iostream>

void Game::run()
{
	Maze* maze = entityFac->createMaze();
	GameEntity* pacman = entityFac->createPacman(VecF3(0.0f, 0.0f, 0.0f), maze);	//tmep

//	GameEntity* pill = entityFac->createPill(VecF3(4.0f, 0.0f, 0.0f));
//	GameEntity* bloodyPill = entityFac->createBloodyPill(VecF3(-3.0f, -2.0f, 3.0f)); 

	gameTimer->reset();
	gameTimer->start();
	do
	{
		double delta = gameTimer->tick();

		pacman->update(delta);
//		pill->update(delta);
//		bloodyPill->update(delta);
		maze->update(delta);
		
		/*Update stuff here*/
		camera->update(delta);
		window->update(delta);
		renderer->update(delta);
		Singleton<ObserverDirector>::get().update(delta);
		
		renderer->renderFrame();
	} while(window->isActive());

	if(pacman)	//tmep
		delete pacman;
}