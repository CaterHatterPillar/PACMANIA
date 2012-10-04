/*#ifndef MSGDXWINDOWHANDLE_H
#define MSGDXWINDOWHANDLE_H

#include "Msg.h"
#include "MsgType.h"
#include <Windows.h>

class MsgDXWindowHandle : public Msg
{
private:
	HWND* hWnd;
public:
	MsgDXWindowHandle(HWND* hWnd) : Msg(DX_WINDOW_HANDLE)
	{
		this->hWnd = hWnd;
	}
	MsgDXWindowHandle(MsgDXWindowHandle* msg) : Msg(DX_WINDOW_HANDLE)
	{
		this->hWnd = msg->hWnd;
	}
	virtual ~MsgDXWindowHandle()
	{

	}

	HWND* getHandle()
	{
		return hWnd;
	}
};

#endif*/
