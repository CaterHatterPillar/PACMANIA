#ifndef MOVEBEHAVIOURMAZEGHOST_H
#define MOVEBEHAVIOURMAZEGHOST_H

#include "MoveBehaviourMaze.h"

class MoveBehaviourMazeGhost : public MoveBehaviourMaze
{
private:
	
public:
	MoveBehaviourMazeGhost(Maze* maze, VecI2 position) : MoveBehaviourMaze(maze, position)
	{
	};
	virtual void init()
	{
	};

	void runAI()
	{
		// If ghost has stopped, choose new direction

		// Rotate 90*random degrees
		VecF3 tmpDir(1.0f,0.0f,0.0f);
		int random = rand() % 4;
		tmpDir.rotate(90.0f*random, VecF3(0.0f,0.0f,1.0f));

		// Convert vector to integer vector
		VecI2 newDir(round(tmpDir.x), round(tmpDir.y));

		// Do not move in opposite direction
		if(newDir == -dir)
		{
		}
		else
		{
			// Try to move in new direction
			move(newDir.x,newDir.y);
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
				//MsgType type = msg->Type();
				//switch(type)
				//{
				//default:
				//	throw 0; //temp
				//	break;
				//}
			}
		}
	}
};

#endif