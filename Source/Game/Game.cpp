#include "Game.h"

#include <iostream>

#include "../Messaging/MsgSound.h"

void Game::run()
{
	SoundEngine* soundEngine = new SoundEngine();

	soundEngine->init();
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_AMBIENT));

	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_AMBIENT, 1.0f));

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
		
		handleGameConditions();

		// Update game entities
		update(delta);
		for(int i=0; i<(int)num_entities; i++)
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

void Game::handleGameConditions()
{
	if(conditionTimer->Ticking())
	{
		conditionTimer->tick();
		if(conditionTimer->Condition())
		{
			switch(curCondition)
			{
			case RESTART:
				restartGame();
				break;
			case NO_CONDITION:
				throw 0; //someone made a mistake
				break;
			}

			/*Reset everything*/
			curCondition = NO_CONDITION;
			conditionTimer->stop();
			conditionTimer->reset();
		}
	}
}
void Game::startGame()
{
	gameRunning = true;

	//Zoom in
	VecF3 pacPos = entities[0]->getPosition();
	MsgZoom* zoomMsg = new MsgZoom(pacPos.x, pacPos.y, STATE_ZOOM_IN);
	Singleton<ObserverDirector>::get().push(zoomMsg);
}
void Game::endGame()
{
	if(gameRunning)
	{
		//Start game over-timer
		curCondition = RESTART;
		conditionTimer->Condition(5.0);	//five sec condition
		conditionTimer->reset();
		conditionTimer->start();

		//Zoom out
		VecF3 pacPos = entities[0]->getPosition();
		MsgZoom* zoomMsg = new MsgZoom(pacPos.x, pacPos.y, STATE_ZOOM_OUT);
		Singleton<ObserverDirector>::get().push(zoomMsg);

		gameRunning = false;
	}
}
void Game::restartGame()
{
	//restart game here
	maze->restart();
	for(int i=0; i<(int)entities.size(); i++)
	{
		if(entities[i])
			entities[i]->reset();
	}
	num_entities = 0;
	spawnPacman();

	startGame();
}