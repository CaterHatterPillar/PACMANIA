
/*Common include*/
#include "Singleton.h"
#include "Messaging/ObserverDirector.h"
#include "Common.h"

#ifndef _WIN32
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


#ifdef _WIN32
#include "LinuxContainer.h"

int main(int argc, char** argv)
{
	LinuxContainer linux;
	linux.main(argc, argv);

	return 0;
}
#endif