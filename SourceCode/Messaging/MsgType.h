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

	/*OpenGL*/
	MSG_GLUT_CALLBACK
};

//todoist: dela upp i win/linux

#endif //MSGTYPE_H