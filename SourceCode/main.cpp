//#define WINDOWS

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


	while(dxWindow->isActive())
	{
		dxWindow->update(1.0);
		dxRenderer->renderFrame();
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
#include "Renderer/GL/SimpleGeometry.h"

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

	SimpleGeometry* simpleGeometry = new SimpleGeometry();
	simpleGeometry->init();

	while(true)
	{
		Singleton<ObserverDirector>::get().update(1.0);

		glWindow->update(1.0);
		glRenderer->update(1.0);
		simpleGeometry->update(1.0);
	}

	delete glWindow;
	delete glRenderer;
	delete simpleGeometry;

	return 0;
}

#endif 