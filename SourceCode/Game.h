#ifndef GAME_H
#define GAME_H

#include "Renderer/Camera.h"
#include "Renderer/Window.h"
#include "Renderer/Renderer.h"

class Game
{
private:
	bool running;

	Camera*		camera;
	Window*		window;
	Renderer*	renderer;
protected:
public:
	void run();

	Game(
		Camera*		camera,
		Window*		window,
		Renderer*	renderer)
	{
		running = true;

		this->camera	= camera;
		this->window	= window;
		this->renderer	= renderer;
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