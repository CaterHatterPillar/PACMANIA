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

	void msgSpawnGhost(Msg* msg);
	void msgKeyboard(Msg* msg);
	void msgGameOver(Msg* msg);
	void msgGameWon(Msg* msg);

	void keyboard(KEY key);

	void spawnGhost();
	void spawnPacman();

	void handleGameConditions();
	void startGame();
	void endGame();
	void wonGame();

	void gameOver();
	void restartGame(); 
};

#endif