#ifndef RENDERER_H
#define RENDERER_H

#include "Common.h"
#include "Component.h"
#include "GraphicsContainer.h"
#include "Math/PacMath.h"

class Renderer : public Component
{
private:
protected:
	static std::vector<GraphicsContainer*>* renderList;
public:
	virtual void init()					= 0;
	virtual void update(double delta)	= 0;
	virtual void renderFrame()			= 0;
	virtual void cleanUp()				= 0;
};

#endif //RENDERER_H