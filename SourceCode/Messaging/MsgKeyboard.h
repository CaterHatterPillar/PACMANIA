#ifndef MSGKEYBOARD_H
#define MSGKEYBOARD_H

#include "Msg.h"

enum KEY
{
	W,
	A,
	S,
	D,
	ESC
};

class MsgKeyboard : public Msg
{
private:
	KEY	key;
protected:
public:
	MsgKeyboard(KEY key) : Msg(INPUT_KEYBOARD)
	{
		this->key = key;
	}
	MsgKeyboard(MsgKeyboard* keyboardMsg) : Msg(INPUT_KEYBOARD)
	{
		key = keyboardMsg->Key();
	}
	~MsgKeyboard() {}

	KEY	Key() { return key;	}
};

#endif //MSGKEYBOARD_H