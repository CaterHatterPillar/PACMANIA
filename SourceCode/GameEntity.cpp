#include "GameEntity.h"

GameEntity::GameEntity()
{
	position			= VecF3(0.0f, 0.0f, 0.0f);
	rotation			= VecF3(0.0f, 0.0f, 0.0f);
	scale				= VecF3(1.0f, 1.0f, 1.0f);
	graphicsContainer	= NULL;

	initMatrices();
}

GameEntity::GameEntity(	VecF3 position, VecF3 rotation, VecF3 scale)
{
	this->position			= position;
	this->rotation			= rotation;
	this->scale				= scale;
	this->components		= components;
	this->graphicsContainer = graphicsContainer;
	
	initMatrices();
}

GameEntity::~GameEntity()
{
	for(unsigned int i=0; i<components.size(); i++)
		delete components[i];

	delete graphicsContainer;
}

void GameEntity::rebuildTranslationMatrix()
{
	translationMatrix.translation(position.x, position.y, position.z);
}

void GameEntity::rebuildRotationMatrix()
{
	rotationMatrix.rotation(rotation.x, rotation.y, rotation.z);
}

void GameEntity::rebuildScalingMatrix()
{
	scalingMatrix.scaling(scale.x, scale.y, scale.z);
}

void GameEntity::rebuildWorldMatrix()
{
	worldMatrix = scalingMatrix * rotationMatrix * translationMatrix;
}

void GameEntity::initMatrices()
{
	rebuildTranslationMatrix();
	rebuildRotationMatrix();
	rebuildScalingMatrix();
	rebuildWorldMatrix();
}

void GameEntity::setPosition(VecF3 position)
{
	this->position = position;
	rebuildTranslationMatrix();
	rebuildWorldMatrix();
}

void GameEntity::setRotation(VecF3 rotation)
{
	this->rotation = rotation;
	rebuildRotationMatrix();
	rebuildWorldMatrix();
}

void GameEntity::setScale(VecF3 scale)
{
	this->scale = scale;
	rebuildScalingMatrix();
	rebuildWorldMatrix();
}

VecF3 GameEntity::getPosition()
{
	return position;
}

VecF3 GameEntity::getRotation()
{
	return rotation;
}

VecF3 GameEntity::getScale()
{
	return scale;
}

void GameEntity::setTranslationMatrix(MatF4 translationMatrix)
{
	this->translationMatrix = translationMatrix;
	rebuildWorldMatrix();
}

void GameEntity::setRotationMatrix(MatF4 rotationMatrix)
{
	this->rotationMatrix = rotationMatrix;
	rebuildWorldMatrix();
}

void GameEntity::setScalingMatrix(MatF4 scalingMatrix)
{
	this->scalingMatrix = scalingMatrix;
	rebuildWorldMatrix();
}

MatF4 GameEntity::getTranslationMatrix()
{
	return translationMatrix;
}

MatF4 GameEntity::getRotationMatrix()
{
	return rotationMatrix;
}

MatF4 GameEntity::getScalingMatrix()
{
	return scalingMatrix;
}

void GameEntity::setGraphicsContainer(GraphicsContainer* graphicsContainer)
{
	this->graphicsContainer = graphicsContainer;
}

void GameEntity::update(double delta)
{
	if(graphicsContainer)
	{
		MsgRender* renderMsg = new MsgRender(graphicsContainer, worldMatrix);
		Singleton<ObserverDirector>::get().push(renderMsg);
	}
}