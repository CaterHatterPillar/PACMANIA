#ifndef MSGRENDER_H
#define MSGRENDER_H

#include "Msg.h"
#include "../Renderer/GraphicsContainer.h"
#include "../Math/PacMath.h"

class MsgRender : public Msg
{
private:
	GraphicsContainer* graphicsContainer;
	MatF4 worldMatrix;
protected:
public:
	MsgRender(GraphicsContainer* graphicsContainer, MatF4 worldMatrix) : Msg(RENDER)
	{
		this->graphicsContainer = graphicsContainer;
		this->worldMatrix = worldMatrix;
	}
	MsgRender(MsgRender* msg) : Msg(RENDER)
	{
		this->graphicsContainer = msg->getGraphicsContainer();
		this->worldMatrix = msg->getWorldMatrix();
	}
	~MsgRender() {}

	GraphicsContainer* getGraphicsContainer() { return graphicsContainer; }
	MatF4 getWorldMatrix() { return worldMatrix; }
};

#endif //MSGRENDER_H