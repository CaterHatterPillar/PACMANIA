#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <vector>

#include "Component.h"
#include "Renderer/GraphicsContainer.h"
#include "Math/PacMath.h"
#include "Messaging/ObserverDirector.h"
#include "Singleton.h"
#include "Messaging/MsgRender.h"
#include "Behaviours/MoveBehaviourPlayer.h"

using namespace std;

class GameEntity
{
private:
	VecF3 position;
	VecF3 scale;
	VecF3 rotation;

	MatF4 translationMatrix;
	MatF4 rotationMatrix;
	MatF4 scalingMatrix;
	MatF4 worldMatrix;

	GraphicsContainer* graphicsContainer;
	MoveBehaviour* moveBehaviour;

	void rebuildTranslationMatrix();
	void rebuildRotationMatrix();
	void rebuildScalingMatrix();
	void rebuildWorldMatrix();
	void initMatrices();

public:
	GameEntity();
	GameEntity(	VecF3 position, VecF3 rotation, VecF3 scale);
	~GameEntity();

	void setPosition(VecF3 position);
	void setRotation(VecF3 rotaiton);
	void setScale(VecF3 scale);

	VecF3 getPosition();
	VecF3 getRotation();
	VecF3 getScale();

	void setTranslationMatrix(MatF4 translationMatrix);
	void setRotationMatrix(MatF4 rotationMatrix);
	void setScalingMatrix(MatF4 scalingMatrix);

	MatF4 getTranslationMatrix();
	MatF4 getRotationMatrix();
	MatF4 getScalingMatrix();

	void setGraphicsContainer(GraphicsContainer* graphicsContainer);
	void setMoveBehaviour(MoveBehaviour* moveBehaviour);

	void update(double delta);
};

#endif //GAMEENTITY_H
