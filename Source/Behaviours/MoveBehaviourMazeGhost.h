#ifndef MOVEBEHAVIOURMAZEGHOST_H
#define MOVEBEHAVIOURMAZEGHOST_H

#include "MoveBehaviourMaze.h"

class MoveBehaviourMazeGhost : public MoveBehaviourMaze
{
private:
	VecI2 target;
public:
	MoveBehaviourMazeGhost(Maze* maze, VecI2 position) : MoveBehaviourMaze(maze, position)
	{
	};
	virtual void init()
	{
		SubscriptionMsg* subscription = new SubscriptionMsg(this, ENTITY_PACMAN_POS);
		Singleton<ObserverDirector>::get().push(subscription);
	};

	bool isValidDir(VecI2 newDir)
	{
		VecI2 newPos = VecI2(pos.x+newDir.x,  pos.y+newDir.y);

		// True: Do not move in opposite direction
		return !(newDir == -dir) && !isWallPos(newPos);
	}

	void runAI()
	{
		// Calc direction to target
		VecI2 newDir;
		newDir.x = target.x - pos.x;
		newDir.y = target.y - pos.y;
		newDir.normalize();

		// True: Invalid direction, chose new
		if(!isValidDir(newDir) || true)
		{
			// Rotate 90*random degrees
			VecF3 tmpDir(1.0f,0.0f,0.0f);
			int random = rand() % 4;
			tmpDir.rotate(90.0f*random, VecF3(0.0f,0.0f,1.0f));

			// Convert vector to integer vector
			newDir = VecI2(round(tmpDir.x), round(tmpDir.y));
		}

		// True: queue valid direction
		if(isValidDir(newDir))
		{
			// Try to move in new direction
			move(newDir.x, newDir.y);
		}
	};

	void atIntersection()
	{
		runAI();
	};

	void updateSpecific(double delta)
	{
		
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
				case ENTITY_PACMAN_POS:
					msgEntityPacmanPos(msg);
					break;
				default:
					throw 0; //temp
					break;
				}
			}
		}
	}

	void msgEntityPacmanPos(Msg* msg)
	{
		MsgEntityPacmanPos* msgCast = (MsgEntityPacmanPos*)msg;

		// Assign pacman possition as target
		target = msgCast->pos;

		delete msgCast;
	};
};

#endif