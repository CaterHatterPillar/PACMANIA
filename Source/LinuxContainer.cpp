#include "LinuxContainer.h"

void LinuxContainer::mainContainer(int argc, char** argv)
{
	Singleton<ObserverDirector>::get().init();
	WindowGL*	glWindow	= new WindowGL(argc, argv);
	RendererGL*	glRenderer	= new RendererGL();
	InputGL*	glInput		= new InputGL();
	CameraGL*	glCamera	= new CameraGL(
		(float)F_O_V,
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 
		(float)Z_NEAR, 
		(float)Z_FAR,
		ZOOMED_IN,
		ZOOMED_OUT);

	initLinux(
		glWindow, 
		glRenderer, 
		glInput, 
		glCamera);

	GameEntityFactory* glFactory = new GameEntityFactoryGL();

	Game* game = new Game(
		glCamera, 
		glWindow, 
		glRenderer,
		glFactory);
	game->run();

	DELETE_NULL(glInput); //handled via callbacks outside of game
	DELETE_NULL(game);
}

void LinuxContainer::initLinux(
	WindowGL*	windowGL, 
	RendererGL*	rendererGL,
	InputGL*	inputGL,
	CameraGL*	cameraGL)
{
	windowGL->init();
	rendererGL->init();
	cameraGL->init();
	inputGL->init();
}