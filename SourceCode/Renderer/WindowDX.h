#ifndef WINDOWDX_H
#define WINDOWDX_H

#include <Windows.h>
#include <WindowsX.h>

#include "../Common.h"


using namespace std;

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int NUM_KEYS = 256;

class WindowDX
{
private:
	static vector<bool> keys;
	static int mouseDeltaX;
	static int mouseDeltaY;

	static HWND hWnd;
	HINSTANCE hInstance;
	int cmdShow;

	void createWindow();
	void initCursor();

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	WindowDX(HINSTANCE hInstance, int cmdShow);
	~WindowDX();

	void initialize();

	bool checkMessages();
	HWND getWindowHandle();
};

#endif //WINDOWDX_H