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
		pos = VecI2(28,16);
		move(1,0);
	};
	virtual void init()
	{
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_PACMAN_POS));
	};

	bool isValidDir(VecI2 newDir)
	{
		// Direction is not zero
		if(newDir.x==0 && newDir.y==0)
			return false;

		VecI2 newPos = VecI2(pos.x+newDir.x,  pos.y+newDir.y);

		// TRUE: Do not move in opposite direction/move outside/collide with wall
		return !(newDir == -dir) && !isWallPos(newPos) && !isOutsidePos(newPos);
	}

	void runAI()
	{
		VecI2 newDir;

		// TRUE: Target is in line-of-sight, pick that direction
		if(isInLineOfSight(pos, target))
		{
			// Calc direction to target
			newDir.x = target.x - pos.x;
			newDir.y = target.y - pos.y;
			newDir.normalize();

			speed = 3.3f;
		}
		else
		{
			speed = 2.6f;
		}

		
		
		// TRUE: Invalid direction, pick random direction
		if(!isValidDir(newDir))
		{
			// Search every direction until we find a suitable
			// if all direction fails it means we are in a dead end
			// in which case we pick the opposite direction 
			int random = rand() % 4;
			for(int i=0; i<4; i++)
			{
				// Rotate 90*(random+i) degrees
				VecF3 tmpDir(1.0f,0.0f,0.0f);
				tmpDir.rotate(90.0f*(random+i), VecF3(0.0f,0.0f,1.0f));
				newDir = VecI2(round(tmpDir.x), round(tmpDir.y));

				// TRUE: Found direction, no further testing needed
				if(isValidDir(newDir))
				{
					break; // Abort further testing
				}
			}

			// TRUE: No valid direction found, we are in a dead end, pick opposite direction
			if(!isValidDir(newDir))
			{
				newDir = -dir;
			}
		}


		// Try to move in new direction
		move(newDir.x, newDir.y);
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

		// Send messages
		Singleton<ObserverDirector>::get().push(new MsgEntityGhostPos(pos, position));
	}


	void msgEntityPacmanPos(Msg* msg)
	{
		MsgEntityPacmanPos* msgCast = (MsgEntityPacmanPos*)msg;

		// Assign pacman position as target
		target = msgCast->pos;

		delete msgCast;
	};
};

#endif