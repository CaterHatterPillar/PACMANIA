#include "Game.h"

void Game::run()
{
	do
	{
		double delta = tickTimer();
		/*Update stuff here*/

		camera->update(delta);
		renderer->update(delta);
		window->update(delta);
		Singleton<ObserverDirector>::get().update(delta);
	} while(window->isActive());
}