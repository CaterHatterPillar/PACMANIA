#include "WindowDX.h"

vector<bool> WindowDX::keys;
int	WindowDX::mouseDeltaX;
int	WindowDX::mouseDeltaY;
HWND WindowDX::hWnd;

WindowDX::WindowDX(HINSTANCE hInstance, int cmdShow)
{
	this->hInstance = hInstance;
	this->cmdShow = cmdShow;

	keys.resize(NUM_KEYS, false);

	SetCursorPos(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

WindowDX::~WindowDX()
{
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
			//mouseDeltaMove(lParam);
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
void WindowDX::init()
{
	createWindow();
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

		/*
		if(msg.message == WM_QUIT)
			quit = true;
			*/
	}

	//return quit;
}

HWND WindowDX::getWindowHandle()
{
	return hWnd;
}