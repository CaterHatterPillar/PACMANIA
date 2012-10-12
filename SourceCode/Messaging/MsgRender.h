#ifndef MSGRENDER_H
#define MSGRENDER_H

#include "Msg.h"
#include "../GraphicsContainer.h"
#include "../Math/PacMath.h"

class MsgRender : public Msg
{
private:
	GraphicsContainer* graphicsContainer;

	MatF4 translationMatrix;
	MatF4 rotationMatrix;
	MatF4 scalingMatrix;
protected:
public:
	MsgRender(
		GraphicsContainer* graphicsContainer, 
		MatF4 translationMatrix, 
		MatF4 rotationMatrix, 
		MatF4 scalingMatrix) : Msg(RENDER)
	{
		this->graphicsContainer	= graphicsContainer;
		this->translationMatrix	= translationMatrix;
		this->rotationMatrix	= rotationMatrix;
		this->scalingMatrix		= scalingMatrix;
	}
	MsgRender(MsgRender* msg) : Msg(RENDER)
	{
		this->graphicsContainer	= msg->getGraphicsContainer();
		this->translationMatrix	= msg->getTranslationMatrix();
		this->rotationMatrix	= msg->getRotationMatrix();
		this->scalingMatrix		= msg->getScalingMatrix();
	}
	virtual ~MsgRender() {}

	GraphicsContainer* getGraphicsContainer() { return graphicsContainer; }
	MatF4 getTranslationMatrix()	{ return translationMatrix;	}
	MatF4 getRotationMatrix()		{ return rotationMatrix;	}
	MatF4 getScalingMatrix()		{ return scalingMatrix;		} 

	void setTranslationMatrix(MatF4 translationMatrix)
	{
		this->translationMatrix = translationMatrix;
	}
	void setRotationMatrix(MatF4 rotationMatrix)
	{
		this->rotationMatrix = rotationMatrix;
	}
	void setScalingMatrix(MatF4 scalingMatrix)
	{
		this->scalingMatrix = scalingMatrix;
	}
	void setMatrices(MatF4 translationMatrix, MatF4 rotationMatrix, MatF4 scalingMatrix)
	{
		this->translationMatrix	= translationMatrix;
		this->rotationMatrix	= rotationMatrix;
		this->scalingMatrix		= scalingMatrix;
	}
};

#endif //MSGRENDER_H