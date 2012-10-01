#include "LinuxContainer.h"

void LinuxContainer::main(int argc, char** argv)
{
	/*Memleaks*/
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	Singleton<ObserverDirector>::get().init();
	WindowGL*	glWindow	= new WindowGL(argc, argv);
	RendererGL*	glRenderer	= new RendererGL();
	InputGL*	input		= new InputGL();
	CameraGL*	camGL		= new CameraGL(
		F_O_V,
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 
		1.0f, 
		1000.0f, 
		SCREEN_WIDTH, 
		SCREEN_HEIGHT);

	initLinux(
		glWindow, 
		glRenderer, 
		input, 
		camGL);

	Game* game = new Game(
		camGL, 
		glWindow, 
		glRenderer);
	game->run();

	//Clean up
	delete game;
	delete camGL;
	delete input;
	delete glWindow;
	delete glRenderer;
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