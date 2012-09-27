#include "Windows.h"

/*Windows include*/
#include "renderer/DX/WindowDX.h"
#include "renderer/DX/RendererDX.h"
#include "Renderer/DX/CameraDX.h"

void Windows::main(
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


	while(dxWindow->isActive())
	{
		Singleton<ObserverDirector>::get().update(1.0);

		dxWindow->update(1.0);
		camera->update(1.0f);
		dxRenderer->update(1.0f);
		dxRenderer->renderFrame();
	}
}