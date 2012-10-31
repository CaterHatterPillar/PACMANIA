#include "Game.h"

void Game::run()
{
	/*Start original game session*/
	maze = entityFac->createMaze();
	spawnPacman();
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

void Game::init()
{
	/*Subscribe to relevant msgs*/
	Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_GHOST_SPAWN));
	Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, INPUT_KEYBOARD_MSG));
	Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, GAME_OVER));

	/*Initialize sound engine*/
	soundEngine->init();
	Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_AMBIENT));
	Singleton<ObserverDirector>::get().push(new MsgSoundVolume(SOUND_AMBIENT, 1.0f));
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
	consumeBehaviour = new ConsumeBehaviour();

	entities.resize(20);
	num_entities = 0;
	for(int i=0; i<(int)entities.size(); i++)
		entities[i]=0;
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