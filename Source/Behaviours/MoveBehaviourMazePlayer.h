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
		case KEY_D:
			//stop();
			break;
		case KEY_A:
			respawn();
			break;
		}
	};
protected:
public:
	MoveBehaviourMazePlayer(Maze* maze, VecI2 position) : MoveBehaviourMaze(maze, position)
	{
		pos = VecI2(-3,16);
		move(1,0);
	};
	virtual void init()
	{
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, INPUT_KEYBOARD_MSG));
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_GHOST_POS));
	};

	void runAI()
	{
		//// If ghost has stopped, choose new direction

		//// Rotate 90*random degrees
		//VecF3 tmpDir(1.0f,0.0f,0.0f);
		//int random = rand() % 4;
		//tmpDir.rotate(90.0f*random, VecF3(0.0f,0.0f,1.0f));

		//// Convert vector to integer vector
		//VecI2 newDir(round(tmpDir.x), round(tmpDir.y));

		//// Do not move in opposite direction
		//if(newDir == -dir)
		//{
		//}
		//else
		//{
		//	// Try to move in new direction
		//	move(newDir.x,newDir.y);
		//}
	};
	void atIntersection()
	{
		runAI();
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
				case ENTITY_GHOST_POS:
					msgEntityGhostPos(msg);
					break;
				default:
					throw 0; //temp
					break;
				}
			}
		}

		Singleton<ObserverDirector>::get().push(new MsgEntityPlayerPos(position));
		Singleton<ObserverDirector>::get().push(new MsgEntityPacmanPos(pos));
	}

	void updateSpecific(double delta)
	{
		// Check collision with pills
		checkCollisionWithPills();
	};


	void msgKeyboard(Msg* msg)
	{
		MsgKeyboard* keyboardMsg = (MsgKeyboard*)msg;
		keyboard(keyboardMsg->Key());
		delete keyboardMsg;
	};

	void checkCollisionWithGhost(VecI2 ghostPos, VecF3 ghostPosition)
	{
		VecF3 v1 = position;
		VecF3 v2 = ghostPosition;

		// TRUE: Collision occurs
		float dist = v1.distanceTo(v2);
		if(dist < 0.4f)
		{
			// Send gameover message
			Singleton<ObserverDirector>::get().push(new MsgGameOver());
		}
	};

	void msgEntityGhostPos(Msg* msg)
	{
		MsgEntityGhostPos* msgCast = (MsgEntityGhostPos*)msg;
		checkCollisionWithGhost(msgCast->pos, msgCast->position);
		delete msgCast;
	};
};

#endif //MOVEBEHAVIORPLAYER_H