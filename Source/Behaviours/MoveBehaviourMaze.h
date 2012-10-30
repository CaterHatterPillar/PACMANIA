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
	float speed;

	void move(int x, int y)
	{
		isMoving = true;

		// Prevent diagonal movements
		if(x!=0 && y!=0)
			x = 0; 

		// Prevent zero vectors
		if(x==0 && y==0)
		{
			throw "Negative vector, this shouldn't occur, please find out why.";
		}

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
		// delete maze;
	};

	// Returns true if both position is in line of sight of eachother i.e. empty of maze segments
	bool isInLineOfSight(VecI2 p1, VecI2 p2)
	{
		int x0 = p1.x;
		int y0 = p1.y;
		int x1 = p2.x;
		int y1 = p2.y;

		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = x0 < x1 ? 1 : -1;
		int sy = y0 < y1 ? 1 : -1;
		int err = dx - dy;

		// Obstacle
		while(true)
		{
			// TRUE: Sight is obscured by wall, there is no point in continuing
			if(isWallPos(VecI2(x0, y0)))
			{
				return false;
			}

			// Break if end is reached
			if(x0 == x1 && y0 == y1) 
			{
				break;
			}

			// Walk to next cell
			int e2 = 2 * err;
			if(e2 > -dy)
			{
				err = err - dy;
				x0 = x0 + sx;
			}
			if(e2 < dx)
			{
				err = err + dx;
				y0 = y0 + sy;
			}
		}

		return true;
	}

	virtual void init()
	{
	};

	// Returns true if position is a wall
	bool isWallPos(VecI2 pos)
	{
		return maze->isWallPos(pos);
	};

	// Returns true if position is a wall
	bool isOutsidePos(VecI2 pos)
	{
		return maze->isOutsidePos(pos);
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
				else 
				{
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