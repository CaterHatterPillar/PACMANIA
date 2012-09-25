#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <vector>

#include "Component.h"
#include "Renderer/GraphicsContainer.h"
#include "Math/PacMath.h"

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

	vector<Component*> components;
	GraphicsContainer* graphicsContainer;

	void rebuildTranslationMatrix();
	void rebuildRotationMatrix();
	void rebuildScalingMatrix();
	void rebuildWorldMatrix();
	void initMatrices();

public:
	GameEntity();
	GameEntity(	VecF3 position, VecF3 rotation, VecF3 scale,
				vector<Component*> components, GraphicsContainer* graphicsContainer);
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

	void update(double delta);
};

#endif //GAMEENTITY_H