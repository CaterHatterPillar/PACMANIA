
/*Common include*/
#include "Singleton.h"
#include "Messaging/ObserverDirector.h"
#include "Common.h"

#ifdef _WIN32
#include "WindowsContainer.h"

int WINAPI WinMain(
	HINSTANCE	hInstance, 
	HINSTANCE	hPrevInstance, 
	LPSTR		lpCmdLine, 
	int			nCmdShow)
{
	WindowsContainer win;
	win.main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}
#endif


#ifndef _WIN32
#include "Linux.h"

int main(int argc, char** argv)
{
	LinuxContainer linux;
	linux.main(argc, argv);

	return 0;
}
#endif