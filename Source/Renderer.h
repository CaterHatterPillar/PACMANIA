#ifndef RENDERER_H
#define RENDERER_H

#include "Common.h"
#include "Component.h"

#include "Math/PacMath.h"

#include "Messaging\MsgRender.h"

class Renderer : public Component
{
private:
protected:
	static std::vector<MsgRender*>* renderList;
public:
	virtual ~Renderer();

	virtual void init()					= 0;
	virtual void update(double delta)	= 0;
	virtual void renderFrame()			= 0;
	virtual void cleanUp()				= 0;
};

#endif //RENDERER_H