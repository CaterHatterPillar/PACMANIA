#ifndef WINDOWDX_H
#define WINDOWDX_H

#include <Windows.h>
#include <WindowsX.h>

#include "InputContainer.h"

#include "../../Common.h"
#include "../Window.h"
#include "../../Messaging/ObserverDirector.h"
#include "../../Singleton.h"
#include "../../Messaging/MsgDXWindowHandle.h"

using namespace std;

static const int NUM_KEYS = 256;

class WindowDX : public Window
{
private:
	static vector<bool> keys;
	static int mouseDeltaX;
	static int mouseDeltaY;

	bool active;

	static HWND hWnd;
	HINSTANCE hInstance;
	int cmdShow;

	void createWindow();
	void initCursor();

	static void mouseDeltaMove(LPARAM lParam);
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	WindowDX(HINSTANCE hInstance, int cmdShow);
	virtual ~WindowDX();

	virtual void init();

	void update(double delta);
	HWND getWindowHandle();
	bool isActive();

	InputContainer getInput();
};

#endif //WINDOWDX_H