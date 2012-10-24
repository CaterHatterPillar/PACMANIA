#ifndef MSGTYPE_H
#define MSGTYPE_H

/*Add new msgs here*/

enum MsgType {
	SUBSCRIBE,
	RENDER,
	INPUT_MOUSE_CLICK,
	INPUT_MOUSE_MOVE,
	INPUT_KEYBOARD_MSG,
	CAMERA,
	ENTITY_STATE,
	
	DX_WINDOW_HANDLE,
	
	MSG_GLUT,
	MSG_GLUT_CALLBACK
};

//todoist: dela upp i win/linux

#endif //MSGTYPE_H