#include "Game.h"

#include <iostream>

#include "../Messaging/MsgSound.h"

void Game::run()
{
	SoundEngine* soundEngine = new SoundEngine();

	soundEngine->init();
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_AMBIENT));
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_GHOST));
	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_GHOST, 0.0f));
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_CONSUME));
	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_CONSUME, 0.0f));
	

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

		//
		// Calc sound
		//

		// ghost sound
		if(entities[0])
		{
			float noise =  1.0f - entities[0]->getLightPower();
			if(noise<0.0f)
				noise = 0.0f;
			Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_GHOST, noise));
		}

		// under bloody pills effect sound
		if(entities[0])
		{
			float noise =  (entities[0]->getLightPower() - 1.0f) / 10.0f;
			if(noise<0.0f)
				noise = 0.0f;
			Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_CONSUME, noise));
		}
		
		// Update stuff here
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
			case CONDITION_RESTART:
				restartGame();
				break;
			case CONDITION_GAME_OVER:
				gameOver();
				break;
			case CONDITION_NO_CONDITION:
				throw 0; //someone made a mistake
				break;
			}

			/*Reset everything*/
			curCondition = CONDITION_NO_CONDITION;
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
		curCondition = CONDITION_RESTART;
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
void Game::wonGame()
{
	//Start game over-timer
	curCondition = CONDITION_GAME_OVER;
	conditionTimer->Condition(5.0);	//five sec condition
	conditionTimer->reset();
	conditionTimer->start();
}

void Game::gameOver()
{
	std::string derp = "hherå";
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