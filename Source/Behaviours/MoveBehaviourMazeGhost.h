#ifndef MOVEBEHAVIOURMAZEGHOST_H
#define MOVEBEHAVIOURMAZEGHOST_H

#include "MoveBehaviourMaze.h"
#include "../Messaging/MsgSound.h"

class MoveBehaviourMazeGhost : public MoveBehaviourMaze
{
private:
	VecI2 target;
	float fleeTimer;
	float lightPower_tween;
public:
	MoveBehaviourMazeGhost(Maze* maze, VecI2 position) : MoveBehaviourMaze(maze, position)
	{
		reset();
	};
	virtual void init()
	{
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_PACMAN_POS));
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_PILL_BLOODY_EATEN));
	};
	
	void reset()
	{
		pos = VecI2(28,16);
		//pos = VecI2(0,16);
		move(1,0);
		fleeTimer = 0.0f;
		lightPower_tween = lightPower;
		isActive = true;
	};

	bool isValidDir(VecI2 newDir)
	{
		// Direction is not zero
		if(newDir.x==0 && newDir.y==0)
			return false;

		VecI2 newPos = VecI2(pos.x+newDir.x,  pos.y+newDir.y);

		// TRUE: Do not move in opposite direction/move outside/collide with wall
		return !isWallPos(newPos) && !isOutsidePos(newPos);
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
			lightPower_tween = 0.8f;

			if(fleeTimer>0)
			{
				speed = 2.0f;
				newDir=-newDir;
			}
		}
		else
		{
			lightPower_tween = 0.2f;
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
				if(isValidDir(newDir) && !(newDir == -dir))
				{
					break; // Abort further testing
				}
			}

			// TRUE: No valid direction found, we are in a dead end, pick opposite direction
			if(!(isValidDir(newDir) && !(newDir == -dir)))
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

	void checkCollisionWithGhost(VecI2 ghostPos, VecF3 ghostPosition)
	{
		VecF3 v1 = position;
		VecF3 v2 = ghostPosition;

		// TRUE: Pacman is invinsible
		if(fleeTimer>0.0f)
		{
			float dist = v1.distanceTo(v2);
			// TRUE: Collision occurs
			if(dist<0.5f)
			{
				Singleton<ObserverDirector>::get().push(new MsgSound(SOUND_GHOST_DEATH));
				reset();
			}
		}
	};

	void updateSpecific(double delta)
	{
		float dt = (float)delta;

		// Light logic & invincible logic
		if(fleeTimer>0)
			fleeTimer-=dt;
		if(fleeTimer<0)
			fleeTimer=0;

		// lerp slower when restoring light
		if(lightPower_tween>lightPower)
			lightPower = lerp(lightPower, lightPower_tween, 0.8f*dt);
		// lerp faster when draining light
		else
			lightPower = lerp(lightPower, lightPower_tween, 2.0f*dt);
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
				case ENTITY_PILL_BLOODY_EATEN:
					msgEntityPillBloodyEaten(msg);
					break;
				default:
					throw 0; //temp
					break;
				}
			}
		}

		// HACK
		// Shouldn't send messages if not active
		if(!isActive)
			return;

		// Send messages
		Singleton<ObserverDirector>::get().push(new MsgEntityGhostPos(pos, position));
	}


	void msgEntityPacmanPos(Msg* msg)
	{
		MsgEntityPacmanPos* msgCast = (MsgEntityPacmanPos*)msg;

		// Assign pacman position as target
		target = msgCast->pos;
		checkCollisionWithGhost(msgCast->pos, msgCast->position);

		delete msgCast;
	};

	void msgEntityPillBloodyEaten(Msg* msg)
	{
		delete msg;
		fleeTimer = 6.0f;
	};
};

#endif