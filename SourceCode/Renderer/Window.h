#ifndef WINDOW_H
#define WINDOW_H

#include "../Component.h"

class Window : public Component
{
private:
protected:
public:
	virtual void update(double delta) = 0;
	virtual void init() = 0;
};

#endif //WINDOW_H