#include "Game.h"

void Game::run()
{
	GameEntity* pacman = entityFac->createPacman(VecF3(0.0f, 0.0f, 0.0f));	//tmep

//	GameEntity* pill = entityFac->createPill(VecF3(4.0f, 0.0f, 0.0f));
//	GameEntity* bloodyPill = entityFac->createBloodyPill(VecF3(-3.0f, -2.0f, 3.0f)); 

	do
	{
		double delta = tickTimer();

		pacman->update(delta);
//		pill->update(delta);
//		bloodyPill->update(delta);
		
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