#ifndef GAME_H
#define GAME_H

#include "Renderer/Camera.h"
#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "GameTimer.h"

class Game
{
private:
	/*Members*/
	bool		running;
	GameTimer*	gameTimer;

	/*Ext*/
	Camera*		camera;
	Window*		window;
	Renderer*	renderer;
protected:
public:
	void run();

	double tickTimer()
	{
		gameTimer->tick();
		double delta = gameTimer->getDeltaTime();

		static int frameCount = 0;
		static float t_base = 0.0f;
		frameCount++;

		/*Calculate frames per second*/
		if((gameTimer->getGameTime() - t_base) >= 1.0f)
		{
			float fps = (float)frameCount;	//Frames per second
			float mspf = 1000.0f / fps;		//Milliseconds per frame

			//Msg* msg = new DebugMsg((int)fps, FPS);
			//Singleton<ObserverDirector>::get().push(msg);

			//Reset for next average
			frameCount = 0;
			t_base += 1.0f;
		}

		return delta;
	}
	Game(
		Camera*		camera,
		Window*		window,
		Renderer*	renderer)
	{
		running = true;

		this->camera	= camera;
		this->window	= window;
		this->renderer	= renderer;

		gameTimer = new GameTimer();
		gameTimer->reset();
	}
	~Game()
	{
	}
};

#endif //GAME_H

/*
testEntity = new GameEntity(VecF3(1.0f, 1.0f, 1.0f), VecF3(1.0f, 1.0f, 1.0f), VecF3(1.0f, 1.0f, 1.0f));
std::vector<PosNormTex>* vertices = new std::vector<PosNormTex>();
PosNormTex vertex;
vertex.pos = VecF3(-1.0f, -1.0f, 0.0f);
vertices->push_back(vertex);
vertex.pos = VecF3(0.0f, -1.0f, 1.0f);
vertices->push_back(vertex);
vertex.pos = VecF3(1.0f, -1.0f, 0.0f);
vertices->push_back(vertex);
vertex.pos = VecF3(0.0f, 1.0f, 0.0f);
vertices->push_back(vertex);
std::vector<unsigned int>* indices = new std::vector<unsigned int>();
indices->push_back(0);
indices->push_back(3);
indices->push_back(1);
indices->push_back(1);
indices->push_back(3);
indices->push_back(2);
indices->push_back(2);
indices->push_back(3);
indices->push_back(0);
indices->push_back(0);
indices->push_back(2);
indices->push_back(1);
unsigned int numVertices = 4;
unsigned int numIndices = 12;
unsigned int numFaces = 4;
unsigned int stride = sizeof(PosNormTex);
unsigned int offset = 0;
GraphicsContainerGL* graphicsContainer = new GraphicsContainerGL(
VERTEX_SHADER_DEFAULT,
PIXEL_SHADER_DEFAULT,
vertices,
indices,
numVertices,
numIndices,
numFaces,
stride,
offset);
testEntity->setGraphicsContainer(graphicsContainer);
*/