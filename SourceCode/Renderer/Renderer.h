#ifndef RENDERER_H
#define RENDERER_H

#include "../Component.h"

class Renderer : Component
{
private:
protected:
public:
	virtual void init()	= 0;
	virtual void update(double delta) = 0;
	virtual void renderFrame() = 0;
	
	virtual void cleanUp() = 0;
};

#endif //RENDERER_H