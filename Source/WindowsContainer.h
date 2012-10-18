#ifndef WINDOWSCONTAINER_H
#define WINDOWSCONTAINER_H

#include <Windows.h>

/*Windows include*/
#include "DX/WindowDX.h"
#include "DX/RendererDX.h"
#include "DX/CameraDX.h"

class WindowsContainer
{
private:
protected:
public:
	void main(
		HINSTANCE	hInstance, 
		HINSTANCE	hPrevInstance, 
		LPSTR		lpCmdLine, 
		int			nCmdShow);
	void initWindows(
		WindowDX*	dxWindow,
		RendererDX*	dxRenderer,
		CameraDX*	dxCamera);

	WindowsContainer()	{}
	~WindowsContainer()	{}
};

#endif //WINDOWSCONTAINER_H