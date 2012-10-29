#ifndef GAME_H
#define GAME_H

#include "GameEntityFactory.h"

#include "../Camera.h"
#include "../Window.h"
#include "../Renderer.h"
#include "../GameTimer.h"

class Game  : public Component
{
private:
	/*Members*/
	bool running;
	GameTimer* gameTimer;

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
		running		= true;
		gameTimer	= new GameTimer();

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
				case INPUT_KEYBOARD_MSG:
					msgKeyboard(msg);
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
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, INPUT_KEYBOARD_MSG));
	}

	void msgKeyboard(Msg* msg)
	{
		MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;
		keyboard(keyboardMsg->Key());
		delete keyboardMsg;
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
};

#endif