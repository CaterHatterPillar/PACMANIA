#include "WindowsContainer.h"
#include "Game/Game.h"

/*Windows include*/
#include "DX/WindowDX.h"
#include "DX/RendererDX.h"
#include "DX/CameraDX.h"
#include "Game/GameEntity.h"
#include "DX/GraphicsContainerDX.h"
#include "DX/GameEntityFactoryDX.h"

void WindowsContainer::main(

	HINSTANCE	hInstance, 
	HINSTANCE	hPrevInstance, 
	LPSTR		lpCmdLine, 
	int			nCmdShow)
{
	Singleton<ObserverDirector>::get().init();
	Singleton<PlatformCheck>::get().openGL = false;


	WindowDX*	dxWindow	= new WindowDX(hInstance, nCmdShow);
	RendererDX*	dxRenderer	= new RendererDX();
	CameraDX*	dxCamera	= new CameraDX(
		(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 
		(float)PI/4, 
		Z_FAR, 
		Z_NEAR,
		ZOOMED_IN,
		ZOOMED_OUT);
	initWindows(
		dxWindow, 
		dxRenderer, 
		dxCamera);

	GameEntityFactory* factory = new GameEntityFactoryDX();


	Game* game = new Game(dxCamera, dxWindow, dxRenderer, factory);
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