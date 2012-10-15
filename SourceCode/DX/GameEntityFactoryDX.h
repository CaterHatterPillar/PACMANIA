#ifndef GAMEENTITYFACTORYDX_H
#define GAMEENTITYFACTORYDX_H

#include "../GameEntityFactory.h"
#include "GraphicsContainerDX.h"

class GameEntityFactoryDX : public GameEntityFactory
{
private:
public:
	GameEntityFactoryDX();
	~GameEntityFactoryDX();

	virtual GameEntity* createPacman(VecF3 position);
	virtual GameEntity* createGhost(VecF3 position);
	virtual GameEntity* createPill(VecF3 position);
	virtual GameEntity* createBloodyPill(VecF3 position);
	virtual GameEntity* createWall(VecF3 position);

};

#endif