#ifndef MOVEBEHAVIOURMAZE_H
#define MOVEBEHAVIOURMAZE_H

#include "MoveBehaviour.h"
#include "../Messaging/MsgKeyboard.h"
#include "../Game/Maze.h"

class MoveBehaviourMaze : public MoveBehaviour
{
private:
	float pos_offset;

	Quaternion qua_rot_tween;
	float speed;
	float turningSpeed; // turning speed (smaller is faster)
	
	Maze *maze;

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
			break;
		}
	};
	
protected:
	VecI2 pos;
	VecI2 dir;
	VecI2 dir_queue;
	bool isMoving;

	void move(int x, int y)
	{
		isMoving = true;

		// Prevent diagonal movements
		if(x!=0 && y!=0)
			x = 0; 

		// Update movement queue
		dir_queue.x=x;
		dir_queue.y=y;
	};
	void stop()
	{
		isMoving = false;
	};
public:
	MoveBehaviourMaze(Maze* maze, VecI2 position)
	{
		this->maze = maze;

		// Settings
		speed = 3.0f;
		turningSpeed = 10.0f;
		
		// Starting values
		pos = position;
		pos_offset = 0.0f;
		dir.x=1;
		dir.y=0;
		isMoving = false;

	};
	virtual ~MoveBehaviourMaze()
	{
		delete maze;
	};

	virtual void init()
	{
	};

	void respawn()
	{
		pos_offset = 0.0f;
		pos = maze->getRandomFreePosition();
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
				//switch(type)
				//{
				//default:
				//	throw 0; //temp
				//	break;
				//}
			}
		}
	}
	virtual void atIntersection() = 0;
	void update(double delta)	
	{
		float dt = (float)delta;

		handleMessages();
		updateSpecific(delta);

		// True: entity is in move state
		if(isMoving)
		{
			// True: Player is moving between two grid points 
			if(pos_offset>0.0f)
			{
				// interpolate "between" positions
				pos_offset-=dt*speed;

				// allow U-turn while moving between two grid points
				if(dir.x == -dir_queue.x && dir.y == -dir_queue.y)
				{
					dir = dir_queue;
					pos_offset = 1.0f - pos_offset;
					pos = VecI2(pos.x+dir.x,  pos.y+dir.y);
				}
			}
			// False: player is at intersection 
			else
			{
				atIntersection();
				VecI2 newPos = VecI2(pos.x+dir_queue.x,  pos.y+dir_queue.y);
				// True: queued direction would cause wall collision 
				if(maze->isWallPos(newPos))
				{
					newPos.x = pos.x+dir.x;
					newPos.y = pos.y+dir.y;
					// True: old direction would cause collision 
					if(maze->isWallPos(newPos))
					{
						// stop pacman and abort further testing
						isMoving = false;
					}
				}
				// Else: queued direction is valid for use
				else {
					dir = dir_queue;
				}

				if(isMoving)
				{
					//
					// Perform movement
					//

					pos=newPos;
					pos_offset +=1.0f;
					// Bugfix: it should only be possible for an entity to move a maximum of one square at every update
					if(pos_offset<0.0f)
						pos_offset = 0.0f; // reset movement
				}
			}
		}
		// False: entity is stopped
		else
		{
			// True: Player at intersection 
			if(pos_offset<=0.0f)
			{
				atIntersection();
			}
		}

		// Interpolate rotation on cube
		interpolateRotation(dt);
		position = getPosition();

		// Check collision with pills
		checkCollisionWithPills();
	}

	virtual void updateSpecific(double delta) = 0;

	void checkCollisionWithPills()
	{
		VecF2 pos(position.x, position.y);
		maze->checkCollisionWithPills(pos);
	};	

	void sendMsgEntityState()
	{
	};	

	void interpolateRotation(float dt)
	{
		// Create quaternion facing in rotation we want to interpolate to
		MatF4 mat_rot;
		VecF3 vec_eye(0.0f, 0.0f, 0.0f);
		VecF3 vec_at((float)dir.x, (float)dir.y, 0.0f);
		VecF3 vec_up(0.0f, 0.0f, -1.0f);
		mat_rot.lookAtLH(vec_eye, vec_at, vec_up);
		Quaternion qua_rot(&mat_rot);

		// Interpolate old rotation with new rotation using quaternions
		qua_rot = Quaternion::quaternionSlerp(&qua_rot_tween,&qua_rot, turningSpeed*dt);
		qua_rot_tween = qua_rot;

		// Update parent
		rotation = qua_rot.toMatrix();
		//rotation = mat_rot;
	};

	VecF3 getPosition()
	{
		// Hides transition between grid
		float xTween = -dir.x * pos_offset;
		float yTween = -dir.y * pos_offset;
		return VecF3(xTween+pos.x, yTween+pos.y, 0.0f);
	};

};

#endif //MOVEBEHAVIORPLAYER_H