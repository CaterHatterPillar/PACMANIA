#include "Game.h"

#include <iostream>

#include "../Messaging/MsgSound.h"

void Game::run()
{
	SoundEngine* soundEngine = new SoundEngine();

	soundEngine->init();
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_AMBIENT, false));

	maze = entityFac->createMaze();
	spawnPacman();

//	GameEntity* pill = entityFac->createPill(VecF3(4.0f, 0.0f, 0.0f));
//	GameEntity* bloodyPill = entityFac->createBloodyPill(VecF3(-3.0f, -2.0f, 3.0f)); 

	startGame();

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
		soundEngine->update(delta);

		renderer->renderFrame();
	} while(window->isActive());
}

void Game::startGame()
{
	//Zoom in
	VecF3 pacPos = entities[0]->getPosition();
	MsgZoom* zoomMsg = new MsgZoom(pacPos.x, pacPos.y, STATE_ZOOM_IN);
	Singleton<ObserverDirector>::get().push(zoomMsg);
}
void Game::endGame()
{
}