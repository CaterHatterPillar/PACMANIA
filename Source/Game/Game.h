#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "GameEntityFactory.h"

#include "../ConditionTimer.h"
#include "../SoundEngine.h"
#include "../Camera.h"
#include "../Window.h"
#include "../Renderer.h"
#include "../GameTimer.h"

#include "../Messaging/MsgZoom.h"
#include "../Messaging/MsgEntity.h"
#include "../Messaging/MsgSound.h"

#include "../Behaviours/ConsumeBehaviour.h"

enum Condition { CONDITION_RESTART, CONDITION_GAME_OVER, CONDITION_NO_CONDITION };

class Game  : public Component
{
private:
	bool gameRunning;

	SoundEngine* soundEngine;

	/*Gametimer*/
	GameTimer* gameTimer;
	
	/*Conditional timer managing transitional events*/
	Condition		curCondition;
	ConditionTimer* conditionTimer;

	/*Ext*/
	Camera*				camera;
	Window*				window;
	Renderer*			renderer;
	GameEntityFactory*	entityFac;
	vector<GameEntity*> entities;
	ConsumeBehaviour*	consumeBehaviour;

	int		num_entities;
	Maze*	maze;
protected:
public:
	void run();

	Game(Camera*			camera,
		Window*				window,
		Renderer*			renderer,
		GameEntityFactory*	entityFac);
	~Game();

	void update(double delta);
	void init();

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
	void msgGameWon(Msg* msg)
	{
		MsgGameWon* gameWonMsg = (MsgGameWon*)msg;
		wonGame();
		delete gameWonMsg;

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
	void wonGame();

	void gameOver();
	void restartGame(); 
};

#endif