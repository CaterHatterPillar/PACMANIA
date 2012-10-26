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
	LIGHT,
	
	DX_WINDOW_HANDLE,
	
	MSG_GLUT,
	MSG_GLUT_CALLBACK,

	// Pacman
	ENTITY_PLAYER_POS,
	ENTITY_PACMAN_POS,
	ENTITY_GHOST_POS,
	ENTITY_PILL_POS
};

//todoist: dela upp i win/linux

#endif //MSGTYPE_H