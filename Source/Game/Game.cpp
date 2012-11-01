#include "Game.h"

void Game::run()
{
	//SoundEngine* soundEngine = new SoundEngine();
	//
	soundEngine->init();
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_AMBIENT));
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_GHOST));
	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_GHOST, 0.0f));
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_CONSUME));
	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_CONSUME, 0.0f));

	maze = entityFac->createMaze();
	spawnPacman();
	startGame();

	gameTimer->reset();
	gameTimer->start();
	do
	{
		double delta = gameTimer->tick();
		
		handleGameConditions();

		/*Update itself*/
		update(delta);

		// Update game entities
		for(int i=0; i<(int)entities.size(); i++)
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
			if(noise>0.7f)
				noise = 0.7f;
			Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_GHOST, noise));
		}

		// under bloody pills effect sound
		if(entities[0] && gameRunning)
		{
			float noise =  (entities[0]->getLightPower() - 1.0f);
			if(noise<-1.0f)
				noise = noise;
			if(noise<0.0f)
				noise = 0.0f;
			if(noise>0.5f)
				noise = 0.5f;
			Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_CONSUME, noise));
		}
	
		if(curCondition == CONDITION_GAME_OVER)
		{
			float volume = 1 - (conditionTimer->getTimeSec() / conditionTimer->getConditionSec());
			Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_CONSUME, volume));
			Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_AMBIENT, volume));
		}
		
		// Update stuff here
		camera->update(delta);
		window->update(delta);
		renderer->update(delta);
		Singleton<ObserverDirector>::get().update(delta);
		soundEngine->update(delta);
		consumeBehaviour->update(delta);

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
		Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_GHOST, 0.0f));
		Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_CONSUME, 0.5f));

		//Start game over-timer
		curCondition = CONDITION_RESTART;
		conditionTimer->Condition(3.0);	//five sec condition
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
	/*Play sound*/
	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_CONSUME, 0.7f));

	/*Consume*/
	MsgConsume* consumeMsg = new MsgConsume(CONSUME_STATE_DISPLAY);
	Singleton<ObserverDirector>::get().push(consumeMsg);

	/*Zoom*/
	VecF3 pacPos = entities[0]->getPosition();
	MsgZoom* zoomMsg = new MsgZoom(pacPos.x, pacPos.y, STATE_ZOOM_OUT);
	Singleton<ObserverDirector>::get().push(zoomMsg);

	/*Start game over-event*/
	curCondition = CONDITION_GAME_OVER;
	conditionTimer->Condition(10.0);	//five sec condition
	conditionTimer->reset();
	conditionTimer->start();

	gameRunning = false;
}

void Game::gameOver()
{
	window->setActive(false);
}
void Game::restartGame()
{
	//restart game here
	maze->restart();
	for(int i=0; i<(int)entities.size(); i++)
	{
		entities[i]->deactivate();
	}
	//HACK: Activate pacman (not safe)
	entities[0]->reset();

	num_entities = 0;
	spawnPacman();
	startGame();
}

void Game::init()
{
	/*Subscribe to relevant msgs*/
	Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_GHOST_SPAWN));
	Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, INPUT_KEYBOARD_MSG));
	Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, GAME_OVER));
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, GAME_WON));

	/*Initialize sound engine*/
	//soundEngine->init();
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_AMBIENT));
	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_AMBIENT, 1.0f));

	consumeBehaviour->init();
}
void Game::update(double delta)
{
	Msg* msg = peek();
	while(msg)
	{
		msg = pop();
		if(msg)
		{
			MsgType type = msg->Type();
			switch(type)
			{
			case ENTITY_GHOST_SPAWN:
				msgSpawnGhost(msg);
				break;
			case INPUT_KEYBOARD_MSG:
				msgKeyboard(msg);
				break;
			case GAME_OVER:
				msgGameOver(msg);
				break;
			case GAME_WON:
				msgGameWon(msg);
				break;
			default:
				throw 0; //temp
				break;
			}
		}
	}
}

Game::Game(
	Camera*				camera,
	Window*				window,
	Renderer*			renderer,
	GameEntityFactory*	entityFac)
{
	this->camera	= camera;
	this->window	= window;
	this->renderer	= renderer;
	this->entityFac = entityFac;

	soundEngine = new SoundEngine();

	gameTimer		= new GameTimer();
	conditionTimer	= new ConditionTimer(-1.0);
	curCondition	= CONDITION_NO_CONDITION;

	/*Create consumer*/
	GameEntity* consumer = entityFac->createConsume(VecF3(0.0f, 0.0f, 0.0f));
	consumeBehaviour = new ConsumeBehaviour(consumer);

	num_entities = 0;
	init();
}
Game::~Game()
{
	for(int i=0; i<(int)entities.size(); i++)
	{
		if(entities[i])
			delete entities[i];
	}
	if(maze)
		delete maze;

	//if(soundEngine)
	//	delete soundEngine;
		
	if(gameTimer)
		delete gameTimer;
	if(conditionTimer)
		delete conditionTimer;

	if(consumeBehaviour)
		delete consumeBehaviour;

	if(camera)
		delete camera;
	if(window)
		delete window;
	if(renderer)
		delete renderer;
	if(entityFac)
		delete entityFac;
}

void Game::msgSpawnGhost( Msg* msg )
{
	spawnGhost();
	delete msg;
}

void Game::msgKeyboard( Msg* msg )
{
	MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;
	keyboard(keyboardMsg->Key());
	delete keyboardMsg;
}

void Game::msgGameOver( Msg* msg )
{
	MsgGameOver* gameOverMsg = (MsgGameOver*)msg;
	endGame();
	delete gameOverMsg;
}

void Game::msgGameWon( Msg* msg )
{
	MsgGameWon* gameWonMsg = (MsgGameWon*)msg;
	wonGame();
	delete gameWonMsg;
}

void Game::keyboard( KEY key )
{
	switch(key)
	{
	case KEY_D:
		spawnGhost();
		break;
	case KEY_W:
		Singleton<ObserverDirector>::get().push(new MsgGameWon());
		break;
	case KEY_S:
		Singleton<ObserverDirector>::get().push(new MsgEntityPillBloodyEaten());
		break;
	case KEY_A:
		endGame();
		break;
	default:
		break;
	}
}

void Game::spawnGhost()
{
	if(num_entities<(int)entities.size())
	{
		entities[num_entities]->reset();
	}
	else
	{
		GameEntity* entity = entityFac->createGhost(VecI2(3, 1), maze);
		entities.push_back(entity);
	}
	num_entities++;
}

void Game::spawnPacman()
{
	if(num_entities<(int)entities.size())
	{
		entities[num_entities]->reset();
	}
	else
	{
		GameEntity* entity = entityFac->createPacman(VecF3(0.0f, 0.0f, 0.0f), maze);
		entities.push_back(entity);
	}
	num_entities++;
}
