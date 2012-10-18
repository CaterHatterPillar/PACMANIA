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

#else

//#include "vld.h" //insert debug-flag here

#include "LinuxContainer.h"
int main(int argc, char** argv)
{
	LinuxContainer* linuxContainer = new LinuxContainer();
	linuxContainer->mainContainer(argc, argv);
	DELETE_NULL(linuxContainer);

	return 0;
}
#endif //_WIN32
