#include "Game.h"

void Game::run()
{
	do
	{
		double delta = tickTimer();
		
		/*Update stuff here*/
		pacman->update(delta);
		camera->update(delta);
		window->update(delta);
		renderer->update(delta);
		Singleton<ObserverDirector>::get().update(delta);
		
		renderer->renderFrame();
	} while(window->isActive());
}