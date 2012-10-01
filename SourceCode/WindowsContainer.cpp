#include "WindowsContainer.h"

/*Windows include*/
#include "renderer/DX/WindowDX.h"
#include "renderer/DX/RendererDX.h"
#include "Renderer/DX/CameraDX.h"
#include "GameEntity.h"
#include "Renderer/DX/GraphicsContainerDX.h"

void WindowsContainer::main(

	HINSTANCE	hInstance, 
	HINSTANCE	hPrevInstance, 
	LPSTR		lpCmdLine, 
	int			nCmdShow)
{
	Singleton<ObserverDirector>::get().init();

	WindowDX* dxWindow = new WindowDX(hInstance, nCmdShow);
	RendererDX* dxRenderer = new RendererDX();

	dxWindow->init();

	Singleton<ObserverDirector>::get().update(1.0);

	dxRenderer->update(1.0f);
	dxRenderer->init();

	Camera* camera = new CameraDX((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, PI/4, 100.0f, 1.0f);
	camera->init();

	GameEntity* gameEntity = new GameEntity(VecF3(0.0f, 0.0f, 0.0f), VecF3(0.0f, 0.0f, 0.0f), VecF3(1.0f, 1.0f, 1.0f));
	
	vector<PosNormTex>* vertices = new vector<PosNormTex>;
	vertices->push_back(PosNormTex(VecF3(-1.0f, 1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(0.0f, 0.0f)));   
	vertices->push_back(PosNormTex(VecF3(1.0f, 1.0f, 1.0f),		VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(-1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 0.0f)));
	vertices->push_back(PosNormTex(VecF3(1.0f, -1.0f, 1.0f),	VecF3(0.0f, 0.0f, 1.0f),	VecF2(1.0f, 1.0f)));																				 
	

	std::vector<unsigned int>* indices = new std::vector<unsigned int>();
	indices->push_back(0);
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(2);
	indices->push_back(1);
	indices->push_back(3);

	GraphicsContainer* graphicsContainer = new GraphicsContainerDX(
		"root/Textures/PacmanTex.png", 
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

	while(dxWindow->isActive())
	{
		Singleton<ObserverDirector>::get().update(1.0);

		dxWindow->update(1.0);
		camera->update(1.0f);

		gameEntity->update(1.0f);

		dxRenderer->update(1.0f);
		dxRenderer->renderFrame();
	}
}