#ifndef GAMEENTITYFACTORYGL_H
#define GAMEENTITYFACTORYGL_H

#include "GraphicsContainerGL.h"
#include "../GameEntityFactory.h"

class GameEntityFactoryGL : public GameEntityFactory
{
private:
protected:
public:
	GameEntity* createPacman(VecF3 position);
	GameEntity* createGhost(VecF3 position);
	GameEntity* createPill(VecF3 position);
	GameEntity* createBloodyPill(VecF3 position);
	GameEntity* createWall(VecF3 position);

	GameEntityFactoryGL();
	virtual ~GameEntityFactoryGL();
};

#endif //GAMEENTITYFACTORYGL_H