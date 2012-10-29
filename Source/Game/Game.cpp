#include "Game.h"

#include <iostream>

void Game::run()
{
	maze = entityFac->createMaze();
	spawnPacman();
	spawnGhost();

//	GameEntity* pill = entityFac->createPill(VecF3(4.0f, 0.0f, 0.0f));
//	GameEntity* bloodyPill = entityFac->createBloodyPill(VecF3(-3.0f, -2.0f, 3.0f)); 

	gameTimer->reset();
	gameTimer->start();
	do
	{
		double delta = gameTimer->tick();

		// Update game entities
		update(delta);
		for(int i=0; i<(int)entities.size(); i++)
			entities[i]->update(delta);
		maze->update(delta);
		
		/*Update stuff here*/
		camera->update(delta);
		window->update(delta);
		renderer->update(delta);
		Singleton<ObserverDirector>::get().update(delta);
		
		renderer->renderFrame();
	} while(window->isActive());
}