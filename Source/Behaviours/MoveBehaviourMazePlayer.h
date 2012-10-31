#ifndef MOVEBEHAVIOURMAZEPLAYER_H
#define MOVEBEHAVIOURMAZEPLAYER_H

#include "MoveBehaviourMaze.h"
#include "../Messaging/MsgKeyboard.h"
#include "../Game/Maze.h"

class MoveBehaviourMazePlayer : public MoveBehaviourMaze
{
private:
	float invinsibleTimer;
	float lightPower_tween;
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
		reset();
	};
	virtual void init()
	{
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, INPUT_KEYBOARD_MSG));
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_GHOST_POS));
		Singleton<ObserverDirector>::get().push(new SubscriptionMsg(this, ENTITY_PILL_BLOODY_EATEN));
	};

	void reset()
	{
		pos = VecI2(-9,16);
		move(1,0);
		invinsibleTimer = 0.0f;
		lightPower_tween = lightPower;
	};

	void atIntersection()
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
				case INPUT_KEYBOARD_MSG:
					msgKeyboard(msg);
					break;
				case ENTITY_GHOST_POS:
					msgEntityGhostPos(msg);
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

		Singleton<ObserverDirector>::get().push(new MsgEntityPlayerPos(position));
		Singleton<ObserverDirector>::get().push(new MsgEntityPacmanPos(pos, position));
	}

	void updateSpecific(double delta)
	{
		float dt = (float)delta;
		// Check collision with pills
		checkCollisionWithPills();

		// Light logic & invincible logic
		if(invinsibleTimer>0)
			invinsibleTimer-=dt;
		if(invinsibleTimer<0)
			invinsibleTimer=0;
		
		// make pacman brighter when invincible
		if(invinsibleTimer>0)
		{
			lightPower_tween = 10.0f;
		}
		else
		{
			if(lightPower_tween>1.0f)
				lightPower_tween = 1.0f;
		}
		// lerp slower when restoring light
		if(lightPower_tween>lightPower)
			lightPower = lerp(lightPower, lightPower_tween, 0.8f*dt);
		// lerp faster when draining light
		else
			lightPower = lerp(lightPower, lightPower_tween, 2.0f*dt);

		// make light fade quicker when eating bloody pills
		if(lightPower>lightPower_tween && lightPower>1.0f)
			lightPower = lerp(lightPower, lightPower_tween, 2.0f*dt);
		
		lightPower_tween = 1.0f;
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

		// TRUE: Not invincible
		if(!(invinsibleTimer>0.0f))
		{
			
			// TRUE: Drain some light if seeing ghost
			if(isInLineOfSight(pos, ghostPos))
			{
				lightPower_tween = 0.7f;
			}
			// FALSE: Player is hidden from ghost and cannot collide
			else
			{
				return;
			}

			float dist = v1.distanceTo(v2);
			// TRUE: Light draining occurs
			float spotDistance = 3.0f;
			float minDistance = 0.0f;
			if(dist < spotDistance - minDistance)
				lightPower_tween = lightPower_tween*dist/(spotDistance-minDistance);
			if(lightPower_tween<0.0f)
				lightPower_tween = 0.0f;

			// TRUE: Collision occurs
			if(dist < 0.4f)
			{
				// Send gameover message
				Singleton<ObserverDirector>::get().push(new MsgGameOver());
			}
		}
	};

	void msgEntityGhostPos(Msg* msg)
	{
		MsgEntityGhostPos* msgCast = (MsgEntityGhostPos*)msg;
		checkCollisionWithGhost(msgCast->pos, msgCast->position);
		delete msgCast;
	};

	void msgEntityPillBloodyEaten(Msg* msg)
	{
		delete msg;
		invinsibleTimer = 5.0f;
	};
};

#endif //MOVEBEHAVIORPLAYER_H