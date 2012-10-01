#include "Game.h"

void Game::run()
{
	do
	{
		double delta = tickTimer();
		
		/*Update stuff here*/
		pacman->update(delta);
		camera->update(delta);
		renderer->update(delta);
		window->update(delta);
		Singleton<ObserverDirector>::get().update(delta);

		renderer->renderFrame();
	} while(window->isActive());
}