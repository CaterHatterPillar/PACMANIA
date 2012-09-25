//#define WINDOWS

/*Common include*/
#include "Singleton.h"
#include "Messaging/ObserverDirector.h"
#include "Common.h"

#ifdef WINDOWS
/*Windows include*/
#include "renderer/DX/WindowDX.h"
#include "renderer/DX/RendererDX.h"
#include "Renderer/DX/CameraDX.h"

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
#include "Renderer/GL/CameraGL.h"
#include "Renderer/Camera.h"
#include "InputGL.h"
//#include "Renderer/GL/SimpleGeometry.h"

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

	//SimpleGeometry* simpleGeometry = new SimpleGeometry();
	//simpleGeometry->init();

	CameraGL* camGL = new CameraGL(F_O_V, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 1000.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	camGL->init();

	InputGL* input = new InputGL();
	input->init();

	while(glWindow->Running())
	{
		Singleton<ObserverDirector>::get().update(1.0);

		input->update(1.0);
		camGL->update(1.0);

		glRenderer->update(1.0);
		glWindow->update(1.0);
		
		//simpleGeometry->update(1.0);
	}

	delete glWindow;
	delete glRenderer;
	delete camGL;
	delete input;
	//delete simpleGeometry;

	return 0;
}

#endif 