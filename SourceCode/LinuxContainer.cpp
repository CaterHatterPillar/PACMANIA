#include "LinuxContainer.h"

void LinuxContainer::mainContainer(int argc, char** argv)
{
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

	GameEntity* pacman = initPacman();

	Game* game = new Game(
		camGL, 
		glWindow, 
		glRenderer,
		pacman);
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
GameEntity* LinuxContainer::initPacman()
{
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

	GraphicsContainer* graphicsContainer = new GraphicsContainerGL( 
		VERTEX_SHADER_DEFAULT, 
		PIXEL_SHADER_DEFAULT, 
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

	return gameEntity;
}
