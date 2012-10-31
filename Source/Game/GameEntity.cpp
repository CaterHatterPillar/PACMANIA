#include "GameEntity.h"

GameEntity::GameEntity()
{
	position			= VecF3(0.0f, 0.0f, 0.0f);
	rotation			= VecF3(0.0f, 0.0f, 0.0f);
	scale				= VecF3(1.0f, 1.0f, 1.0f);
	graphicsContainer	= NULL;
	moveBehaviour		= NULL;
	light				= NULL;

	initMatrices();
}

GameEntity::GameEntity(	VecF3 position, VecF3 rotation, VecF3 scale)
{
	this->position	= position;
	this->rotation	= rotation;
	this->scale		= scale;

	graphicsContainer	= NULL;
	moveBehaviour		= NULL;
	light				= NULL;

	initMatrices();
}

GameEntity::~GameEntity()
{
	if(graphicsContainer)
		delete graphicsContainer;
	if(moveBehaviour)
		delete moveBehaviour;
	if(light)
		delete light;
}

void GameEntity::rebuildTranslationMatrix()
{
	translationMatrix.translation(position.x, position.y, position.z);
	rebuildWorldMatrix();
}

void GameEntity::rebuildRotationMatrix()
{
	rotationMatrix.rotation(rotation.x, rotation.y, rotation.z);
	rebuildWorldMatrix();
}

void GameEntity::rebuildScalingMatrix()
{
	scalingMatrix.scaling(scale.x, scale.y, scale.z);
	rebuildWorldMatrix();
}

void GameEntity::rebuildWorldMatrix()
{
	worldMatrix = scalingMatrix * translationMatrix * rotationMatrix;
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

void GameEntity::setMoveBehaviour(MoveBehaviour* moveBehaviour)
{
	this->moveBehaviour = moveBehaviour;
}

void GameEntity::setLight(Light* light)
{
	this->light = light;
}

void GameEntity::update(double delta)
{
	if(moveBehaviour)
	{
		moveBehaviour->update(delta);
		position = moveBehaviour->getPosition();
		rotationMatrix = moveBehaviour->getRotation();
		rebuildWorldMatrix();

		rebuildTranslationMatrix();
		
	}
	if(graphicsContainer)
	{
		MsgRender* renderMsg = new MsgRender(
			graphicsContainer, 
			translationMatrix, 
			rotationMatrix, 
			scalingMatrix);
		Singleton<ObserverDirector>::get().push(renderMsg);
	}
	if(light)
	{
		light->pos.x = position.x;
		light->pos.y = position.y;

		if(moveBehaviour)
		{
			
			float power = moveBehaviour->lightPower;
			light->att.x = 0.25f/power;
		}

		MsgLight* msgLight = new MsgLight(light);
		Singleton<ObserverDirector>::get().push(msgLight);
	}
}