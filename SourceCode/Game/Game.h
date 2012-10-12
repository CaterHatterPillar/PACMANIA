#ifndef GAME_H
#define GAME_H

#include "../Renderer/Camera.h"
#include "../Renderer/Window.h"
#include "../Renderer/Renderer.h"
#include "GameEntity.h"

class Game
{
private:
	/*Members*/
	bool		running;

	/*Ext*/
	Camera*		camera;
	Window*		window;
	Renderer*	renderer;
	GameEntity* pacman;
protected:
public:
	void run();

	float tickTimer()
	{
		float delta = 1.0f;
		return delta;
	}
	Game(
		Camera*		camera,
		Window*		window,
		Renderer*	renderer,
		GameEntity*	pacman)
	{
		running = true;

		this->camera	= camera;
		this->window	= window;
		this->renderer	= renderer;
		this->pacman	= pacman;
	}
	~Game()
	{
		if(pacman)
			delete pacman;
		if(camera)
			delete camera;
		if(window)
			delete window;
		if(renderer)
			delete renderer;
	}
};

#endif //GAME_H