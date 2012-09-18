//#define WINDOWS

/*Common include*/
#include "Singleton.h"
#include "Messaging/ObserverDirector.h"

#ifdef WINDOWS
/*Windows include*/
#include "renderer/DX/WindowDX.h"

int WINAPI WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	WindowDX* dxWindow = new WindowDX(hInstance, nCmdShow);
	dxWindow->init();

	while(true)
	{
		dxWindow->update(1.0);
	}
}
#endif

#ifndef WINDOWS
/*Linux include*/

/*memleaks*/
#include <vld.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Renderer/GL/WindowGL.h"
#include "Renderer/GL/RendererGL.h"

int main(int argc, char**	argv)
{
	/*Memleaks*/
	_CrtSetDbgFlag (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG );

	Singleton<ObserverDirector>::get().init();

	WindowGL* glWindow = new WindowGL(argc, argv);
	glWindow->init();

	RendererGL* glRenderer = new RendererGL();
	glRenderer->init();

	while(true)
	{
		Singleton<ObserverDirector>::get().update(1.0);
		glWindow->update(1.0);
		glRenderer->update(1.0);
	}

	delete glWindow;
	delete glRenderer;

	return 0;
}

#endif 