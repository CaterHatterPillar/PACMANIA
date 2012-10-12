#include "Game.h"

void Game::run()
{
	GameEntity* pacman = entityFac->createPacman(VecF3(0.0f, 0.0f, 0.0f));	//tmep

	do
	{
		double delta = tickTimer();

		pacman->update(delta);
		
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