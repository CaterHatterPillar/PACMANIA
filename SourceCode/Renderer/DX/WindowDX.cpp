#include "WindowDX.h"

vector<bool> WindowDX::keys;
int	WindowDX::mouseDeltaX;
int	WindowDX::mouseDeltaY;
bool WindowDX::leftMouseButton;
bool WindowDX::rightMouseButton;
HWND WindowDX::hWnd;

WindowDX::WindowDX(HINSTANCE hInstance, int cmdShow) : Window()
{
	this->hInstance = hInstance;
	this->cmdShow = cmdShow;

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
			PostQuitMessage(0);
			return 0;
		break;
	case WM_KEYDOWN:
			if(wParam == VK_ESCAPE)
				DestroyWindow(hWnd);
			keys[wParam] = true;
			sendKeyboardInput(wParam, true);
			return 0;
		break;
	case WM_KEYUP:
			keys[wParam] = false;
			sendKeyboardInput(wParam, false);
			return 0;
		break;
	case WM_MOUSEMOVE:
			mouseDeltaMove(lParam);
			sendMouseMove();
			return 0;
		break;
	case WM_LBUTTONDOWN:
		leftMouseButton = true;
		sendMouseClick();
		break;
	case WM_LBUTTONUP:
		leftMouseButton = false;
		break;
	case WM_RBUTTONDOWN:
		rightMouseButton = true;
		sendMouseClick();
		break;
	case WM_RBUTTONUP:
		rightMouseButton = false;
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


void WindowDX::sendKeyboardInput(WPARAM key, bool isPressed)
{
	if(key == VK_W)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_W);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
	if(key == VK_A)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_A);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
	if(key == VK_S)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_S);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
	if(key == VK_D)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_D);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
	if(key == VK_UP)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_UP);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
	if(key == VK_LEFT)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_LEFT);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
	if(key == VK_DOWN)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_DOWN);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
	if(key == VK_RIGHT)
	{
		MsgKeyboard* msgKeyboard = new MsgKeyboard(KEY_RIGHT);
		Singleton<ObserverDirector>::get().push(msgKeyboard);
	}
}

void WindowDX::sendMouseMove()
{
	MsgMouseMove* msgMouseMove = new MsgMouseMove(mouseDeltaX, mouseDeltaY);
	Singleton<ObserverDirector>::get().push(msgMouseMove);
}

void WindowDX::sendMouseClick()
{
	MsgMouseClick* msgMouseClick = new MsgMouseClick(leftMouseButton, rightMouseButton);
	Singleton<ObserverDirector>::get().push(msgMouseClick);
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

InputContainer WindowDX::getInput()
{
	return InputContainer(keys, mouseDeltaX, mouseDeltaY);
}