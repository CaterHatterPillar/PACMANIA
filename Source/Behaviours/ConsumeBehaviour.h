#ifndef CONSUMEBEHAVIOUR_H
#define CONSUMEBEHAVIOUR_H

#include "../Common.h"
#include "../Component.h"
#include "../GraphicsContainer.h"
#include "../ConditionTimer.h"

#include "../Game/GameEntity.h"

#include "../Messaging/SubscriptionMsg.h"
#include "../Messaging/MsgCamera.h"

#include "../Math/PacMath.h"

static const double	eventCondition	= 3.0;
static const float	interPolFac		= 1.0f;

class ConsumeBehaviour : public Component
{
private:
	GameEntity* entity;

	ConsumeState state;
	ConditionTimer* eventTimer;

	bool interpolPos;
protected:
public:
	void init();
	void update(double delta);

	void displayEvent();
	void displayConsume();

	ConsumeBehaviour(GameEntity* entity);
	~ConsumeBehaviour();

	void msgConsume(Msg* msg);
	void msgCamera(Msg* msg);
};

#endif //CONSUMEBEHAVIOUR_H