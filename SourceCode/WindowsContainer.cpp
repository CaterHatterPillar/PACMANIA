#include "WindowsContainer.h"
#include "Game/Game.h"

/*Windows include*/
#include "Renderer/DX/WindowDX.h"
#include "Renderer/DX/RendererDX.h"
#include "Renderer/DX/CameraDX.h"
#include "Game/GameEntity.h"
#include "Renderer/DX/GraphicsContainerDX.h"

void WindowsContainer::main(

	HINSTANCE	hInstance, 
	HINSTANCE	hPrevInstance, 
	LPSTR		lpCmdLine, 
	int			nCmdShow)
{
	Singleton<ObserverDirector>::get().init();


	WindowDX*	dxWindow	= new WindowDX(hInstance, nCmdShow);
	RendererDX*	dxRenderer	= new RendererDX();
	CameraDX*	dxCamera	= new CameraDX(
		(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 
		(float)PI/4, 
		100.0f, 
		1.0f);
	initWindows(
		dxWindow, 
		dxRenderer, 
		dxCamera);

	
	GameEntity* gameEntity = new GameEntity(VecF3(0.0f, 0.0f, 0.0f), VecF3(0.0f, 0.0f, 0.0f), VecF3(1.0f, 1.0f, 1.0f));
	vector<PosNormTex>* vertices = new vector<PosNormTex>;
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 0.0f)));   
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, 1.0f),		VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 1.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 1.0f)));																				 
	
	std::vector<unsigned int>* indices = new std::vector<unsigned int>();
	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(3);
	

	GraphicsContainer* graphicsContainer = new GraphicsContainerDX( 
		VERTEX_SHADER_DEFAULT, 
		PIXEL_SHADER_DEFAULT,
		TEXTURE_PACMAN,
		vertices, 
		indices, 
		vertices->size(), 
		indices->size(), 
		8, 
		sizeof(PosNormTex), 
		0);

	gameEntity->setGraphicsContainer(graphicsContainer);
	
	MoveBehaviour* moveBehaviour = new MoveBehaviourPlayer();
	moveBehaviour->init();
	gameEntity->setMoveBehaviour(moveBehaviour);


	Game* game = new Game(dxCamera, dxWindow, dxRenderer, gameEntity);
	game->run();

	/*CleanUp*/
	delete game;
}

void WindowsContainer::initWindows(
		WindowDX*	dxWindow,
		RendererDX*	dxRenderer,
		CameraDX*	dxCamera)
{
	dxWindow->init();

	Singleton<ObserverDirector>::get().update(1.0);
	dxRenderer->update(1.0f);

	dxRenderer->init();

	dxCamera->init();
}