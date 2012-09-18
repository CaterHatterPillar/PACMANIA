#ifndef SIMPLEGEOMETRY_H
#define SIMPLEGEOMETRY_H

#include "../../Component.h"
#include "GraphicsContainerGL.h"

#include "../../Messaging/ObserverDirector.h"
#include "../../Singleton.h"
#include "../../Messaging/MsgRender.h"

#include "../../Math/PacMath.h"

class SimpleGeometry : public Component
{
private:
	GraphicsContainerGL* graphicsContainer;
protected:
public:
	void init();
	void update(double delta);

	SimpleGeometry();
	~SimpleGeometry();
};

#endif //SIMPLEGEOMETRY_H