#ifndef CONSUMEBEHAVIOUR_H
#define CONSUMEBEHAVIOUR_H

#include "../Component.h"
#include "../GraphicsContainer.h"

class ConsumeBehaviour : public Component
{
private:
	GraphicsContainer* graphicsContainer;
protected:
public:
	void init();
	void update(double delta);

	ConsumeBehaviour();
	~ConsumeBehaviour();
};

#endif //CONSUMEBEHAVIOUR_H