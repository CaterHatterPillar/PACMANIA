#include "Game.h"

void Game::run()
{
	do
	{
		/*Update stuff here*/

		camera->update(1.0);
		renderer->update(1.0);
		window->update(1.0);
		Singleton<ObserverDirector>::get().update(1.0);
	} while(window->isActive());
}