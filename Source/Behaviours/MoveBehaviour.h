#ifndef MOVEBEHAVIOUR_H
#define MOVEBEHAVIOUR_H

#include "../Component.h"
#include "../Math/PacMath.h"
#include "../Singleton.h"
#include "../Messaging/ObserverDirector.h"
#include "../Messaging/SubscriptionMsg.h"

class MoveBehaviour : public Component
{
private:
protected:
	MatF4 rotation;
	VecF3 position;
	
public:
	float lightPower;
	bool isActive;

	MoveBehaviour()
	{
		lightPower = 1.0f;
		isActive = true;
	}
	void activate()
	{
		isActive = true;
	};
	void deactivate()
	{
		isActive = false;
	};
	~MoveBehaviour(){}
	virtual void reset() = 0;
	void throwMessages()
	{
		Msg* msg = peek();
		while(msg)
		{
			msg = pop();
			if(msg)
			{
				delete msg;
			}
		}
	}
	MatF4 getRotation() { return rotation; }
	VecF3 getPosition() { return position; }
};

#endif //MOVEBEHAVIOR_H