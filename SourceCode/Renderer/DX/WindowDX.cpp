#include "WindowDX.h"

vector<bool> WindowDX::keys;
int	WindowDX::mouseDeltaX;
int	WindowDX::mouseDeltaY;
HWND WindowDX::hWnd;

WindowDX::WindowDX(HINSTANCE hInstance, int cmdShow)
{
	this->hInstance = hInstance;
	this->cmdShow = cmdShow;

	this->active = true;

	keys.resize(NUM_KEYS, false);

	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

WindowDX::~WindowDX()
{
	ReleaseCapture();
	ShowCursor(true);
}

void WindowDX::mouseDeltaMove(LPARAM lParam)
{
	//Find the upper left corner of the window's client area in screen coordinates
	POINT point;
	point.x = 0;
	point.y = 0;
	MapWindowPoints(hWnd, NULL, &point, 1);
	
	//Get current mouse position
	int mouseX = GET_X_LPARAM(lParam)+point.x;
	int mouseY = GET_Y_LPARAM(lParam)+point.y;

	//Calculate relative mouse movement
	mouseDeltaX = mouseX - SCREEN_WIDTH/2;
	mouseDeltaY = mouseY - SCREEN_HEIGHT/2;

	//Return cursor to screen center
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

LRESULT CALLBACK WindowDX::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}break;

	case WM_KEYDOWN:
		{
			if(wParam == VK_ESCAPE)
			{
				DestroyWindow(hWnd);
			}

			keys[wParam] = true;

			return 0;
		}break;

	case WM_KEYUP:
		{
			keys[wParam] = false;

			return 0;
		}break;

	case WM_MOUSEMOVE:
		{
			mouseDeltaMove(lParam);
			return 0;
		}break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void WindowDX::createWindow()
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "WindowClass";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(NULL,
		"WindowClass",
		"PACMANIA",
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, cmdShow);
}

void WindowDX::initCursor()
{
	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	SetCapture(hWnd);
	ShowCursor(false);
}

void WindowDX::init()
{
	createWindow();
	initCursor();

	MsgDXWindowHandle* msg = new MsgDXWindowHandle(&hWnd);
	Singleton<ObserverDirector>::get().push(msg);
}

void WindowDX::update(double delta)
{
	//Returns true if the applications is to be destroyed

	//bool quit = false;

	MSG msg = {0};

	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if(msg.message == WM_QUIT)
			active = false;
	}

	//return quit;
}

HWND WindowDX::getWindowHandle()
{
	return hWnd;
}

bool WindowDX::isActive()
{
	return active;
}