//#ifndef MOVEBEHAVIOURPILL_H
//#define MOVEBEHAVIOURPILL_H
//
//#include "MoveBehaviour.h"
//#include "../Messaging/MsgKeyboard.h"
//#include "Maze.h"
//
//class MoveBehaviourPill : public MoveBehaviour
//{
//private:
//	VecI2 pos;
//	float pos_offset;
//	VecI2 dir_queue;
//	VecI2 dir;
//	bool isMoving;
//
//	Quaternion qua_rot_tween;
//	float speed;
//	float turningSpeed; // turning speed (smaller is faster)
//	
//	Maze *maze;
//protected:
//public:
//	MoveBehaviourPill(Maze* maze)
//	{
//		this->maze = maze;
//	};
//	virtual ~MoveBehaviourPlayer()
//	{
//		delete maze;
//	};
//
//	virtual void init()
//	{
//		SubscriptionMsg* subscription = new SubscriptionMsg(this, INPUT_KEYBOARD_MSG);
//		Singleton<ObserverDirector>::get().push(subscription);
//	};
//	virtual void handleMessages()
//	{
//		Msg* msg = peek();
//		while(msg)
//		{
//			msg = pop();
//			if(msg)
//			{
//				MsgType type = msg->Type();
//				switch(type)
//				{
//				case INPUT_KEYBOARD_MSG:
//					msgKeyboard(msg);
//					break;
//				default:
//					throw 0; //temp
//					break;
//				}
//			}
//		}
//	}
//	virtual void update(double delta)
//	{
//		float dt = (float)delta;
//
//		handleMessages();
//	};
//
//	VecF3 getPosition()
//	{
//		// Hides transition between grid
//		float xTween = -dir.x * pos_offset;
//		float yTween = -dir.y * pos_offset;
//		return VecF3(xTween+pos.x, yTween+pos.y, 0.0f);
//	};
//};
//
//#endif //MOVEBEHAVIORPLAYER_H