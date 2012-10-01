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
	VecF3 direction;
public:
	MoveBehaviour() { direction = VecF3(0.0f, 0.0f, 0.0f); }
	~MoveBehaviour() { }
	VecF3 getDirection() { return direction; }
};

#endif //MOVEBEHAVIOR_H