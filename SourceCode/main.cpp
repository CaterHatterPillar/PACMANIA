//#define WINDOWS

#ifdef WINDOWS
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
#include "Renderer/GL/WindowGL.h"

int main(int argc, char**	argv)
{
	//OpenGL* openGL = new OpenGL(1920.0f, 1200.0f, 60.0f, 1.0f, 1000.0f);
	//openGL->initialize(argc, argv);

	/*Clear*/
	//delete openGL;


	WindowGL* glWindow = new WindowGL(argc, argv);
	glWindow->init();

	return 0;
}

#endif 