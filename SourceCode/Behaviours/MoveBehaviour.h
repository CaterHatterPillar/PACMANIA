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
	MoveBehaviour() {}
	~MoveBehaviour() { }
	MatF4 getRotation() { return rotation; }
	VecF3 getPosition() { return position; }
};

#endif //MOVEBEHAVIOR_H