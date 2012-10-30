#ifndef GAME_H
#define GAME_H

#include "GameEntityFactory.h"
#include "../ConditionTimer.h"

#include "../Camera.h"
#include "../Window.h"
#include "../Renderer.h"
#include "../GameTimer.h"

#include "../Messaging/MsgZoom.h"
#include "../Messaging/MsgEntity.h"

enum Condition { RESTART, NO_CONDITION };

class Game  : public Component
{
private:
	/*Members*/
	GameTimer* gameTimer;
	bool running;

	/*Condition*/
	Condition curCondition;
	ConditionTimer* conditionTimer;

	/*Ext*/
	Camera*				camera;
	Window*				window;
	Renderer*			renderer;
	GameEntityFactory*	entityFac;
	vector<GameEntity*> entities;
	Maze* maze;
protected:
public:
	void run();

	Game(
		Camera*				camera,
		Window*				window,
		Renderer*			renderer,
		GameEntityFactory*	entityFac)
	{
		running			= true;
		gameTimer		= new GameTimer();

		curCondition	= NO_CONDITION;
		conditionTimer	= new ConditionTimer(-1.0);

		this->camera	= camera;
		this->window	= window;
		this->renderer	= renderer;
		this->entityFac = entityFac;

		init();
	}
	~Game()
	{
		for(int i=0; i<(int)entities.size(); i++)
		{
			if(entities[i])
				delete entities[i];
		}
		if(maze)
			delete maze;
			
		if(gameTimer)
			delete gameTimer;
		if(camera)
			delete camera;
		if(window)
			delete window;
		if(renderer)
			delete renderer;
		if(entityFac)
			delete entityFac;
	}

	void update(double delta)
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
					spawnGhost();
					break;
				case INPUT_KEYBOARD_MSG:
					msgKeyboard(msg);
					break;
				case GAME_OVER:
					msgGameOver(msg);
					break;
				default:
					throw 0; //temp
					break;
				}
			}
		}
	}
	void init()
	{
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_GHOST_SPAWN));
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, GAME_OVER));
	}

	void msgKeyboard(Msg* msg)
	{
		MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;
		keyboard(keyboardMsg->Key());
		delete keyboardMsg;
	}
	void msgGameOver(Msg* msg)
	{
		MsgGameOver* gameOverMsg = (MsgGameOver*)msg;
		endGame();
		delete gameOverMsg;
	}

	void keyboard(KEY key)
	{
		switch(key)
		{
		case KEY_D:
			spawnGhost();
			break;
		default:
			break;
		}
	}

	void spawnGhost()
	{
		GameEntity* entity = entityFac->createGhost(VecI2(3, 1), maze);
		entities.push_back(entity);
	}
	void spawnPacman()
	{
		GameEntity* entity = entityFac->createPacman(VecF3(0.0f, 0.0f, 0.0f), maze);
		entities.push_back(entity);
	}

	void handleGameConditions();
	void startGame();
	void endGame();
	void restartGame(); 
};

#endif