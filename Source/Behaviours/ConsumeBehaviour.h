#ifndef CONSUMEBEHAVIOUR_H
#define CONSUMEBEHAVIOUR_H

#include "../Component.h"
#include "../GraphicsContainer.h"
#include "../ConditionTimer.h"

#include "../Game/GameEntity.h"

static const double eventCondition = 5.0;

class ConsumeBehaviour : public Component
{
private:
	GameEntity* entity;

	ConditionTimer* eventTimer;
protected:
public:
	void init();
	void update(double delta);

	ConsumeBehaviour(GameEntity* entity);
	~ConsumeBehaviour();
};

#endif //CONSUMEBEHAVIOUR_H