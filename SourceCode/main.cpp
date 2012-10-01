/*Common include*/
#include "Singleton.h"
#include "Messaging/ObserverDirector.h"
#include "Common.h"

#ifdef _WIN32
#include "Windows.h"
int WINAPI WinMain(
	HINSTANCE	hInstance, 
	HINSTANCE	hPrevInstance, 
	LPSTR		lpCmdLine, 
	int			nCmdShow)
{
	Windows win;
	win.main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	return 0;
}
#endif

#ifndef _WIN32
#include "Linux.h"
int main(int argc, char** argv)
{
	Linux linux;
	linux.main(argc, argv);

	return 0;
}
#endif