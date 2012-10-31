#ifndef GAME_H
#define GAME_H

#include "GameEntityFactory.h"
#include "../ConditionTimer.h"

#include "../SoundEngine.h"

#include "../Camera.h"
#include "../Window.h"
#include "../Renderer.h"
#include "../GameTimer.h"

#include "../Messaging/MsgZoom.h"
#include "../Messaging/MsgEntity.h"

enum Condition { CONDITION_RESTART, CONDITION_GAME_OVER, CONDITION_NO_CONDITION };

class Game  : public Component
{
private:
	/*Members*/
	GameTimer* gameTimer;
	bool gameRunning;

	Condition curCondition;
	ConditionTimer* conditionTimer;

	/*Ext*/
	Camera*				camera;
	Window*				window;
	Renderer*			renderer;
	GameEntityFactory*	entityFac;
	vector<GameEntity*> entities;
	int num_entities;
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
		this->camera	= camera;
		this->window	= window;
		this->renderer	= renderer;
		this->entityFac = entityFac;

		gameTimer		= new GameTimer();
		conditionTimer	= new ConditionTimer(-1.0);
		curCondition	= CONDITION_NO_CONDITION;

		entities.resize(20);
		num_entities = 0;
		for(int i=0; i<(int)entities.size(); i++)
			entities[i]=0;
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
		if(conditionTimer)
			delete conditionTimer;

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
					msgSpawnGhost(msg);
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
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, INPUT_KEYBOARD_MSG));
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, GAME_OVER));
	}

	void msgSpawnGhost(Msg* msg)
	{
		spawnGhost();
		delete msg;
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
		case KEY_W:
			endGame();
			break;
		default:
			break;
		}
	}

	void spawnGhost()
	{
		if(num_entities<(int)entities.size())
		{
			if(entities[num_entities] == 0)
			{
				GameEntity* entity = entityFac->createGhost(VecI2(3, 1), maze);
				entities[num_entities]=entity;
			}
			num_entities++;
		}
	}
	void spawnPacman()
	{
		if(entities[num_entities] == 0)
		{
			GameEntity* entity = entityFac->createPacman(VecF3(0.0f, 0.0f, 0.0f), maze);
			entities[num_entities]=entity;
		}
		num_entities++;
	}

	void handleGameConditions();
	void startGame();
	void endGame();
	void restartGame(); 
};

#endif