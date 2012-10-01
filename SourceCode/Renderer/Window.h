#ifndef WINDOW_H
#define WINDOW_H

#include "../Component.h"

class Window : public Component
{
private:
protected:
	bool active;
public:
	virtual void init() = 0;
	virtual void update(double delta) = 0;

	Window();
	~Window();

	bool isActive() { return active; }
};

#endif //WINDOW_H