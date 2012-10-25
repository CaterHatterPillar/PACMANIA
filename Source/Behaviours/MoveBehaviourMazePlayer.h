#ifndef MOVEBEHAVIOURMAZEPLAYER_H
#define MOVEBEHAVIOURMAZEPLAYER_H

#include "MoveBehaviourMaze.h"
#include "../Messaging/MsgKeyboard.h"
#include "../Game/Maze.h"

class MoveBehaviourMazePlayer : public MoveBehaviourMaze
{
private:
	void keyboard(KEY key)
	{
		switch(key)
		{
		case KEY_UP:
			move(0,1);
			break;
		case KEY_LEFT:
			move(-1,0);
			break;
		case KEY_DOWN:
			move(0,-1);
			break;
		case KEY_RIGHT:
			move(1,0);
			break;
		case KEY_S:
			stop();
			respawn();
			break;
		}
	};
protected:
public:
	MoveBehaviourMazePlayer(Maze* maze, VecI2 position) : MoveBehaviourMaze(maze, position)
	{
	};
	virtual void init()
	{
		SubscriptionMsg* subscription = new SubscriptionMsg(this, INPUT_KEYBOARD_MSG);
		Singleton<ObserverDirector>::get().push(subscription);
	};
	virtual void handleMessages()
	{
		Msg* msg = peek();
		while(msg)
		{
			msg = pop();
			if(msg)
			{
				MsgType type = msg->Type();
				switch(type)
				{
				case INPUT_KEYBOARD_MSG:
					msgKeyboard(msg);
					break;
				default:
					throw 0; //temp
					break;
				}
			}
		}

		// Send message of current state to all relevent listeners
		sendMsgEntityState();
	}

	void sendMsgEntityState()
	{
		MsgEntityState* msg = new MsgEntityState(position, 0);
		Singleton<ObserverDirector>::get().push(msg);
	};	

	void msgKeyboard(Msg* msg)
	{
		MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;
		keyboard(keyboardMsg->Key());
		delete keyboardMsg;
	};
};

#endif //MOVEBEHAVIORPLAYER_H