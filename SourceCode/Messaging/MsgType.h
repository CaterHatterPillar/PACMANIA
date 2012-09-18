#ifndef MSGTYPE_H
#define MSGTYPE_H

/*Add new msgs here*/
enum MsgType
{
	SUBSCRIBE,
	RENDER,

	INPUT_MOUSE_CLICK,
	INPUT_MOUSE_MOVE,
	INPUT_KEYBOARD,
	CAMERA,

	MSG_GLUT_CALLBACK,
	
	DX_WINDOW_HANDLE
};

//todoist: dela upp i win/linux

#endif //MSGTYPE_H