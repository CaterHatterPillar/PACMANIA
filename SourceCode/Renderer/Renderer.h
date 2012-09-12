#ifndef RENDERER_H
#define RENDERER_H

#include "Component.h"

class Renderer : Component
{
private:
protected:
public:
	virtual void init()	= 0;
	virtual void update(double delta) = 0;

	Renderer();
	virtual ~Renderer();
};

#endif //RENDERER_H