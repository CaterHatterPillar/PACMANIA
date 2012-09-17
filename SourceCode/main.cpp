#define WINDOWS

/*Common include*/
#include "Singleton.h"
#include "Messaging/ObserverDirector.h"
#include "Common.h"

#ifdef WINDOWS
/*Windows include*/
#include "renderer/DX/WindowDX.h"
#include "renderer/DX/RendererDX.h"

int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	Singleton<ObserverDirector>::get().init();

	WindowDX* dxWindow = new WindowDX(hInstance, nCmdShow);
	RendererDX* dxRenderer = new RendererDX();

	dxWindow->init();

	Singleton<ObserverDirector>::get().update(1.0);

	dxRenderer->update(1.0f);
	dxRenderer->init();


	while(true)
	{
		dxWindow->update(1.0);
	}
}
#endif

#ifndef WINDOWS
/*Linux include*/
#include "Renderer/GL/WindowGL.h"
#include "Renderer/GL/RendererGL.h"

int main(int argc, char**	argv)
{
	Singleton<ObserverDirector>::get().init();

	WindowGL* glWindow = new WindowGL(argc, argv);
	glWindow->init();

	RendererGL* glRenderer = new RendererGL();
	glRenderer->init();

	return 0;
}

#endif 