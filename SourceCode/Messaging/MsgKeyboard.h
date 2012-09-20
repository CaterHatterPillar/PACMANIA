#ifndef MSGKEYBOARD_H
#define MSGKEYBOARD_H

#include "Msg.h"

enum KEY
{

	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_ESC
	
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT

};

class MsgKeyboard : public Msg
{
private:
	KEY	key;
protected:
public:
	MsgKeyboard(KEY key) : Msg(INPUT_KEYBOARD_MSG)
	{
		this->key = key;
	}
	MsgKeyboard(MsgKeyboard* keyboardMsg) : Msg(INPUT_KEYBOARD_MSG)
	{
		key = keyboardMsg->Key();
	}
	~MsgKeyboard() {}

	KEY	Key() { return key;	}
};

#endif //MSGKEYBOARD_H